/*
 *  Seeds.cpp
 *  intraspecific
 *
 *  Created by Martin Köchy on Thu Feb 06 2003.
 *  Copyright (c) 2003 __MyCompanyName__. All rights reserved.
 *
 */

#include <iostream>		// for testing
#include <math.h>		// for sin()
#include "r250m.h"
#include "normdistfunctions.h"
#include "MyTime.h"
#include "Grid.h"
#include "Soil.h"		// for getRunoff() and getPotentialO()
#include "SeedParameters.h"
#include "MK_round.h"
#include "Seeds.h"

using namespace std;
/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
*/
/*
const SEED_PARAMETERS SEEDS::sSP = SEED_PARAMETERS();
const cSPAveSteri cSAveSteri::sASP = cSPAveSteri();
const cSPBiscDid cSBiscDid::sBDP = cSPBiscDid();
const cSPBraDist cSBraDist::sBrDP = cSPBraDist();
const cSPBromFasc cSBromFasc::sBFP = cSPBromFasc();
const cSPCarrAnn cSCarrAnn::sCAP = cSPCarrAnn();
const cSPCriDeli cSCriDeli::sCDP = cSPCriDeli();
const cSPFilDes cSFilDes::sFDP = cSPFilDes();
const cSPHippUni cSHippUni::sHUP = cSPHippUni();
const cSPHymCir cSHymCir::sHCP = cSPHymCir();
const cSPRebPin cSRebPin::sRPP = cSPRebPin();
const cSPSchisArab cSSchisArab::sSAP = cSPSchisArab();
const cSPStipCap cSStipCap::sSCP = cSPStipCap();
const cSPValHis cSValHis::sVHP = cSPValHis();
const cSPTypMes cSTypMes::sTMesP = cSPTypMes();
const cSPTypMed cSTypMed::sTMedP = cSPTypMed();
const cSPTypSem cSTypSem::sTSemP = cSPTypSem();
const cSPTypAri cSTypAri::sTAriP = cSPTypAri();
*/
long  SEEDS::theNumberOfAllSeeds = 0;
 
SEEDS::SEEDS (void)
{
  theNewSeeds = 0;
	theTSumR = 0.0;
	theGerminated = false;
	theTheta = 0.0;
	theTSumG = 0.0;
	theWetDays = 0;
}

SEEDS::~SEEDS ()
{
}

void SEEDS::setParameters (SEED_PARAMETERS* pSeedP)
{
  pP = pSeedP;
  thePsiB = pP->PsiB50b;
  initializeSeedbank(pP->iniSeedNbr);
}
/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm

_initializeSeedbank_

*/

void SEEDS::initializeSeedbank(float n)
{
	// start with some random seed number that is on average that of iniSeedNbr
  if (pP->iniSeedNbrV > 0.0)
  {
	float se = vr250() * pP->iniSeedNbrV; //
	n = n*(1.0+se);
  }
  if (n < 0.0) n = 0;
  
  float seeds_per_cell = n * cellArea / 1.0E4;
  
  theNumber = MK_rRound(seeds_per_cell);
  theNumberOfAllSeeds+=theNumber;
  theNGerminable = 0;
}

void SEEDS::prepareNewYear (void)
{
  theNGerminable = 0;
  theGerminated = false;
  theReady = 0;
  theOldReady = 0;
  long seedsToSeedbank = 0;
  
// constant seedbank for testing
  if (pP->constSeedbank){
	initializeSeedbank(pP->iniSeedNbr);
	theNewSeeds = 0;
  }
		
  // predation of dispersed seeds
  seedsToSeedbank = predation(theNewSeeds, pP->survRate, pP->survRateV);
	 
  // add dispersed seeds to seedbank
  theNumber += seedsToSeedbank;
  
  // calculate how many seeds are active (non-dormant)
  if (pP->maxGerm < 1.0){
	if (theNumber > 6) // saves computing time
	  theNGerminable = MK_rRound(theNumber * pP->maxGerm);
	else {
	  for (long n = 0; n < theNumber; n++)
	  {float z = dr250();
		if (z < pP->maxGerm)
		  theNGerminable++;
	  }
	}
  }
  else
	theNGerminable = theNumber;
  // if there is only one seed, calculate PsiB
  if (theNGerminable == 1)
	thePsiB = pP->PsiB50b + pP->PsiB50S*stdnormalcum_inv(dr250()); // tested, OK  
}
  
  /*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm

_updateSeedbank_

Encapsulation function for all seed processes

*/

void SEEDS::updateSeedbank (int day, float T, float TIndex, float psi_of_surface_layer, bool Plant_alive)
{
  theDay = day;
  theTSumR += T;
  float HTT;
  theGerminated = Plant_alive;
   
 if (!Plant_alive && (theReady > 0)) {
	float z = 0.0;	float p = 0.0;
	p = controlDensity(theReady);
	z = dr250();
	if (z<p)
	  germination();
  }
 
 theOldReady = theReady;
 
  if (theNGerminable)
  {
    if (theNGerminable == 1)
	  HTT = calcHydroThermalTimeB(psi_of_surface_layer, T);
	else
	  HTT = calcHydroThermalTimeG(psi_of_surface_layer, T);
	
	float p = HTT * activity(day);
	theReady = MK_rRound(float(theNGerminable) * p);
  }  
  
  if (day == days_in_year-1) // at end of year
  {  /* accounting; keep "newSeeds" separate to allow granivory on only newly dispersed seeds, not seeds in seedbank*/
	theNumberOfAllSeeds += (theNumber + theNewSeeds);
	theNumber = oldSeedbankSurvival(theNumber, pP->seedbankPersistence);
  }
}			


/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm

This function calculates the loss of dispersed seeds due to predation.

*/

long SEEDS::predation (long newSeeds, double survivalRate, double sRV)
{ int count = newSeeds;
  for (unsigned short i = 0; i < cNeighbourhood; i++) 
	count += pTheNeighbours[i]->getNewSeeds();
  
  if (count > pP->granivoryThreshold/10000.0*19.0)
	newSeeds=MK_rRound(newSeeds*(survivalRate+sRV*vr250()));
  else
	newSeeds=MK_rRound(newSeeds*pP->seedbankPersistence);
  return newSeeds;
}

/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm

This function summerizes the loss of viable seeds in the seedbank (before dispersed seeds are added) between two growth periods

*/

long	SEEDS::oldSeedbankSurvival (long oldSeeds, double oSbRate)
{
  oldSeeds = MK_rRound(oldSeeds*oSbRate);
  return oldSeeds;   
}


/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm

_setSPPointers_

*/
void SEEDS::setSPPointers (TIME* p_Time, GRID* p_Grid, int col, int row, SOIL* location)
{
  pTIME = p_Time;
  pGRID = p_Grid;
  theCol = col;
  theRow = row;
  int c = 0; // counter
  
  for (unsigned int l = 1; l <= cSuppress_dist; l++)
	for (unsigned int i = 0; i < NCellsOnPerimeter(l); i++) {
	  pSNeighbourhood[c] = p_Grid->getNbrGPtr(theCol, theRow, i*60, l); // soil neighbours
	  pTheNeighbours[c] = pSNeighbourhood[c]->getPSeedbank(); // seedbank neighbours
	  c++;
	}
	  
  pHere = location;
}

/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm

_prepare germination_

*/

float SEEDS::controlDensity (long germinableS)
{
  long maxN = 0;
  long count = germinableS;
  int countGerminated = 0;
  int cells = germinableS ? 1 : 0;
  float p = 0.0;
  
  // count how many germinable seeds are in how many cells in the nbhood
  for (unsigned short i = 0; i < cNeighbourhood; i++){ 
	int temp = pTheNeighbours[i]->getHowManyReady(theDay-1);
	count += temp;
	if (temp)
	  cells++;
	countGerminated += pTheNeighbours[i]->isGerminated();}
  
  // if there is >1 germinable seed, calculate density effect
  if (count>1) {
	// density dependence; calculated from Goldberg et al. 2001
	// a = 1+slope  in Goldberg et al. 2001
	// (max seedl density in nbhd) = 
	//	  (�(germinableS in nbhd) / nbhd * 1E4)^a / 1E4 * nbhd
	double nbspm2 = double(count)/double(cNeighbourhood+1)*1.0E4;
	double d = 0.0;
	d = pP->DD + pP->DDv*vr250();
	
	if (d>1) d = 1;
	maxN = MK_rRound(pow(nbspm2, d) / 1.0E4 * (cNeighbourhood+1));
  }
  else 
	maxN = 1;
  
  // adjust probability of germination depending on how many
  // seeds are still "allowed"
  int lack = maxN > countGerminated? maxN - countGerminated : 0;
  p = double(lack)/double(cells-countGerminated);
  
  return p;
}


/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm

_germination_

This function calculates whether one seed from the seedbank has germinated.

*/

void SEEDS::germination (void)
{
	  if(theNumber>0) 
	  {theNumber--; // remove germinated seeds from seedbank
		theGerminated = true;}
}


/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm

_calcHydroThermalTimeG_

calculates the germination percentage based on the hydro-time concept (Bradford 1995)
probit (g) = [SUM(Psi-PsiB50) - thetaHT/(SUM(T-Tb)/t)] / (t * PsiB50s)

*/

float SEEDS::calcHydroThermalTimeG (float Psi, float T)
{
  float G = 0.0; // germination percentage [0;1)
  float probitG = 0.0;
  
  // calculate PsiB50 as a linear function of T (Allen et al. 2000)
  float PsiB50 = pP->PsiB50m * T + pP->PsiB50b;

  float PsiB50Min = PsiB50 - 2.0*pP->PsiB50S;
  
  float PsiDiff =  Psi - PsiB50Min;
  float TDiff = T - pP->Tmin;

	if (PsiDiff > 0.0 && TDiff > 0.0) {
		theDryDays = 0;
		theWetDays++;	// count hydrotime
		theTheta += PsiDiff;
        theTSumG += TDiff;
	}
	else {        
		theDryDays++;
		if (theDryDays >= pP->DryDaysMax) {
			theTheta = 0.0;
            theTSumG = 0.0;
			theWetDays = 0;
		}
	}
					
	if (PsiDiff > 0.0 & TDiff > 0.0)
    {
		probitG = (theTheta/theWetDays - pP->thetaH/theTSumG)/pP->PsiB50S;
		G =  stdnormal_cdf(probitG);
	}
  
    return G;
}

// version for one seed
float SEEDS::calcHydroThermalTimeB (float Psi, float T)
{
  float PsiDiff = Psi - thePsiB;
  float TDiff = T - pP->Tmin;
    
  if (PsiDiff > 0.0 && TDiff > 0.0) {
	theDryDays = 0;
	theWetDays++;	// count hydrotime
	theTheta += (PsiDiff * TDiff);
  }
  else {        
	theDryDays++;
	if (theDryDays >= pP->DryDaysMax) {
	  theTheta = 0.0;
	  theWetDays = 0;
	}
  }
  
  if (PsiDiff > 0.0 & TDiff > 0.0 && (theTheta > pP->thetaH))
	  return 1.0;
	else
	  return 0.0;
}

/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm

_activity_

Seed dormancy is lowest around New Year (K. Tielbörger, pers. comm) and germination generally occurs only between November and February. 
Day of year is a surrogate for cues like temperature or day length. Activity ranges between 0 and maximum germination percentage (0≤a≤1).
     _
    | \
___/   \__

*/

/*float SEEDS::activity (float TIndex)
{ // Variante 1
  float ready = 0.0;

  float m1_2 = (pP->AY[2]-pP->AY[1])/(pP->AX[2]-pP->AX[1]); float b1_2 = -m1_2*pP->AX[1]+pP->AY[1];
  float m2_3 = (pP->AY[3]-pP->AY[2])/(pP->AX[3]-pP->AX[2]); float b2_3 = -m2_3*pP->AX[2]+pP->AY[2];
  float m3_4 = (pP->AY[4]-pP->AY[3])/(pP->AX[4]-pP->AX[3]); float b3_4 = -m3_4*pP->AX[3]+pP->AY[3];
  float m4_5 = (pP->AY[5]-pP->AY[4])/(pP->AX[5]-pP->AX[4]); float b4_5 = -m4_5*pP->AX[4]+pP->AY[4];
  float m5_6 = (pP->AY[6]-pP->AY[5])/(pP->AX[6]-pP->AX[5]); float b5_6 = -m5_6*pP->AX[5]+pP->AY[5];
  
		    
  if (d < pP->AX[1]) ready = pP->AY[0];
  else
    if (d < pP->AX[2]) ready = m1_2 * d + b1_2;
    else
      if (d < pP->AX[3]) ready = m2_3 * d + b2_3;
      else
        if (d < pP->AX[4]) ready = m3_4 * d + b3_4;
        else
          if (d < pP->AX[5]) ready = m4_5 * d + b4_5;
          else
            if (d < pP->AX[6]) ready = m5_6 * d + b5_6;
            else
                ready = pP->AY[7];
                
    ready += (dr250()*pP->ActivityV);
          
    if (ready > 1.0) ready = 1.0;
    else if (ready < 0) ready = 0.0;

	return ready;
}
*/
/*
float SEEDS::activity (float TIndex)
{ // Variante 2
  float ready = 0.0;
  // check range of TIndex
  if (TIndex < 0)
    ready = pow(float (-TIndex), float(0.1));
  return ready;
}
*/

float SEEDS::activity (int day)
{ // Variante 3: Gauss peak shape curve
  float ready = 0.0;
  float width = 30.0;
  int peakDay = 167;
  int flatness = 4; // must be an even number!
    ready = exp(-pow(float(day-peakDay),flatness)/(2.0*pow(width,flatness)));
  return ready;
}



/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm

This function adds the number of dispersed seeds to the temporary seedbank

*/
			
void SEEDS::addSeeds (int number)
{   
	theNewSeeds += number;
	theTSumR = 0.0;
}
  
void SEEDS::zeroNewSeeds (void)
{
  theNewSeeds = 0;
}
/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
*/

long SEEDS::getNumber (void) const
{
	return theNumber;
}

long SEEDS::getNewSeeds (void) const
{
  return theNewSeeds;
}

// ---------------------
        	
bool SEEDS::isGerminated (void) const
{
	return theGerminated;
}

long SEEDS::getHowManyReady (int wantday) const
{
  if (wantday==theDay)
	return theReady;
  else
	return theOldReady;
}

long SEEDS::getGNumber (void) const
{
  return theNGerminable;
}

// ---------------------
long SEEDS::getNumberOfAllSeeds (void)
{
	return theNumberOfAllSeeds; // all available seeds
}

// ---------------------

void SEEDS::zeroAllSeeds (void)
{
	theNumberOfAllSeeds = 0;
}
/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm*/
/*
cSAveSteri::cSAveSteri(void) : SEEDS(sASP)
{
}

cSBiscDid::cSBiscDid(void) : SEEDS(sBDP)
{
}

cSBraDist::cSBraDist(void) : SEEDS(sBrDP)
{
}

cSBromFasc::cSBromFasc(void) : SEEDS(sBFP)
{
}

cSCarrAnn::cSCarrAnn(void) : SEEDS(sCAP)
{
}

cSCriDeli::cSCriDeli(void) : SEEDS(sCDP)
{
}

cSFilDes::cSFilDes(void) : SEEDS(sFDP)
{
}

cSHippUni::cSHippUni(void) : SEEDS(sHUP)
{
}

cSHymCir::cSHymCir(void) : SEEDS(sHCP)
{
}

cSRebPin::cSRebPin(void) : SEEDS(sRPP)
{
}

cSSchisArab::cSSchisArab(void) : SEEDS(sSAP)
{
}

cSStipCap::cSStipCap(void) : SEEDS(sSCP)
{
}

cSValHis::cSValHis(void) : SEEDS(sVHP)
{
}

cSTypMes::cSTypMes(void) : SEEDS(sTMesP)
{
}
cSTypMed::cSTypMed(void) : SEEDS(sTMedP)
{
}
cSTypSem::cSTypSem(void) : SEEDS(sTSemP)
{
}
cSTypAri::cSTypAri(void) : SEEDS(sTAriP)
{
}
*/
