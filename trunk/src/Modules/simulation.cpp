/*
 *  simulation.cpp
 *  annuals
 *
 *  Created by Forschung on Fri Nov 05 2004.
 *  Copyright (c) 2004 __MyCompanyName__. All rights reserved.
 *
 */

#include "Results.h"
#include "MyTime.h"
#include "user_input.h"
#include "simulation.h"

void simulation (const char* ID, int trials, int years, 
				 const char* name_of_results_files, inType inTypeMethod, 
				 RAINPARAMETERS* pRainP, CLIMATE* pClimateP, 
				 GRIDPARAMETERS* pGridP, SOILPARAMETERS* pSoilP, 
				 SEED_PARAMETERS* pSeedP, PLANT_PARAMETERS* pPlantP)
{
  startMessage();
  // the max number of trials for detailed output must be adjusted here, in MyTime.cpp:151ff and Results.cpp
	
	bool detailsLevel = trials<4?true:false;
	
  RESULTS results(name_of_results_files, detailsLevel, ID); 
  
  if (inTypeMethod != batch)
	outputMessage(trials);
  
  for (int i=0; i<trials; i++)
  {
	trialsMessage (trials, i);
	
	results.setTrial(i);
	
	TIME theTime (&results, trials, pRainP, pClimateP, pGridP, pSoilP, pSeedP, pPlantP, i);
	
	theTime.years_loop(years);
  }
  
  finishedMessage();  
}
