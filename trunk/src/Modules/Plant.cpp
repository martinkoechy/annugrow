/*
 *  Plant.cpp
 *  intraspecific
 *
 *  Created by Martin Köchy on Thu Feb 06 2003.
 *  Copyright (c) 2003 __MyCompanyName__. All rights reserved.
 *
 */

#include <iostream>
#include <math.h>
#include "r250m.h"
#include "MK_round.h"
#include "MyTime.h"
#include "Grid.h"
#include "PlantParameters.h"
#include "Plant.h"

//using namespace std;

/* mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
*/

long	PLANT::theNumberOfAllPlants = 0;
long	PLANT::theMatureIndividuals = 0;
float PLANT::theTotalDailyMass = 0.0;
/*const  PLANT_PARAMETERS PLANT::sSP = PLANT_PARAMETERS();

long cPAveSteri::theNumberOfAllAvena = 0;
long cPAveSteri::theMatureAvena = 0;
const cPPAveSteri cPAveSteri::sASP = cPPAveSteri();

long cPBiscDid::theNumberOfAllBiscutella = 0;
long cPBiscDid::theMatureBiscutella = 0;
const cPPBiscDid cPBiscDid::sBDP = cPPBiscDid();

long cPBraDist::theNumberOfAllBrachypodium = 0;
long cPBraDist::theMatureBrachypodium = 0;
const cPPBraDist cPBraDist::sBrDP = cPPBraDist();

long cPBromFasc::theNumberOfAllBromus = 0;
long cPBromFasc::theMatureBromus = 0;
const cPPBromFasc cPBromFasc::sBFP = cPPBromFasc();

long cPCarrAnn::theNumberOfAllCarrichtera = 0;
long cPCarrAnn::theMatureCarrichtera = 0;
const cPPCarrAnn cPCarrAnn::sCAP = cPPCarrAnn();

long cPCriDeli::theNumberOfAllCrithopsis = 0;
long cPCriDeli::theMatureCrithopsis = 0;
const cPPCriDeli cPCriDeli::sCDP = cPPCriDeli();

long cPFilDes::theNumberOfAllFilDes = 0;
long cPFilDes::theMatureFilDes = 0;
const cPPFilDes cPFilDes::sFDP = cPPFilDes();

long cPHippUni::theNumberOfAllHippUni = 0;
long cPHippUni::theMatureHippUni = 0;
const cPPHippUni cPHippUni::sHUP = cPPHippUni();

long cPHymCir::theNumberOfAllHymCir = 0;
long cPHymCir::theMatureHymCir = 0;
const cPPHymCir cPHymCir::sHCP = cPPHymCir();

long cPRebPin::theNumberOfAllRebPin = 0;
long cPRebPin::theMatureRebPin = 0;
const cPPRebPin cPRebPin::sRPP = cPPRebPin();

long cPSchisArab::theNumberOfAllSchisArab = 0;
long cPSchisArab::theMatureSchisArab = 0;
const cPPSchisArab cPSchisArab::sSAP = cPPSchisArab();

long cPStipCap::theNumberOfAllStipa = 0;
long cPStipCap::theMatureStipa = 0;
const cPPStipCap cPStipCap::sSCP = cPPStipCap();

long cPValHis::theNumberOfAllVala = 0;
long cPValHis::theMatureVala = 0;
const cPPValHis cPValHis::sVHP = cPPValHis();

long cPTypMes::theNumberOfAllTypMes = 0;
long cPTypMes::theMatureTypMes = 0;
const cPPTypMes cPTypMes::sTMesP = cPPTypMes();

long cPTypMed::theNumberOfAllTypMed = 0;
long cPTypMed::theMatureTypMed = 0;
const cPPTypMed cPTypMed::sTMedP = cPPTypMed();

long cPTypSem::theNumberOfAllTypSem = 0;
long cPTypSem::theMatureTypSem = 0;
const cPPTypSem cPTypSem::sTSemP = cPPTypSem();

long cPTypAri::theNumberOfAllTypAri = 0;
long cPTypAri::theMatureTypAri = 0;
const cPPTypAri cPTypAri::sTAriP = cPPTypAri();
*/

PLANT::PLANT (void)
{
	theMass = 0.0;
	theOldMass = 1.0;
//	theMaxMass = 0.0;
	theDay = 0;
	theReprTissue = 0.0;
	theDiaspores = 0;
	theCohort = 0;
	theMatureUpdated = false;
  theSoilN = medium;
  theSpecies = noSpec;
}


PLANT::~PLANT ()
{
}

void PLANT::setParameters (PLANT_PARAMETERS* pPlantP)
{
  pP = pPlantP;
}

/* mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm

_updatePlant_

Envelope function. Called from SOIL::updateSoil.

*/

bool PLANT::updatePlant (int day, bool hasGerminated)
{
  theDay = day;

  const int n_layers = 4;
  float psi[n_layers] = {
	pHere->getPotentialA1(), pHere->getPotentialA2(), pHere->getPotentialA3(), pHere->getPotentialA4()};
  
 // limit water uptake to rooting depth; similar categories as in Kigel et al. 2002 App.
  if (theMass <  pP->MassAccessA4) psi[3] = SOIL::PsiMin_MPa; // A4
  if (theMass <  pP->MassAccessA3) psi[2] = SOIL::PsiMin_MPa; //A3
  if (theMass <  pP->MassAccessA2) psi[1] = SOIL::PsiMin_MPa; //A2
  
	if (!theDay)
		reset();
        
	if (theMass == 0.0 && hasGerminated)
		establish ();

	if (theMass > 0.0)
	{
		grow (MK_max(psi, n_layers)); // ??? hier noch berücksichtigen, dass Wasser
										 // aus Nachbarzelle aufgebraucht werden kann.
		loseMass (0.0); // nothing happening yet

		if (theMass/theOldMass < 1.001)
		  wilting();
	}
		// prevent germination when cell is occupied or after successful germination
	if (theMass > 0.0)
		return true;	// occupied
	else
		return false;	// empty cell
}


/* mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm

_reset_: Things to do before a new year starts.

*/

void PLANT::reset(void)
{
	theDiaspores = 0;	// leave this here, don't put it in disperse()
						// or the GRID::getResults function can't get it
	theMaxMass = 0.0;
  theOldMass = 0.0;
	theCohort = 0;
	theIsMature = false; // not really necessary
}

/* mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm

_establish_

*/

void PLANT::establish (void)
{		
	NSupplyQ soilN;
    theMass = pP->MassSeed * (1.0+vr250()*0.2);
	theNumberOfAllPlants++;
    
    soilN = pHere->getNSupply();
    
    if (pP->N_tolerance == zero)
      theNLimitation = 1.0;
    else {
      switch (soilN) {
		case zero: theNLimitation = 0.0; break;
        case low: theNLimitation = 0.4; break; //0.3653, Dyer et al. 2001
        case medium: theNLimitation = 0.7; break; 
        case high: theNLimitation = 1.0; break;
		default: std::cerr<< "soilN hat falschen Wert" << std::endl;
      }
    }
    
    theLLimitation = pHere->getRelLight();
}

/* mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm

_relativeWetness_
 
This logistic function calculates an index, "effective soil moisture".
At 100% ESM, growth is maximal, at 0%, growth is nil. I have fitted the
parameters so that it corresponds to the statement in Benecke's Hydrology
lecture notes p. 36. PWP differs for each species and can be < -1.5 
(Larcher, p. 294)

*/

float PLANT::relativeWetness (float psiRoots)
{
  float rW = 0.0;
  float PWP = pP->PWP;
	if (psiRoots < PWP)
		rW = 0.0;
	else
		if (psiRoots < SOIL::FKPsi_MPa)
			rW = 1/(1+exp(12.5/PWP*(psiRoots-PWP)+5.3));
		else
			rW = 1.0;
	
	return rW; // [0.0;1.0]
}


/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm

_grow_

This function is the logistic growth equation 
because growthRate() is a function of mass.

*/

void PLANT::grow (float psiRoots)
{
	float newGrowth = 0.0;
	float newReprTissue = 0.0;
	
	resourceUptake();
	
	newGrowth = (theMass-theReprTissue) * growthRate(psiRoots); // changed in 2.6.0
	
	//--- allocate some mass to produce fruits ---
	if (theMass > pP->MassFlowering)
	{
		newReprTissue = newGrowth * pP->AllocationRepro;
		newGrowth -= newReprTissue;
		if (theMass > pP->MassFlowering + pP->MassFruit)
		{
			if (theMatureUpdated == false)
			{	theMatureIndividuals++; theMatureUpdated = true;}
			theIsMature = true;
		}
		else
			theIsMature = false;
	}
	
	theReprTissue += newReprTissue;// add to total reproductive tissue
	theOldMass = theMass;
	if (theMass > theMaxMass)
		theMass += (newGrowth + newReprTissue); // add produced mass to 
	//  existing mass; changed in 2.6.0
	
	theTotalDailyMass += theMass;
}


/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm

_growthRate_

The growth rate depends on the soil moisture and the present mass

*/

float PLANT::growthRate (float psiRoots)
{
    float RGR = 0.0;
  
	// the slope (first derivative of logistic growth function)
	RGR = pP->RGR_Max - pP->RGR_Max/pP->MassMax*theMass; // Reproductive mass is contributing to RGR and RGR is based on total mass.
	RGR += dr250()*0.01-0.005; // add a little variation
	if (RGR < 0.0) RGR = 0.0; // make sure RGR is not negative
		
    // effect of seasonal temperature
	float T = pTIME->getTemperature();
    if (T<25.0)
		RGR *= exp(-1.7329+0.06931*T); // Q10 rule
	
	// effect of soil moisture, shrub cover, and nutrients
    float limitations [] = {
      relativeWetness(psiRoots), 
      theLLimitation, 
      theNLimitation
      };
      
    RGR *= MK_min(limitations, 3);
	 
	RGR *= suppression(); // added 2005-02-23

    return exp(RGR)-1.0; // convert from RGR to absolute GR
}

/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
 _resourceUptake_

*/

void PLANT::resourceUptake (void)
{
  int neighbours = 0;
  
  if (theMass > pP->MassCompetition2)
	neighbours = 18;
  else if (theMass > pP->MassCompetition1)
	neighbours = 6;
  
  for (short c = 0; c<neighbours; c++)
	pSNeighbourhood[c]->setResourceShare(theMass);
}

/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm

_suppression_

This function calculates a competitive suppression index with range [0.0;1.0].
My competition index.

*/

float PLANT::suppression (void)
{
  int neighbours = 0;
  if (theMass > pP->MassCompetition2)
	neighbours = 18; // only immdediate neighbours
  else if (theMass > pP->MassCompetition1)
	neighbours = 6;
  
	float K = pP->Home;
  float iNb = 1.0-K;

	if (!neighbours)
	  K = 1.0;
	else
	  for (short c = 0; c < neighbours; c++)
		K += (pSNeighbourhood[c]->getResourceShare(theMass))/float(neighbours) * iNb;
	
	if (K < pP->DDMortality) // density-dependent mortality
	  K = 0.0;

	return K*K;
}

/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm

_setSPPointers_

*/
void PLANT::setSPPointers (TIME* p_Time, GRID* p_Grid, int col, int row, SOIL* location)
{
	pTIME = p_Time;
	pGRID = p_Grid;
	theCol = col;
	theRow = row;
	int c = 0; // counter
	
	for (unsigned int l = 1; l <= cSuppress_dist; l++)
	  for (unsigned int i = 0; i < NCellsOnPerimeter(l); i++) {
		pSNeighbourhood[c] = pGRID->getNbrGPtr(theCol, theRow, i*60, l); // soil neighbours
		pTheNeighbours[c] = pSNeighbourhood[c]->getPPlant(); // plant neighbours
		c++;
	  }
	
  pHere = location;
}


/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
*/

void PLANT::loseMass (float amount)
{
	theMass -= amount;
}


/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
*/

void PLANT::wilting (void)
{
	short seeds = calcSeeds();
//if (theMass > theMassFlowering && seeds == 0) std::cerr << "verdorrt ohne Frucht" <<  std::endl;
    if (seeds > 0)
      disperse(seeds);        

    theOldMass = theMass;
    theMass = 0.0;
    theReprTissue = 0.0;
    theNumberOfAllPlants--;
    if (theMatureUpdated == true)
    {	theMatureIndividuals--; theMatureUpdated = false;}
	 theIsMature = false;
}


/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
*/
void PLANT::disperse (int seeds)
{
  theDiaspores += seeds; // in case of >1 cohorts/yr
  
  if (seeds)
  {
	short seedsInPackage = 3;	
	float direction = 0.0;
	int distance = 0;
	
	if (seeds < seedsInPackage) // when there are mayn seeds, 
	{					        // they are dispersed in packages of htree to speed up the simulation
	  seedsInPackage = 1; 
	}
	
	do
	{
	  direction = dr250()*360.0; // random direction
	  float z = 1.0-dr250();	  // random distance
	  if (!z)					  // if seeds disperse beyond ...
		distance = pGRID->getNCells(3);	  // ... disperse them only to nearest edge
	  else
		distance = int(-5.0*log(z));  // inv. of cumul. distri. function of exp. distribution
	  pGRID->getNbrGPtr (theCol, theRow, direction, distance)
		->getPSeedbank()->addSeeds(seedsInPackage);
	  seeds -= seedsInPackage;
	  if(seeds<seedsInPackage) seedsInPackage = seeds;
	}
	while (seeds);
  }
}

/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm

_calcSeeds_

This function returns the number of fruits (=seeds),
MassFruit should include the proportion of supporting
mass remaining on the plant.
So basically, MassFruit = reproductive structures/seeds produced.

*/

short PLANT::calcSeeds (void)
{
	int newFruits = 0;

	if (theMass > pP->MassFlowering)
		newFruits = int(theReprTissue/pP->MassFruit);

	if (newFruits > 0)
		theCohort++;

	return newFruits;
}


/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
*/

float PLANT::getOldMass (void) const
{
	return theOldMass;
}

// ---------------------

float PLANT::getMass (void) const
{
	return theMass;
}

// ---------------------

float PLANT::getMaxMass (void) const
{
	return theMaxMass;
}

// ---------------------

short PLANT::getAllSeeds (void) const
{
	return theDiaspores;
}

// ---------------------

int PLANT::getDay (void) const
{
	return theDay;
}

// ---------------------

bool PLANT::isMature (void) const
{
//  return theIsMature;
  if (theMass >= pP->MassFlowering)  return true;
  else return false;

}

int PLANT::getCohorts (void) const
{
	return theCohort;
}

// ---------------------

long PLANT::getNumberOfPlants (void)
{
    return theNumberOfAllPlants;
}

// ---------------------

long PLANT::getNumberOfMaturePlants (void)
{
	return theMatureIndividuals;
}

// ---------------------

float PLANT::getTotalShootMass (void)
{
	return theTotalDailyMass;
}

SPECIES PLANT::getASpecies (void) const
{
  return pP->name;
}

bool PLANT::isEstablished (void) const
{
  if (theMass >= pP->MassEstablish)  
	return true;
  else 
	return false;
}

bool PLANT::isSeedling (void) const
{
  if (theMass > 0.1)  return true;
  else return false;
}

/* ---------------------
_zeroNumberOfAllPlants_

necessary because static variable carries over to next trial. When this function is called, the mortality parameters should be inspected.

*/
void PLANT::zeroNumberOfAllPlants (void)
{
	if (theNumberOfAllPlants>0)
	{
		cerr << "Total number of plants set to zero." << endl;
		theNumberOfAllPlants = 0;
	}
	theMatureIndividuals = 0;
}

// ---------------------
void PLANT::zeroTotalDailyMass (void)
{
  theTotalDailyMass = 0.0;
}

/* ============================ */
/*
 cPAveSteri::cPAveSteri(void) : PLANT(sASP)
{
  theSpecies = AveSteri;
}
cPBiscDid::cPBiscDid(void) : PLANT(sBDP)
{
  theSpecies = BiscDid;
}
cPBraDist::cPBraDist(void) : PLANT(sBrDP)
{
  theSpecies = BraDist;
}

cPBromFasc::cPBromFasc(void) : PLANT(sBFP)
{
  theSpecies = BromFasc;
}

cPCarrAnn::cPCarrAnn(void) : PLANT(sCAP)
{
  theSpecies = CarrAnn;
}
cPCriDeli::cPCriDeli(void) : PLANT(sCDP)
{
  theSpecies = CriDeli;
}

cPFilDes::cPFilDes(void) : PLANT(sFDP)
{
  theSpecies = FilDes;
}

cPHippUni::cPHippUni(void) : PLANT(sHUP)
{
  theSpecies = HippUni;
}
void cPHippUni::setRGRmax (NSupplyQ soilN)
{
}

cPHymCir::cPHymCir(void) : PLANT(sHCP)
{
  theSpecies = HymCir;
}

void cPHymCir::setRGRmax (NSupplyQ soilN)
{
}

cPRebPin::cPRebPin(void) : PLANT(sRPP)
{
  theSpecies = RebPin;
}

cPSchisArab::cPSchisArab(void) : PLANT(sSAP)
{
  theSpecies = SchisArab;
}

cPStipCap::cPStipCap(void) : PLANT(sSCP)
{
  theSpecies = StipCap;
}

cPValHis::cPValHis(void) : PLANT(sVHP)
{
  theSpecies = ValHis;
}

cPTypMes::cPTypMes(void) : PLANT(sTMesP)
{
  theSpecies = typMes;
}
cPTypMed::cPTypMed(void) : PLANT(sTMedP)
{
  theSpecies = typMed;
}
cPTypSem::cPTypSem(void) : PLANT(sTSemP)
{
  theSpecies = typSem;
}
cPTypAri::cPTypAri(void) : PLANT(sTAriP)
{
  theSpecies = typAri;
}
*/
// additional species require changes in SOIL, RESULTS, PLANT, SEEDS, main, user_input
