/*
 *  Parameters.h
 *
 *  Created by Martin Köchy on Tue Apr 29 2003.
 *  Copyright (c) 2003 __MyCompanyName__. All rights reserved.
 *
 */

#include "hexmath.h"

//------------------------------------------------------------------
#ifndef ParametersH
#define ParametersH
//------------------------------------------------------------------

 enum SOILTYPE {noSoil, SlSB, LsLA, LsuBG, LtsMA, LtEJ, generic, batchSoil};
enum SPECIES  {noSpec, AveSteri, BiscDid, BraDist, BromFasc, CarrAnn, CriDeli, FilDes, HippUni, HymCir, RebPin, SchisArab, StipCap, ValHis, annual, typMes, typMed, typSem, typAri, all, batchSpecies};

enum NSupplyQ {zero, low, medium, high};
enum cover {bare, herb, shrub, hus};

const int gridLengthC = 50;	// seitwärts; cell units, 50*50*4 = 1 m2, 71*71*2 = 1 m2
const int gridLengthR = 50; // abwärts; 38*38*1 = 0.15 m2
// large grids result in EXC_BAD_ACCESS errors or Segmentation faults

const float cellArea = 1.0; // cm2
const int days_in_year = 365;
const float maxPsi = -0.01;

// the distance over which competition and density dependent effects are effective
const unsigned int cSuppress_dist = 2;

/*
Where to switch off variability:
	SEEDS::updateSeedbank, setParameters ..., theNewSeeds = 0
	SEEDS::predation
	PLANT::disperse, distance = 0
	PLANT::competition, K = 1
	SOIL::evaporation, varies with vegetation type
	(Rain.cpp)
	GRIDPARAMETERS::GRIDPARAMETERS, moistureTopoV = 0
	GRIDPARAMETERS::GRIDPARAMETERS, shrubCover = 0	or 100
	Seed_Parameters::setForAllSpecies, iniSeedNbrV = 0, survRateV = 0, DDv = 0
	ActivityV = 0.0
	SOIL_Parameters, runoff coefficients vary with vegetation type
	
Don't switch off:
	SEEDS::germination
*/

//------------------------------------------------------------------
#endif
