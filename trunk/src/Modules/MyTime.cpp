/*
 *  MyTime.cpp
 *  intraspecific
 *
 *  Created by Martin Köchy on Thu Feb 06 2003.
 *  Copyright (c) 2003 __MyCompanyName__. All rights reserved.
 *
 */

//#include <vcl.h>			// for Borland C++ Builder
//#pragma hdrstop			// for Borland C++ Builder

#include <iostream>
#include <fstream>
#include "Results.h"
#include "Rain.h"
#include "Grid.h"
#include "Plant.h"
#include "MyTime.h"

/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
*/

TIME::TIME  ( RESULTS* pResults,
              int outputDetail,
			  RAINPARAMETERS* pRainP, CLIMATE* p_CLIMATE, GRIDPARAMETERS* pGridP, 
			  SOILPARAMETERS* pSoilP, SEED_PARAMETERS* pSeedP, PLANT_PARAMETERS* pPlantP, 
			  bool documented
			  ) : pi(3.1415926)
{
  pRESULTS = pResults;
  theOutputDetail = outputDetail;
				
  pCLIMATE = p_CLIMATE;
  if (pRainP->isReGen)
	pRAIN = new ReGen (this, pRainP);
  else
	pRAIN = new PreFile (this, pRainP);
  pGRID = new GRID (this, pGridP, pRESULTS, pSoilP, pSeedP, pPlantP, pCLIMATE);
  pRESULTS->setPointers(pRAIN, pGRID);
  if (!documented) pRESULTS->saveParameters(pCLIMATE, pSoilP, pSeedP, pPlantP);
  pRESULTS->saveVegCover();
  				
  theYear = 0;
  theDay = 0;
  theTemperatureIndex = 0.0;	
}

TIME::~TIME()
{
  delete pRAIN; // no need to set pointer to null in destructor
  delete pGRID;
}

/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm

_years_loop_

Simple encapsulation function for everything that happens within one year.

 */

void TIME::years_loop (int run_years)
{
  bool loop = true;
  
  for (theYear = 0; theYear < run_years; theYear++)
  {
	SEEDS::zeroAllSeeds(); // just a precaution...
	pRESULTS->zeroAnnualSums();	
	pGRID->yearlyReset();
	
	informUser(theYear, run_years);
	pRAIN->drawYear();
	days_loop();		// each year
	
	pRESULTS->calcMeanAnnualValues();
	loop = getResults(run_years);	// after each year
	if (loop == false)// check if population is extinct
	  theYear = run_years; // stop loop
	if(theYear%10==3) pRESULTS->saveVegCover();
  }
}

/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm

_days_loop_

Encapsulation function for everything that happens within one day.

 */
 
void TIME::days_loop (void)
{
  for (theDay = 0; theDay < days_in_year; theDay++)
  {
		theTemperatureIndex = cos( (theDay+pCLIMATE->getColdestDay() )/float(days_in_year) * 2.0*pi );
		theTemperature = theTemperatureIndex * pCLIMATE->getRangeT() + pCLIMATE->getMeanT();
		
		float rainfall =  pRAIN->getRain(theDay);
		pGRID->updateGrid(theDay, theTemperatureIndex, theTemperature, rainfall);
		  pRESULTS->copyDailyValues(theDay);
  }
}

/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
_informUser_
*/
void TIME::informUser(int year, int maxYr)
{
  if (maxYr <= 10)
	std::cout << " Now doing year " << year << std::endl;
  else
	if (theOutputDetail!=1)
	  if (year%10 == 0)
		std::cout << " Now doing years " << year << "-" << (year+9>maxYr?maxYr:year+9) << std::endl;
}
/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
calculated in days_loop. Minimum on 15 January. Range [-1,1]
*/
 
float TIME::getTemperatureIndex (void)
{
  return theTemperatureIndex;
}

/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
calculated in days_loop. Minimum on 15 January.
*/
 
float TIME::getTemperature (void)
{
  return theTemperature;
}

/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm

_getResults_

This function controls which files are produced.

*/

bool TIME::getResults (int maxYears)
{
  bool keepGoing = true;
  
  pRESULTS->saveRainDocumentation(theYear); // for all
  keepGoing = pRESULTS->saveMeanYearlyValues(theYear);
  
  if (theOutputDetail)	// if only one trial, produce detailed output
  {
	  if (maxYears <= 5) {
		pRESULTS->saveDailyValues(theYear);
			pRESULTS->saveYearlyLattAsGrid();
			pRESULTS->saveYearlyRunoffAsGrid();
			pRESULTS->saveYearlyPotA1AsGrid();
			pRESULTS->saveYearlyPotA2AsGrid();
			pRESULTS->saveYearlyPotA3AsGrid();
			pRESULTS->saveYearlyPotA4AsGrid();
			pRESULTS->saveYearlyCWaterAsGrid();
	  }
  }
  
  if (theOutputDetail>1)	// if many trials, produce condensed output
  {
	pRESULTS->saveDailyValues(theYear);
//  keepGoing = pRESULTS->savePersistence(maxYears, theYear);
  }
  
  return keepGoing; 
}

/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
*/
int TIME::getYear (void) const
{
  return theYear;
}

/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
*/
int TIME::getDay (void) const
{
  return theDay;
}
/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
*/

