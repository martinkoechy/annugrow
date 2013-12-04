/*
 *  user_input.h
 *  annuals
 *
 *  Created by Martin Kšchy on Sun Feb 29 2004.
 *  Copyright (c) 2004 __MyCompanyName__. All rights reserved.
 *
 */
#include <string>
#include <vector>
#include "Parameters.h"
#include "GridParameters.h"
#include "SoilParameters.h"
#include "SeedParameters.h"
#include "PlantParameters.h"
#include "ClimateParameters.h"

//--------------------------------------------------------------------
#ifndef InputH
#define InputH
//--------------------------------------------------------------------

using namespace std;

class CLIMATE;

int inputSpecies (void);
void translateSpecies (int speciesID, SEED_PARAMETERS* &, PLANT_PARAMETERS* &, string &);
int inputSoilType (void);
void translateSoilType (int soilID, SOILPARAMETERS* &, string &);
string inputTClimate (CLIMATE* &);
void inputLandscape (GRIDPARAMETERS* &);
void inputRain (vector <string> &);
void fillRainVector (vector <string> &);
void inputRainVol (vector <float> &);
void RainVolume (vector <float> & mean_batch);
int inputYears (void);
int inputTrials (void);
void trialsMessage (int trials, int trial);
bool outputMessage (int trials);
int repeatMessage (void);
void startMessage (void);
void finishedMessage (void);
void rainMessage (string);

//--------------------------------------------------------------------
#endif
