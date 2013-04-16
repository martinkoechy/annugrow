/*
 *  Results.cpp
 *  intraspecific
 *
 *  Created by Martin Köchy on Thu Feb 06 2003.
 *  Copyright (c) 2003 __MyCompanyName__. All rights reserved.
 *
 */


#include <fstream>
#include <iostream>
#include <time.h>
#include "MyTime.h"
#include "Rain.h"
#include "Grid.h"
#include "Results.h"

using namespace std;

/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
*/

RESULTS::RESULTS(const char* baseFileName, int fileInput, const char* ID): theSimID(ID)
{
	const char tagDLC [] = "_DLC.txt";
	const char tagYCC [] = "_YCC.txt";
	const char tagYLC [] = "_YLC.txt";
	const char tagYLG [] = "_YLG.txt";
	const char tagYRoG [] = "_YRoG.txt";
	const char tagYA1G [] = "_YA1G.txt";
	const char tagYA2G [] = "_YA2G.txt";
	const char tagYA3G [] = "_YA3G.txt";
	const char tagYA4G [] = "_YA4G.txt";
	const char tagYCWG [] = "_YCWG.txt";
	const char tagPers [] = "_pers.txt";
	const char tagList [] = "_log.txt";

	strcpy (theResultsDailyLattCol, baseFileName);
	strcat (theResultsDailyLattCol, tagDLC);
	
	strcpy (theResultsYearlyCellCol, baseFileName);
	strcat (theResultsYearlyCellCol, tagYCC);
	
	strcpy (theResultsYearlyLattCol, baseFileName);
	strcat (theResultsYearlyLattCol, tagYLC);
	
	strcpy (theResultsYearlyLattGrid, baseFileName);
	strcat (theResultsYearlyLattGrid, tagYLG);

	strcpy (theResultsYearlyRoGrid, baseFileName);
	strcat (theResultsYearlyRoGrid, tagYRoG);
	strcpy (theResultsYearlyA1Grid, baseFileName);
	strcat (theResultsYearlyA1Grid, tagYA1G);
	strcpy (theResultsYearlyA2Grid, baseFileName);
	strcat (theResultsYearlyA2Grid, tagYA2G);
	strcpy (theResultsYearlyA3Grid, baseFileName);
	strcat (theResultsYearlyA3Grid, tagYA3G);
	strcpy (theResultsYearlyA4Grid, baseFileName);
	strcat (theResultsYearlyA4Grid, tagYA4G);
	strcpy (theResultsYearlyCWGrid, baseFileName);
	strcat (theResultsYearlyCWGrid, tagYCWG);
	
	strcpy (theResultsPersist, baseFileName);
	strcat (theResultsPersist, tagPers);

	strcpy (theResultsList, baseFileName);
	strcat (theResultsList, tagList);

	theTrial = 0;
	
	theStationID = 0.0;
	theStationYR = 0;

	theRainHeader = false;
	theDLCHeader = false;
	theYCCHeader = false;
	theYLCHeader = false;
	theYLGHeader = false;
    thePerHeader = false;
	thePersistence = true;
	
	fileInput == 4 ? theFilebatch = true : theFilebatch=false;
}

RESULTS::~RESULTS()
{}

/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
*/

void RESULTS::setTrial (int trial)
{
	theTrial = trial; thePersistence = true;
}

void RESULTS::setPointers (RAIN* p_Rain, GRID* p_Grid)
{
	pRAIN = p_Rain; pGRID = p_Grid;
	theGridLengthC = pGRID->getNCells(1);
	theGridLengthR = pGRID->getNCells(2);
	theGridSize = float(theGridLengthC * theGridLengthR); // changed 2006-01-30
}

/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
*/

void RESULTS::copyDailyValues (int day)
{
  SOIL* pSoil;
  for (int col = 0; col < theGridLengthC; col++)
  {
    for (int row = 0; row < theGridLengthR; row++)
    {
	  pSoil = pGRID->getNbrGPtr(col,row);
	  theDailyCell.psiO[col][row] = pSoil->getPotentialO();
	  theDailyCell.psiA1[col][row] = pSoil->getPotentialA1();
	  theDailyCell.psiA2[col][row] = pSoil->getPotentialA2();
	  theDailyCell.psiA3[col][row] = pSoil->getPotentialA3();
	  theDailyCell.psiA4[col][row] = pSoil->getPotentialA4();
	  theDailyCell.watO[col][row] = pSoil->getVolWaterO();
	  theDailyCell.watA1[col][row] = pSoil->getVolWaterA1();
	  theDailyCell.watA2[col][row] = pSoil->getVolWaterA2();
	  theDailyCell.watA3[col][row] = pSoil->getVolWaterA3();
	  theDailyCell.watA4[col][row] = pSoil->getVolWaterA4();
	  theDailyCell.watC[col][row] = pSoil->getWaterC();
	  theDailyCell.runoff[col][row] = pSoil->getRunoff();
	  theDailyCell.evtr[col][row] = pSoil->getOAWaterET();
	  theDailyCell.moist5[col][row] = int(theDailyCell.psiA1[col][row] >= -5.0 || 
		                                  theDailyCell.psiA2[col][row] >= -5.0 || 
		                                  theDailyCell.psiA3[col][row] >= -5.0 ||
		                                  theDailyCell.psiA4[col][row] >= -5.0 );
	  theDailyCell.moist3[col][row] = int(theDailyCell.psiA1[col][row] >= -3.0 || 
		                                  theDailyCell.psiA2[col][row] >= -3.0 || 
							              theDailyCell.psiA3[col][row] >= -3.0 ||
		                                  theDailyCell.psiA4[col][row] >= -3.0 );
	  theDailyCell.moist2[col][row] = int(theDailyCell.psiA1[col][row] >= -1.5 || 
		                                  theDailyCell.psiA2[col][row] >= -1.5 || 
		                                  theDailyCell.psiA3[col][row] >= -1.5 ||
		                                  theDailyCell.psiA4[col][row] >= -1.5 );
	  theDailyCell.S[col][row] = pSoil->getPPlant()->getASpecies();
	  theDailyCell.mass[col][row] = pSoil->getPPlant()->getMass();
	  if(day==0) theDailyCell.st_cr[col][row]=0.0;
	  if(pSoil->getPPlant()->getMass()>theDailyCell.st_cr[col][row]) // test st.crop
		  theDailyCell.st_cr[col][row] = pSoil->getPPlant()->getMass(); // test st.crop
	  theDailyCell.seedl[col][row] = int(pSoil->getPPlant()->isSeedling());
	  theDailyCell.indiv[col][row] = int(pSoil->getPPlant()->isEstablished());
	  theDailyCell.mature[col][row] = int(pSoil->getPPlant()->isMature());
	}
  }
  calcDailyValuesAcrossLattice(day);
  calcAnnualValuesForEachCell(day);
}
	  
/* mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm */

void RESULTS::calcDailyValuesAcrossLattice (int day)
{
  float sumOPsi  = 0.0;
  float sumA1Psi = 0.0;
  float sumA2Psi = 0.0;
  float sumA3Psi = 0.0;
  float sumA4Psi = 0.0;
  float sumWaterO = 0.0;
  float sumWaterA1 = 0.0;
  float sumWaterA2 = 0.0;
  float sumWaterA3 = 0.0;
  float sumWaterA4 = 0.0;
  float sumWaterC = 0.0;
  float sumRunoff = 0.0;
  float sumRunoffE = 0.0;
  float sumWaterOAET = 0.0;
  long sumMoistDays5 = 0;
  long sumMoistDays3 = 0;
  long sumMoistDays2 = 0;
  float sumMass = 0.0;
  float sumStCr = 0.0;
  long sumSeedl = 0;
  long  sumIndiv = 0;
	long sumMature = 0;
  
  for (int col = 0; col < theGridLengthC; col++)
  {
    for (int row = 0; row < theGridLengthR; row++)
    {
      sumOPsi += theDailyCell.psiO[col][row];
      sumA1Psi += theDailyCell.psiA1[col][row];
      sumA2Psi += theDailyCell.psiA2[col][row];
      sumA3Psi += theDailyCell.psiA3[col][row];
      sumA4Psi += theDailyCell.psiA4[col][row];
      sumWaterO +=  theDailyCell.watO[col][row];
      sumWaterA1 += theDailyCell.watA1[col][row];
      sumWaterA2 += theDailyCell.watA2[col][row];
      sumWaterA3 += theDailyCell.watA3[col][row];
      sumWaterA4 += theDailyCell.watA4[col][row];
      sumWaterC += theDailyCell.watC[col][row];
	  sumRunoff += theDailyCell.runoff[col][row];
      sumWaterOAET += theDailyCell.evtr[col][row];
	  sumMoistDays5 += theDailyCell.moist5[col][row];
	  sumMoistDays3 += theDailyCell.moist3[col][row];
	  sumMoistDays2 += theDailyCell.moist2[col][row];
	  sumMass += theDailyCell.mass[col][row];
	  sumStCr += theDailyCell.st_cr[col][row];
	  sumSeedl += theDailyCell.seedl[col][row];
	  sumIndiv += theDailyCell.indiv[col][row];
		theIndivDay[day]+=theDailyCell.indiv[col][row];
	  sumMature += theDailyCell.mature[col][row];
	}
	sumRunoffE += theDailyCell.runoff[col][theGridLengthR-1];
  }
  
  theMDaily.DRain[day] = pRAIN->getRain(day);
  theMDaily.DMPotentialO[day] = sumOPsi / float(theGridSize);
  theMDaily.DMPotentialA1[day] = sumA1Psi / float(theGridSize);
  theMDaily.DMPotentialA2[day] = sumA2Psi / float(theGridSize);
  theMDaily.DMPotentialA3[day] = sumA3Psi / float(theGridSize);
  theMDaily.DMPotentialA4[day] = sumA4Psi / float(theGridSize);
  theMDaily.DMWaterO[day] = sumWaterO / float(theGridSize);
  theMDaily.DMWaterA1[day] = sumWaterA1 / float(theGridSize);
  theMDaily.DMWaterA2[day] = sumWaterA2 / float(theGridSize);
  theMDaily.DMWaterA3[day] = sumWaterA3 / float(theGridSize);
  theMDaily.DMWaterA4[day] = sumWaterA4 / float(theGridSize);
  theMDaily.DMWaterC[day] = sumWaterC / float(theGridSize);
  theMDaily.DMRunoff[day] = sumRunoff / float(theGridSize);
  theMDaily.DMRunoffE[day] = sumRunoffE / float(theGridLengthC);
  theMDaily.DMEvTr[day] = sumWaterOAET / float(theGridSize);
  theMDaily.DMNbrMoistDays5[day] = sumMoistDays5 / float(theGridSize);
  theMDaily.DMNbrMoistDays3[day] = sumMoistDays3 / float(theGridSize);
  theMDaily.DMNbrMoistDays2[day] = sumMoistDays2 / float(theGridSize);
  theMDaily.DMMassGPM2[day] = sumMass /float(theGridSize * cellArea) * 10.0;
  theMDaily.DMStCrGPM2[day] = sumStCr /float(theGridSize * cellArea) * 10.0;
  theMDaily.DSeedlPM2[day] = float(sumSeedl /float(theGridSize * cellArea) * 10000.0);
  theMDaily.DIndivPM2[day] = float(sumIndiv /float(theGridSize * cellArea) * 10000.0);
  theMDaily.DMaturePM2[day] =  float(sumMature /float(theGridSize * cellArea) * 10000.0);
}

/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
*/

void RESULTS::calcAnnualValuesForEachCell(int day)
{
  for (int col = 0; col < theGridLengthC; col++)
  {
    for (int row = 0; row < theGridLengthR; row++)
    {	  
      theAnnualSumCell.psiO[col][row] += theDailyCell.psiO[col][row];
      theAnnualSumCell.psiA1[col][row] += theDailyCell.psiA1[col][row];
      theAnnualSumCell.psiA2[col][row] += theDailyCell.psiA2[col][row];
      theAnnualSumCell.psiA3[col][row] += theDailyCell.psiA3[col][row];
      theAnnualSumCell.psiA4[col][row] += theDailyCell.psiA4[col][row];
      theAnnualSumCell.watO[col][row] += theDailyCell.watO[col][row];
      theAnnualSumCell.watA1[col][row] += theDailyCell.watA1[col][row];
      theAnnualSumCell.watA2[col][row] += theDailyCell.watA2[col][row];
      theAnnualSumCell.watA3[col][row] += theDailyCell.watA3[col][row];
      theAnnualSumCell.watA4[col][row] += theDailyCell.watA4[col][row];
      theAnnualSumCell.watC[col][row] += theDailyCell.watC[col][row];
      theAnnualSumCell.runoff[col][row] += theDailyCell.runoff[col][row];
      theAnnualSumCell.evtr[col][row] += theDailyCell.evtr[col][row];
	  if(theDailyCell.moist5[col][row] == 1)
		// store the accumulated number of wet days in a temporary variable
		theNbrOfMoistDays5[col][row] ++;
	  if(theDailyCell.moist5[col][row] == 0 || day == days_in_year-1) {
		  // if the new wet period is longer than the old one
		if (theNbrOfMoistDays5[col][row] > theAnnualSumCell.moist5[col][row])
			// store the new one
		  theAnnualSumCell.moist5[col][row] = theNbrOfMoistDays5[col][row];
		  // and reset the temporary variable
		theNbrOfMoistDays5[col][row] = 0;	 
	  }
	  if(theDailyCell.moist3[col][row] == 1)
		theNbrOfMoistDays3[col][row] ++;
	  if(theDailyCell.moist5[col][row] == 0 || day == days_in_year-1) {
		if (theNbrOfMoistDays3[col][row] > theAnnualSumCell.moist3[col][row])
		  theAnnualSumCell.moist3[col][row] = theNbrOfMoistDays3[col][row];
		theNbrOfMoistDays3[col][row] = 0;	 
	  }
	  if(theDailyCell.moist2[col][row] == 1)
		theNbrOfMoistDays2[col][row] ++;
	  if(theDailyCell.moist5[col][row] == 0 || day == days_in_year-1) {
		if (theNbrOfMoistDays2[col][row] > theAnnualSumCell.moist2[col][row])
		  theAnnualSumCell.moist2[col][row] = theNbrOfMoistDays2[col][row];
		theNbrOfMoistDays2[col][row] = 0;	 
	  }
	  if(theDailyCell.mass[col][row] > theAnnualSumCell.mass[col][row]) 
		theAnnualSumCell.mass[col][row] = theDailyCell.mass[col][row];
	  if(theDailyCell.seedl[col][row]) 
		  theAnnualSumCell.seedl[col][row] = true;	  
	  if(theDailyCell.indiv[col][row])
		theAnnualSumCell.indiv[col][row] = true;
	  if(theDailyCell.mature[col][row])
		theAnnualSumCell.mature[col][row] = true;
    }
    theAnnualSumCell.runoffE[col] += theDailyCell.runoff[col][theGridLengthR-1];
  }
}

void RESULTS::zeroAnnualSums (void)
{
  for (int col = 0; col < theGridLengthC; col++)
  {
    for (int row = 0; row < theGridLengthR; row++)
    {	  
	  theNbrOfMoistDays5[col][row] = 0;
	  theNbrOfMoistDays3[col][row] = 0;
	  theNbrOfMoistDays2[col][row] = 0;
      theAnnualSumCell.psiO[col][row] = 0.0;
      theAnnualSumCell.psiA1[col][row] = 0.0;
      theAnnualSumCell.psiA2[col][row] = 0.0;
      theAnnualSumCell.psiA3[col][row] = 0.0;
      theAnnualSumCell.psiA4[col][row] = 0.0;
      theAnnualSumCell.watO[col][row] = 0.0;
      theAnnualSumCell.watA1[col][row] = 0.0;
      theAnnualSumCell.watA2[col][row] = 0.0;
      theAnnualSumCell.watA3[col][row] = 0.0;
      theAnnualSumCell.watA4[col][row] = 0.0;
      theAnnualSumCell.watC[col][row] = 0.0;
      theAnnualSumCell.runoff[col][row] = 0.0;
      theAnnualSumCell.evtr[col][row] = 0.0;
	  theAnnualSumCell.moist5[col][row] = 0;
	  theAnnualSumCell.moist3[col][row] = 0;
	  theAnnualSumCell.moist2[col][row] = 0;
	  theAnnualSumCell.mass[col][row] = 0.0;
	  theAnnualSumCell.seedl[col][row] = false;
	  theAnnualSumCell.indiv[col][row] = false;	
	  theAnnualSumCell.mature[col][row] = false;
	}
    theAnnualSumCell.runoffE[col]  = 0.0;
  }
	for (short d=0; d<days_in_year; d++)
		theIndivDay[d]=0;
  
}

/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
*/

void RESULTS::calcMeanAnnualValues (void)
{
  float sumPsiO  = 0.0;
  float sumPsiA1 = 0.0;
  float sumPsiA2 = 0.0;
  float sumPsiA3 = 0.0;
  float sumPsiA4 = 0.0;
  float sumWaterO = 0.0;
  float sumWaterA1 = 0.0;
  float sumWaterA2 = 0.0;
  float sumWaterA3 = 0.0;
  float sumWaterA4 = 0.0;
  float sumWaterC = 0.0;
  float sumRunoff = 0.0;
  float sumRunoffE = 0.0;
  float sumWaterOAET = 0.0;
  long sumMoistDays5 = 0;
  long sumMoistDays3 = 0;
  long sumMoistDays2 = 0;
  long  sumIndiv = 0;
  float sumMass = 0.0;
  long sumSeedl = 0;
  long sumMature = 0;
  long sumSeeds = 0;
  long sumSeedbank = 0;
  
  for (int col = 0; col < theGridLengthC; col++)
  {
    for (int row = 0; row < theGridLengthR; row++)
    {
      sumPsiO += theAnnualSumCell.psiO[col][row];
      sumPsiA1 += theAnnualSumCell.psiA1[col][row];
      sumPsiA2 += theAnnualSumCell.psiA2[col][row];
      sumPsiA3 += theAnnualSumCell.psiA3[col][row];
      sumPsiA4 += theAnnualSumCell.psiA4[col][row];
      sumWaterO +=  theAnnualSumCell.watO[col][row];
      sumWaterA1 += theAnnualSumCell.watA1[col][row];
      sumWaterA2 += theAnnualSumCell.watA2[col][row];
      sumWaterA3 += theAnnualSumCell.watA3[col][row];
      sumWaterA4 += theAnnualSumCell.watA4[col][row];
      sumWaterC += theAnnualSumCell.watC[col][row];
	  sumRunoff += theAnnualSumCell.runoff[col][row];
      sumWaterOAET += theAnnualSumCell.evtr[col][row];
	  sumMoistDays5 += theAnnualSumCell.moist5[col][row];
	  sumMoistDays3 += theAnnualSumCell.moist3[col][row];
	  sumMoistDays2 += theAnnualSumCell.moist2[col][row];
	  sumMass += theAnnualSumCell.mass[col][row];
	  sumSeedl += theAnnualSumCell.seedl[col][row];
	  sumIndiv += theAnnualSumCell.indiv[col][row];
	  sumMature += theAnnualSumCell.mature[col][row];
	  sumSeeds += pGRID->getNbrGPtr(col,row)->getPPlant()->getAllSeeds();
	  sumSeedbank += pGRID->getNbrGPtr(col,row)->getPSeedbank()->getNumber();
	}
	sumRunoffE += theAnnualSumCell.runoffE[col];
  }
  
  theMAnnual.ARain =  pRAIN->getAnnualRain();
  theMAnnual.APotentialO = sumPsiO / float(theGridSize * days_in_year);
  theMAnnual.APotentialA1 = sumPsiA1 / float(theGridSize * days_in_year);
  theMAnnual.APotentialA2 = sumPsiA2 / float(theGridSize * days_in_year);
  theMAnnual.APotentialA3 = sumPsiA3 / float(theGridSize * days_in_year);
  theMAnnual.APotentialA4 = sumPsiA4 / (theGridSize * days_in_year);
  theMAnnual.AWaterO = sumWaterO / float(theGridSize * days_in_year);
  theMAnnual.AWaterA1 = sumWaterA1 / float(theGridSize * days_in_year);
  theMAnnual.AWaterA2 = sumWaterA2 / float(theGridSize * days_in_year);
  theMAnnual.AWaterA3 = sumWaterA3 / float(theGridSize * days_in_year);
  theMAnnual.AWaterA4 = sumWaterA4 / float(theGridSize * days_in_year);
  theMAnnual.AWaterC = sumWaterC / float(theGridSize * days_in_year);
  theMAnnual.ARunoff = sumRunoff / float(theGridSize * days_in_year);
  theMAnnual.ARunoffE = sumRunoffE / float(theGridLengthC);
  theMAnnual.AEvTr = sumWaterOAET / float(theGridSize);
  theMAnnual.AMoist5 = sumMoistDays5 / float(theGridSize);
  theMAnnual.AMoist3 = sumMoistDays3 / float(theGridSize);
  theMAnnual.AMoist2 = sumMoistDays2 / float(theGridSize);
  theMAnnual.AMassGPM2 = sumMass /float(theGridSize * cellArea) * 10.0;
  theMAnnual.ASeedlPM2 = float(sumSeedl) /float(theGridSize * cellArea) * 1.0E4;
  theMAnnual.AIndivPM2 = float(sumIndiv) /float(theGridSize * cellArea) * 1.0E4;
  theMAnnual.AdIndivPM2 = float(MK_max(theIndivDay, days_in_year)) /float(theGridSize * cellArea) * 1.0E4;
  theMAnnual.AMaturePM2 = float(sumMature) /float(theGridSize * cellArea) * 1.0E4;
  theMAnnual.ASeedsPM2 = float (sumSeeds)/float(theGridSize * cellArea) * 1.0E4;
  theMAnnual.ASeedbankPM2 = float (sumSeedbank)/float(theGridSize * cellArea) * 1.0E4;
}

/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
_saveParameters_
 */
void RESULTS::saveParameters (CLIMATE* pCLIMATE, SOILPARAMETERS* pSoilP, SEED_PARAMETERS* pSeedP, PLANT_PARAMETERS* pPlantP)
{

  time_t currentTime;
  time (&currentTime);
  
  ofstream ParameterDocu;
  ParameterDocu.open (theResultsList, std::ios::app);
  
  ParameterDocu << "Date and time: " << ctime(&currentTime) << "\n\n" << endl;
  ParameterDocu << "Version: 2.7.0\n\n" << endl;
  pGRID->pP->documentation(theResultsList);
  if (!theFilebatch)
  {	pCLIMATE->documentation(theResultsList);
	pSoilP->documentation(theResultsList);
	pSeedP->documentation(theResultsList);
	pPlantP->documentation(theResultsList);
  }
  ParameterDocu << "\n--------------------------------------------\n\n" << endl;
  
  ParameterDocu.close();
  }

/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
*/

void RESULTS::saveRainDocumentation (int year)
{
  if (!theFilebatch)
  {
  ofstream RainDocu;
  RainDocu.open(theResultsList, std::ios::app);
  
  if (theRainHeader == false) {
	RainDocu
	<< "trial"  << "\t"
	<< "year"	  << "\t"
	<< "stationID"	<< "\t"
	<< "stationYr" <<"\t"
	<< "rain (mm/yr)"
	<< endl;
	theRainHeader = true;
  }
  
  RainDocu
	<< theTrial					<< "\t"
	<< year						<< "\t"
	<< pRAIN->getStationID()	<< "\t"
	<< pRAIN->getStationYR()	<< "\t"
	<< pRAIN->getAnnualRain()
	<< endl;
  
  RainDocu.close();
  }
}

/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
*/

bool RESULTS::saveDailyValues (int year)
{
  if(!theFilebatch)// if(theFilebatch)
  {
	ofstream DLC;
	DLC.open(theResultsDailyLattCol, std::ios::app);
	
	if (theDLCHeader == false) {
	  DLC 
	  << "trial"	<< "\t"
      << "year"			<< "\t"
	  << "day"			<< "\t"
	  << "rain.mm"		<< "\t"
	  << "O.MPa"		<< "\t"
	  << "A1.MPa"		<< "\t"
	  << "A2.MPa"		<< "\t"
	  << "A3.MPa"		<< "\t"
	  << "A4.MPa"		<< "\t"
	  << "O.mm"  << "\t"
	  << "A1.mm"  << "\t"
	  << "A2.mm"  << "\t"
	  << "A3.mm"  << "\t"
	  << "A4.mm"  << "\t"
	  << "C.mm"  << "\t"
      << "ro.mm" 	<< "\t"
      << "roE.mm" 	<< "\t"
	  << "OAET.mm" << "\t"
	  << "moistD5" << "\t"
	  << "moistD3" << "\t"
	  << "moistD1.5" << "\t"
      << "mass.g.m2"<< "\t"
	  << "StCr.g.m2"<< "\t"
	  << "seedl.m2"	<< "\t"
	  << "ind.m2"	<< "\t"
	  << "fl.ind.m2"
	  << endl;
	  theDLCHeader = true;
	}
	
  DLC.setf(ios_base::fixed, ios_base::floatfield); // see Stroustrup p. 628
	for (int day = 0; day < days_in_year; day++) {	
		DLC.precision(1);
    DLC 
	  << theTrial << "\t"
      << year << "\t"
	  << day << "\t"
	  << theMDaily.DRain[day]	<< "\t";
	DLC.precision(2);
	DLC
	  << theMDaily.DMPotentialO[day] << "\t"
	  << theMDaily.DMPotentialA1[day]	<< "\t"
	  << theMDaily.DMPotentialA2[day]	<< "\t" 
	  << theMDaily.DMPotentialA3[day] 	<< "\t"
	  << theMDaily.DMPotentialA4[day] 	<< "\t";
	DLC.precision(1);
	DLC
	  << theMDaily.DMWaterO[day] << "\t"
	  << theMDaily.DMWaterA1[day] << "\t"
	  << theMDaily.DMWaterA2[day] << "\t"
	  << theMDaily.DMWaterA3[day] << "\t"
	  << theMDaily.DMWaterA4[day] << "\t"
	  << theMDaily.DMWaterC[day] << "\t"
	  << theMDaily.DMRunoff[day] 	<< "\t"
	  << theMDaily.DMRunoffE[day] 	<< "\t"
	  << theMDaily.DMEvTr[day] << "\t";
    DLC.precision(0);
    DLC
	  << theMDaily.DMNbrMoistDays5[day] << "\t"
	  << theMDaily.DMNbrMoistDays3[day] << "\t"
	  << theMDaily.DMNbrMoistDays2[day] << "\t";
    DLC.precision(3);
    DLC
	  << theMDaily.DMMassGPM2[day]	<< "\t"
	<< theMDaily.DMStCrGPM2[day]	<< "\t";
    DLC.precision(0);
    DLC
	  << theMDaily.DSeedlPM2[day]	<< "\t"
	<< theMDaily.DIndivPM2[day]	<< "\t"
	  << theMDaily.DMaturePM2[day]
	  << std::endl;
    DLC.precision(6);
	}
  DLC.setf(ios_base::fmtflags(0), ios_base::floatfield); // reset format to default

	DLC.close();
	
	if (SEEDS::getNumberOfAllSeeds() == 0)
      thePersistence = false;
	return thePersistence;
  }
  else
	return true;
}


/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
*/
int nParameterCombos = 0; // global variable

bool RESULTS::saveMeanYearlyValues (int year)
{
  
  if((theFilebatch && year>2) || !theFilebatch)
  {
  float	sumSeedbank = double(SEEDS::getNumberOfAllSeeds()) / (theGridSize * cellArea) * 10000.0;
  
	ofstream YLC;
	YLC.open(theResultsYearlyLattCol, std::ios::app);
	
	if (theYLCHeader == false && nParameterCombos == 1) {
	  YLC << "ID" << "\t"
		  << "trial"	<< "\t"
		  << "year"		<< "\t";
	  YLC
	  << "rain.mm"		<< "\t"
	  << "O.MPa"		<< "\t"
	  << "A1.MPa"		<< "\t"
	  << "A2.MPa"		<< "\t"
	  << "A3.MPa"		<< "\t"
	  << "A4.MPa"		<< "\t"
	  << "O.mm"  << "\t"
	  << "A1.mm"  << "\t"
	  << "A2.mm"  << "\t"
	  << "A3.mm"  << "\t"
	  << "A4.mm"  << "\t"
	  << "C.mm"  << "\t";
	  YLC
      << "ro.mm" 	<< "\t"
      << "roE.mm" 	<< "\t"
	  <<  "OAET.mm" << "\t"
	  << "moistD5" << "\t"
	  << "moistD3" << "\t"
	  << "moistD1.5" << "\t"
		<< "mass.g.m2" << "\t"
		<< "seedl.m2" << "\t"
	  << "ind.m2"	<< "\t"
	  << "d.ind.m2" << "\t"
	  << "fl.ind.m2" << "\t"
	  << "seeds.m2" << "\t"
	  << "seedbank.m2"
	  << std::endl;
		theYLCHeader = true;
	}
	
	YLC.setf(ios_base::fixed, ios_base::floatfield); // see Stroustrup p. 628
    YLC.precision(0);
	YLC << theSimID << "\t";
	YLC << theTrial << "\t"
		<< year << "\t"
	  << theMAnnual.ARain << "\t";
	YLC.precision(1);
	YLC <<
	theMAnnual.APotentialO << "\t" <<
	theMAnnual.APotentialA1 << "\t" <<
	theMAnnual.APotentialA2 << "\t" <<
	theMAnnual.APotentialA3 << "\t" <<
	theMAnnual.APotentialA4 << "\t" <<
	theMAnnual.AWaterO << "\t" <<
	theMAnnual.AWaterA1 << "\t" <<
	theMAnnual.AWaterA2 << "\t" <<
	theMAnnual.AWaterA3 << "\t" <<
	theMAnnual.AWaterA4 << "\t" <<
	theMAnnual.AWaterC << "\t";
	YLC.precision(2);
	YLC <<
	theMAnnual.ARunoff << "\t";
	  YLC.precision(1);
	YLC <<
	theMAnnual.ARunoffE << "\t" << 
	theMAnnual.AEvTr << "\t"<<
	theMAnnual.AMoist5 << "\t" <<
	  theMAnnual.AMoist3 << "\t" <<
	  theMAnnual.AMoist2 << "\t" <<
	  theMAnnual.AMassGPM2 << "\t";
	YLC.precision(0);
	YLC <<
	theMAnnual.ASeedlPM2 << "\t" <<
	theMAnnual.AIndivPM2 << "\t" <<
	theMAnnual.AdIndivPM2 << "\t" <<
	theMAnnual.AMaturePM2 << "\t" <<
	theMAnnual.ASeedsPM2 << "\t" <<
	theMAnnual.ASeedbankPM2
	<< std::endl;
	YLC.setf(ios_base::fmtflags(0), ios_base::floatfield); // reset format to default

	YLC.close();
    
    if (sumSeedbank == 0.0)
      thePersistence = false;
    return thePersistence;
  }
  else
	return true;
}


/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
*/

void RESULTS::saveYearlyLattAsGrid (void)
{
	ofstream YLG;
	YLG.open(theResultsYearlyLattGrid, std::ios::app);

	if (theYLGHeader == false)
	{
		YLG << "Mass per individual" // adjust 
											 //  when you change the output below
			<< endl;
		theYLGHeader = true;
	}

	for (int row = 0; row < theGridLengthR; row++)
	{
		for (int col = 0; col < theGridLengthC; col++)
		{
//			YLG << pGRID->getNbrGPtr(col,row)->getPSeedbank()->getNumber();
//			YLG << pGRID->getNbrGPtr(col,row)->getPPlant()->getNewSeeds();
//			YLG << pGRID->getNbrGPtr(col,row)->getPPlant()->getAllSeeds();
			YLG << theAnnualSumCell.mass[col][row];

			if (col < theGridLengthC-1)
				YLG << "\t";
		}	
		YLG << std::endl;
	}
	YLG.close();	
}
/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
*/

void RESULTS::saveYearlyRunoffAsGrid (void)
{
	ofstream YLG;
	YLG.open(theResultsYearlyRoGrid, std::ios::app);

	for (int row = 0; row < theGridLengthR; row++)
	{
		for (int col = 0; col < theGridLengthC; col++)
		{
      YLG << theAnnualSumCell.runoff[col][row]; 
			if (col < theGridLengthC-1)
				YLG << "\t";
		}	
		YLG << std::endl;
	}
	YLG.close();	
}
//---------------------------------------------------
void RESULTS::saveYearlyPotA1AsGrid (void)
{
	ofstream YLG;
	YLG.open(theResultsYearlyA1Grid, std::ios::app);

	for (int row = 0; row < theGridLengthR; row++)
	{
		for (int col = 0; col < theGridLengthC; col++)
		{
      YLG <<  theAnnualSumCell.psiA1[col][row]/float(days_in_year); 
			if (col < theGridLengthC-1)
				YLG << "\t";
		}	
		YLG << std::endl;
	}
	YLG.close();	
}
//---------------------------------------------------
void RESULTS::saveYearlyPotA2AsGrid (void)
{
	ofstream YLG;
	YLG.open(theResultsYearlyA2Grid, std::ios::app);

	for (int row = 0; row < theGridLengthR; row++)
	{
		for (int col = 0; col < theGridLengthC; col++)
		{
      YLG << theAnnualSumCell.psiA2[col][row]/float(days_in_year); 
			if (col < theGridLengthC-1)
				YLG << "\t";
		}	
		YLG << std::endl;
	}
	YLG.close();	
}
//---------------------------------------------------
void RESULTS::saveYearlyPotA3AsGrid (void)
{
	ofstream YLG;
	YLG.open(theResultsYearlyA3Grid, std::ios::app);

	for (int row = 0; row < theGridLengthR; row++)
	{
		for (int col = 0; col < theGridLengthC; col++)
		{
      YLG << theAnnualSumCell.psiA3[col][row]/float(days_in_year); 
			if (col < theGridLengthC-1)
				YLG << "\t";
		}	
		YLG << std::endl;
	}
	YLG.close();	
}
//---------------------------------------------------
void RESULTS::saveYearlyPotA4AsGrid (void)
{
	ofstream YLG;
	YLG.open(theResultsYearlyA4Grid, std::ios::app);

	for (int row = 0; row < theGridLengthR; row++)
	{
		for (int col = 0; col < theGridLengthC; col++)
		{
      YLG << theAnnualSumCell.psiA4[col][row]/float(days_in_year); 
			if (col < theGridLengthC-1)
				YLG << "\t";
		}	
		YLG << std::endl;
	}
	YLG.close();	
}
//---------------------------------------------------
void RESULTS::saveYearlyCWaterAsGrid (void)
{
	ofstream YLG;
	YLG.open(theResultsYearlyCWGrid, std::ios::app);

	for (int row = 0; row < theGridLengthR; row++)
	{
		for (int col = 0; col < theGridLengthC; col++)
		{
      YLG << theAnnualSumCell.watC[col][row]/float(days_in_year); 
			if (col < theGridLengthC-1)
				YLG << "\t";
		}	
		YLG << std::endl;
	}
	YLG.close();	
}

/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
*/

bool RESULTS::savePersistence (int maxYears, int year)
{
	long nSB = SEEDS::getNumberOfAllSeeds(); // total sum of all grid cells!
	
	if ((nSB == 0 && thePersistence == true) || 
		(maxYears == year+1 && thePersistence == true))
	{
		ofstream SBPersistence;
		
		SBPersistence.open(theResultsPersist, std::ios::app);

    if (thePerHeader == false)
    {
      SBPersistence << "Persistence" << endl;
      thePerHeader = true;
    }
		
		if (nSB == 0) {
			SBPersistence << year << std::endl;
			thePersistence = false;
		}
		else
			SBPersistence << year+1 << std::endl;
		
		SBPersistence.close();
	}
	
	return thePersistence;
}

void RESULTS::saveVegCover (void)
{
  if(theFilebatch)
  {
  ofstream ParameterDocu;
  ParameterDocu.open (theResultsList, std::ios::app);
    for (int row = 0; row < theGridLengthR; row++)
    {
      ParameterDocu << "  v ";
      for (int col = 0; col < theGridLengthC; col++)
        switch(pGRID->getNbrGPtr(col,row)->getVegetation())
				{ case hus:		ParameterDocu << "R "; break;
					case shrub: ParameterDocu << "T "; break;
					case herb:  ParameterDocu << "i "; break;
					default:		ParameterDocu << ". ";
				}
      ParameterDocu << endl;
    }
    ParameterDocu << endl;
}
}
