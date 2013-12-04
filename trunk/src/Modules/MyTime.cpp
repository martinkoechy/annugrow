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
              int trials,
			  RAINPARAMETERS* pRainP, CLIMATE* p_CLIMATE, GRIDPARAMETERS* pGridP, 
			  SOILPARAMETERS* pSoilP, SEED_PARAMETERS* pSeedP, PLANT_PARAMETERS* pPlantP, 
			  bool documented
			  ) : pi(3.1415926)
{
  pRESULTS = pResults;
  theTrials = trials;
				
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
	pRAIN->drawYear(); // go to function to choose random or ordered sequence
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
	//if (theTrials)
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
  
		pRESULTS->saveDailyValues(theYear); // output of mean biomass across grid per day
		//  keepGoing = pRESULTS->savePersistence(maxYears, theYear);

		if (theTrials==1)	// if only one trial, produce additional output
		{
			if (maxYears <= 3) {
//			pRESULTS->saveYearlyLattAsGrid(); // additional output of max biomass as cell matrix
//			pRESULTS->saveYearlyRunoffAsGrid(); // additional output of runoff as cell matrix
//			pRESULTS->saveYearlyPotA1AsGrid(); // additional output of pot in A1 as cell matrix
//			pRESULTS->saveYearlyPotA2AsGrid(); // additional output of pot in A2 as cell matrix
//			pRESULTS->saveYearlyPotA3AsGrid(); // additional output of pot in A3 as cell matrix
//			pRESULTS->saveYearlyPotA4AsGrid(); // additional output of pot in A4 as cell matrix
//			pRESULTS->saveYearlyCWaterAsGrid(); // additional output of water in C as cell matrix
			}
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

