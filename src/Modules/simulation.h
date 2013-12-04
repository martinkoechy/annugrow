/*
 *  simulation.h
 *  annuals
 *
 *  Created by Forschung on Fri Nov 05 2004.
 *  Copyright (c) 2004 __MyCompanyName__. All rights reserved.
 *
 */

#include "Parameters.h"
#include "RainParameters.h"
#include "ClimateParameters.h"
#include "GridParameters.h"
#include "SoilParameters.h"

#ifndef SimulationH
#define SimulationH

void simulation(const char* ID, int trials, int years, 
				const char* name_of_results_files, inType typeOfInput, 
				RAINPARAMETERS* pRainP, CLIMATE* pClimateP, 
				GRIDPARAMETERS* pGridP, SOILPARAMETERS* pSoilP, 
				SEED_PARAMETERS* pSEEDPARAMETERS, PLANT_PARAMETERS* pPLANTPARAMETERS);

#endif
