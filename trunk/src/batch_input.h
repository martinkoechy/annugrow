/*
 *  batch_input.h
 *  annuals
 *
 *  Created by Forschung on Fri Nov 05 2004.
 *  Copyright (c) 2004 __MyCompanyName__. All rights reserved.
 *
 */
#include "RainParameters.h"
#include "ClimateParameters.h"
#include "GridParameters.h"
#include "SoilParameters.h"
#include "SeedParameters.h"
#include "PlantParameters.h"

//------------------------------------------------------------------
#ifndef Batch_InputH
#define Batch_InputH
//------------------------------------------------------------------

class PARAMCOLL
{
  public:
	PARAMCOLL (void);
	~PARAMCOLL();
	string outputID;
//	string theFileName;
	int trials;
	int years;
	RAINPARAMETERS rainP;
	CLIMATE climateP;
	GRIDPARAMETERS gridP;
	cSPSoilBatch soilP;
	cSPSeedBatch seedP;
	cPPPlantBatch plantP;
	short read_parameter_file (ifstream &, const char* file_name); //true if not yet eol
private:
	  long thePosition;
};

//------------------------------------------------------------------
#endif

