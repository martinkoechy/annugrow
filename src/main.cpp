/*
 *  main.cpp
 *  intraspecific
 *
 *  Created by Martin Kšchy on Thu Feb 06 2003.
 *  Copyright (c) 2003 __MyCompanyName__. All rights reserved.
 *
 * Version 2.4.5: drained water is not lost but drains into lower soil layer
 * Version 2.4.7: calculations for soil are now collected in RESULTS
 *				  introduced new parameter: soil stoniness (reduces soil volume)
 *				  added creation of results folder
 * Version 2.4.8: enabled input from batch file
 * Version 2.4.10: modified PLANT::suppression
 * Version 2.5: modified SEEDS:predation and seedbank survival, 
 *				density-dependence only when other seeds in neighbourhood
 * Version 2.5.2: changes to competition procedure
 * Version 2.5.3: inclusion of stochastic rain generation
 *                     this version was used for published results
 * Version 2.5.4: correction of mistakes in results.h, results.cpp 
 *                    (erroneous conversion from float to int)
 * Version 2.6.0: correction of SOIL::balancePsi (see there for details)
 *                    modifications related to "total mass" in PLANT::grow - until now, total mass 
 *                    was actually vegetative mass.
 * Version 2.6.1: incorporated algorithms of ReGen 2.0 with variable shape parameters
 *                added standing crop in daily output; no defragmentation or decomposition, manual reset at start of year
 *					in MyTime.cpp:days_loop: division by 365 days corrected from int to float
 * Version 2.7: changes for testing inverse-hypothesis effect
 *                longest wet period (moistd2 etc.) is now calculated correctly when the soil is moist during the summer
 *                new parameters based on more years
 * Version 2.7.1: corrected a mistake in moistD3, moistD2 output (variable moistD5 was used for resetting)
 */

#include <fstream>
#include <iostream>
#include <sstream>
#include <time.h>
#include "r250m.h"
#include "user_input.h"
#include "simulation.h"
#include "batch_input.h"


using namespace std;

int main (int argc, const char * argv[]) 
/* argv[0] is supplied automatically and contains absolute path of program
*/
{ 
  CLIMATE* pCLIMATE;
  GRIDPARAMETERS* pGRIDPARAMETERS = new GRIDPARAMETERS;
  SOILPARAMETERS* pSOILPARAMETERS;
  SEED_PARAMETERS* pSEEDPARAMETERS;
  PLANT_PARAMETERS* pPLANTPARAMETERS;
  RAINPARAMETERS* pRAINPARAMETERS = new RAINPARAMETERS;
  
  PARAMCOLL* pBatchP;
  extern int nParameterCombos; // in Results.cpp
  
  class PFileNotFound {}; // for error handling

  int years = 0;
  int trials = 0;
  
  string RPath =  "./../../../Regen/";   // on Mac use single forward slash, on PC use double backslashes
  pRAINPARAMETERS->RFilePath = RPath;
  
  string name_of_rain_file = "somewhere";
	string name_of_results_files = "Results";
	
	string climate_char = "some climate";
	string species_char = "some species";
	string soil_char = "some soil";
	
	int soilID = 0;
	int speciesID = 0;
	r250_init(clock());	// when left out, repeated runs of the program
						//  produce identical results
	
	if (argc==2) // read parameters from batch file
	{
	  short stop = 0;
	  
	  ifstream FParameters;			// declaration of input file
	  try
	  {
		FParameters.open(argv[1]);
		if (!FParameters)				//Fehlerabfrage
		{
		  throw PFileNotFound();
		}
		FParameters.close();
	  }
	  catch(PFileNotFound){cerr<< "Stapeldatei nicht gefunden!"<<endl;exit(99);};
	  
	  pBatchP = new PARAMCOLL;
	  while (stop < 1)
	  {
		stop = pBatchP->read_parameter_file(FParameters, argv[1]);
		if (stop != 0) continue;
		
		nParameterCombos++;
		cout << "++++  Working on parameter set " << nParameterCombos << "  (ID " << pBatchP->outputID << ")  ++++" << endl;
		
		pRAINPARAMETERS = &(pBatchP->rainP);
		pRAINPARAMETERS->RFilePath = RPath;

		pCLIMATE = &(pBatchP->climateP);
		pGRIDPARAMETERS = &(pBatchP->gridP);
		pSOILPARAMETERS = &(pBatchP->soilP);
		pSEEDPARAMETERS = &(pBatchP->seedP);
		pPLANTPARAMETERS= &(pBatchP->plantP);
				
		string ResultsFileName = string(argv[1]);
		int findDot = ResultsFileName.rfind(".");
		int ssize = ResultsFileName.size();
		if (findDot > ssize) findDot = ssize;
		ResultsFileName = ResultsFileName.substr(0,findDot);
		ResultsFileName = ResultsFileName + "_out";
		ssize = ResultsFileName.size();
		char* pResultsFileNameC = new char [ssize + 1];
		strcpy(pResultsFileNameC, ResultsFileName.c_str());
		
		simulation((pBatchP->outputID).c_str(), 
				   pBatchP->trials, 
				   pBatchP->years, 
				   pResultsFileNameC, 
				   4, // file batch simulation
				   pRAINPARAMETERS, pCLIMATE, pGRIDPARAMETERS, 
				   pSOILPARAMETERS, pSEEDPARAMETERS, pPLANTPARAMETERS);

		delete pResultsFileNameC;
	  }
	}
	else // user input
	{
	do
	{
    // INPUT =================================================
	  nParameterCombos = 1;
	  
	  speciesID = inputSpecies();
	  
	  climate_char = inputTClimate(pCLIMATE);
	  
		soilID = inputSoilType();
		
		inputLandscape(pGRIDPARAMETERS);

		vector <string> rain_batch;
		inputRain(rain_batch);
		
		vector <float> mean_batch;
		inputRainVol(mean_batch);
				
		years = inputYears();
		if (years < 0) break;

		trials = inputTrials();
		
		// END INPUT =============================================
	
	  
		// --------------- species batch loop		
    int smin = speciesID, smax = speciesID;
    if (speciesID == 98) {
      smin = 6; smax = 18;
    }
    if (speciesID == 99) {
      smin = 1; smax = 5;
    }
		
    for (int s = smin; s <= smax; s++) {
			translateSpecies(s, pSEEDPARAMETERS, pPLANTPARAMETERS, species_char);
			
			// ------------- soil batch loop
      int soilIDmin = soilID, soilIDmax = soilID;
      if (soilID == 99) {
        soilIDmin = 1; soilIDmax = 5;
      }
			
      for (int p = soilIDmin; p <= soilIDmax; p++) {
				translateSoilType(p, pSOILPARAMETERS, soil_char);
				        
				// ----------- rain batch loop
				unsigned short rain_batch_size = rain_batch.size();
				unsigned short mean_batch_size = mean_batch.size();
				for (unsigned int b = 0; b < rain_batch_size; b++) {
					for (unsigned int c = 0; c < mean_batch_size; c++) // vers. 2.4.10
					{
					  pRAINPARAMETERS->RFileName = (rain_batch[b]).c_str();
					  pRAINPARAMETERS->meanAP = mean_batch[c];
						string vol;
						if (mean_batch[c] == -1)
							vol = "nat";
						else {
							stringstream tmp;
							tmp << mean_batch[c];
							tmp >> vol;
						}
						name_of_results_files = species_char + soil_char + climate_char + pRAINPARAMETERS->RFileName + vol; // replace user-defined name
				
			  			rainMessage (pRAINPARAMETERS->RFileName);
																
						// -------- START SIMULATION =======================
						simulation("u", trials, years, 
								   name_of_results_files.c_str(),
								   3, // user input
								   pRAINPARAMETERS, pCLIMATE, pGRIDPARAMETERS,
								   pSOILPARAMETERS, pSEEDPARAMETERS, pPLANTPARAMETERS);
						// -------- END SIMULATION =========================
					}
				} // end of batch rain	
		} // end of batch soil					
	  } // end of batch species	
	  years = repeatMessage();
	} while (years > 0);
  } // end of batch?user input
	pGRIDPARAMETERS = 0;
	pRAINPARAMETERS = 0;
  return 0;
}
