/*
 *  user_input.cpp
 *  annuals
 *
 *  Created by Martin Kšchy on Sun Feb 29 2004.
 *  Copyright (c) 2004 __MyCompanyName__. All rights reserved.
 *
 */

#include <iostream>
#include <time.h>
#include "user_input.h"

//--------------------------- SPECIES -------------------------------------
int inputSpecies (void)
{
	int selection = -1;
	do
	{
	  cout << "Choose a species:" << endl;
      cout << "[0] generic annual, " ;
      cout << "[1] typical arid (SC), ";
      cout << "[2] typical semiarid (CD), " << endl;
      cout << "[4] typical Mediterranean (AS), ";
      cout << "[5] typical mesic Mediterranean (BrD), " << endl;
	  cout << "[6] Avena sterilis, ";
	  cout << "[7] Biscutella didyma, ";
	  cout << "[8] Brachypodium distachyum, " << endl;
	  cout << "[9] Bromus fasciculatus, ";
	  cout << "[10] Carrichtera annua, ";
	  cout << "[11] Crithopsis delileana, "  << endl;
      cout << "[12] Filago desertorum,";
      cout << "[13] Hippocrepis unisiliquosa, ";
      cout << "[14] Hymenocarpos circinnatus," << endl;
      cout << "[15] Reboudia pinnata, ";
      cout << "[16] Schismus arabicus,";
      cout << "[17] Stipa capensis, " << endl;
      cout << "[18] Valantia hispida," << endl;
      cout << "[98] all typical species" << endl;
      cout << "[99] all species" << endl;
	  cin >> selection;

	  if (selection < 0 || (selection > 18 && selection < 98) || selection > 99)
      {  
        cout << "Selection not available." << endl;
        selection = -1;
      }
		} while (selection == -1);
	return selection;
}

void translateSpecies (int s, SEED_PARAMETERS* & pSeedP,
					   PLANT_PARAMETERS* & pPlantP, string & species_char)
{
  switch(s)
  {
	case(0): pSeedP = new SEED_PARAMETERS, 
	  pPlantP = new PLANT_PARAMETERS; species_char = "ga_"; break;
	case(1): pSeedP = new cSPTypAri, 
	  pPlantP = new cPPTypAri; species_char = "tS_"; break;
	case(2): pSeedP = new cSPTypSem; 
	  pPlantP = new cPPTypSem; species_char = "tL_"; break;
	case(3): pSeedP = new SEED_PARAMETERS, 
	  pPlantP = new PLANT_PARAMETERS; species_char = "ga_"; break;
	case(4): pSeedP = new cSPTypMed; 
	  pPlantP = new cPPTypMed; species_char = "tM_"; break;
	case(5): pSeedP = new cSPTypMes; 
	  pPlantP = new cPPTypMes; species_char = "tE_"; break;
	case(6): pSeedP = new cSPAveSteri; 
	  pPlantP = new cPPAveSteri; species_char = "AS_"; break;
	case(7): pSeedP = new cSPBiscDid; 
	  pPlantP = new cPPBiscDid; species_char = "BD_"; break;
	case(8): pSeedP = new cSPBraDist; 
	  pPlantP = new cPPBraDist; species_char = "BrD_"; break;
	case(9): pSeedP = new cSPBromFasc; 
	  pPlantP = new cPPBromFasc; species_char = "BF_"; break;
	case(10): pSeedP = new cSPCarrAnn; 
	  pPlantP = new cPPCarrAnn; species_char = "CA_"; break;
	case(11): pSeedP = new cSPCriDeli; 
	  pPlantP = new cPPCriDeli; species_char = "CD_"; break;
	case(12): pSeedP = new cSPFilDes; 
	  pPlantP = new cPPFilDes; species_char = "FD_"; break;
	case(13): pSeedP = new cSPHippUni; 
	  pPlantP = new cPPHippUni; species_char = "HU_"; break;
	case(14): pSeedP = new cSPHymCir; 
	  pPlantP = new cPPHymCir; species_char = "HC_"; break;
	case(15): pSeedP = new cSPRebPin; 
	  pPlantP = new cPPRebPin; species_char = "RP_"; break;
	case(16): pSeedP = new cSPSchisArab; 
	  pPlantP = new cPPSchisArab; species_char = "SA_"; break;
	case(17): pSeedP = new cSPStipCap; 
	  pPlantP = new cPPStipCap; species_char = "SC_"; break;
	case(18): pSeedP = new cSPValHis; 
	  pPlantP = new cPPValHis; species_char = "VH_"; break;
  }
}

//--------------------------- SOIL TYPE ---------------------------------------
int inputSoilType(void)
{		
	int selection = -1;
	
	do
	{
		cout << "\nChoose a soil type:" << endl;
		cout << "[0] generic" << endl;
		cout << "[1] sandy Loam (Sed'e Boqer),     [2] Loam (Lahav)," << endl;
		cout << "[3] Loamy Clay (Bet Guvrin), [4] Clay (Matta)," << endl;
		cout << "[5] Clay ('En Y'aqov)" << endl;
		cout << "[99] all types, excluding generic" << endl;
		cin >> selection;

		if ((selection < -1 || selection > 7) && (selection != 99)){
		  cout << "Selection not available." << endl;
		  selection = -1;}
	}
	while (selection == -1);
	
	return selection;
}

void translateSoilType (int p, SOILPARAMETERS* & pSoilP, string & soil_char)
{
	switch (p)
	{
		case(1): pSoilP = new cSPSedeBoqer; soil_char = "S1_"; break;
		case(2): pSoilP = new cSPLahab; soil_char = "S2_"; break;
		case(3): pSoilP = new cSPBetGubrin; soil_char = "S3_"; break;
		case(4): pSoilP = new cSPMaththa; soil_char = "S4_"; break;
		case(5): pSoilP = new cSPEnJaqob; soil_char = "S5_"; break;
		case(0): pSoilP = new SOILPARAMETERS(1); soil_char = "S0_"; break;
	}	
}

//--------------------------- CLIMATE-TEMPERATURE --------------------------------

string inputTClimate (CLIMATE* & pCLIMATE)
{
	int selection = 0;
	string name = "cIL_";
	float meanT = 0.0, rangeT = 0.0, light = 1.0;
	do
	{
		cout << "\nChoose a site with current mean annual temperature" << endl;
		cout << "and temperature range:" << endl;
		cout << "[1] Sed'e Boqer: Tmean = 20.5 degC, range = 6.5 K, light under shrubs = 1.0" << endl; 
		cout << "[2] Lahav: Tmean = 20.0 degC, range = 7.0 K, light under shrubs = 0.95" << endl;
		cout << "[3] Bet Guvrin: Tmean = 19.5 degC, range = 7.0 K, light under shrubs = 0.9" << endl; 
		cout << "[4] Matta: Tmean = 19.0 degC, range = 7.0 K, light under shrubs = 0.85" << endl;
		cout << "[5] 'En Ya'aqov: Tmean = 20.5 degC, range = 7.5 K, light under shrubs = 0.85" << endl; 
		cout << "[6] set Tmean, T range and light" << endl;
		cin >> selection;

		switch (selection)
		{
			case 1: pCLIMATE = new cPCSedeBoqer; name = "cSB_"; break;
			case 2: pCLIMATE = new cPCLahab; name = "cLA_"; break;
			case 3: pCLIMATE = new cPCBetGubrin; name = "cBG_"; break;
			case 4: pCLIMATE = new cPCMaththa; name = "cMA_"; break;
			case 5: pCLIMATE = new cPCEnJaqob; name = "cEY_"; break;
			case 6: do
					{
						cout << "\nEnter mean annual temperature (15-25 degC): ";
						cin >> meanT;
						cout << "and the monthly range (5-15 K): ";
						cin >> rangeT;
						cout << "and the percentage of light under shrubs (0-100): ";
						  cin >> light;
					}
					while (meanT < 15 || meanT > 25 || rangeT < 5 || rangeT > 15 || light < 0 || light > 100);
					pCLIMATE = new CLIMATE(meanT, rangeT, light/100.0); name = "cIL_"; break;
			default: cout << "Selection not available." << endl; selection = 0;
		}
	}
	while (!selection);
	
	return name;
}


//--------------------------- GRIDPARAMETERS ---------------------------------
/*
void inputLandscape (GRIDPARAMETERS* & pGridP)
{
  char a = 0;
  do {
  cout << "\nSet landscape features? [Y/N]" << endl;
  cin >> a;
  	if (a=='Y' || a == 'y')
	{
	  cout << "\n Set surface variability [0.0 .. 1.0]" << endl;
	  cin >> pGridP->moistureTopoV;
	  cout << "\n Set stone cover [0.0 .. 1.0]" << endl;
	  cin >> pGridP->stoniness;
	  cout << "\n Set stone cover variability [0.0 .. 1.0]" << endl;
	  cin >> pGridP->stoninessV;
	  cout << "\n Set shrub cover [0 .. 100]" << endl;
	  cin >> pGridP->shrubCover;
	  cout << "\n Set shrub radius [0 .. 50]" << endl;
	  cin >> pGridP->shrubRadius;
	}
  } while (a == 0);
}
*/
void inputLandscape (GRIDPARAMETERS* & pGridP)
{
  float cover = 0.0;
  do{
	cout << "\n Set surface variability [0.0 .. 1.0]" << endl;
	cin >> pGridP->moistureTopoV;}
  while (pGridP->moistureTopoV < 0.0 || pGridP->moistureTopoV > 1.0);
  
  do{
	cout << "\n Set shrub cover [0 .. 100]" << endl;
	cin >> cover;
	if (cover > 0.0 && cover < 100.0)
	  do {
		cout << "\n Set shrub radius [0 .. 50]" << endl;
		cin >> pGridP->shrubRadius;
	  } while (pGridP->shrubRadius < 0.0 || pGridP->shrubRadius > 50.0);
  } while (cover < 0.0 || cover > 100.0);
  pGridP->shrubCover = int(cover);
}

//--------------------------- RAIN ---------------------------------
void inputRain (vector <string> & rain_batch)
{
	string name_of_rain_file = "somewhere";
	char a=0;
	do {
	cout << "\nChoose the rain files for all five stations? [Y/N]" << endl;
	cin>> a;
	if (a=='Y' || a == 'y') fillRainVector (rain_batch);
	else
	{
		do
		{
			cout << "\nRain file name, stop with \"0\"):"
			<< endl;
			cin >> name_of_rain_file;
			rain_batch.push_back(name_of_rain_file);
    }
	 while (name_of_rain_file != "0");
   rain_batch.pop_back();
	}
	} while (a == 0);
}


void fillRainVector (vector <string> & rain_batch)
{
  rain_batch.push_back("SB");
  rain_batch.push_back("BS");
  rain_batch.push_back("BG");
  rain_batch.push_back("BR");
  rain_batch.push_back("EL");
}

void inputRainVol (vector <float> & mean_batch)
{
	int v=0;
	cout << "\nEnter mean annual rain volume."<< endl;
  cout << " '-1' for natural, '-2' for standard (100, 200, 400, 600, 800)," << endl;
  cout << " '0' to stop." << endl;
  
  if (v == -2) RainVolume(mean_batch);
  else do
  {
    cout << "value: "; cin >> v;
    mean_batch.push_back(v);
  }
  while (v > 0 || v == -1);
  if( v == 0) mean_batch.pop_back();
}

void RainVolume (vector <float> & mean_batch)
{
  mean_batch.push_back(100);
  mean_batch.push_back(200);
  mean_batch.push_back(400);
  mean_batch.push_back(600);
  mean_batch.push_back(800);
}

//--------------------------- YEARS --------------------------------
int inputYears (void)
{
	int years;
	cout << "\nEnter number of years (negative number to stop program):" << endl;
	cin >> years;
	return years;
}

//--------------------------- TRIALS --------------------------------
int inputTrials (void)
{
	int trials;
	cout << "\nHow many trials (repeat runs) do you want?\n";
	cin >> trials;
	return trials;
}

//---------------------------- OUTPUT --------------------------------

int outputMessage (int trials)
{
	int outfiles = 0;
	
	if (trials == 1)
	{
		cout << "\nThere can be five output files (*.txt):\n";
		cout << " 1. [ _log] documentation of the variables and rain data used,\n";
		cout << " 2. [ _DLC] daily values (rain, #plants, soil psi) averaged across cells,\n";
		cout << " 3. [ _YCC] annual values for each cell, printed in columns,\n";
		cout << " 4. [ _YLC] annual means across cells, printed in columns,\n";
		cout << " 5. [ _YLG] annual mean of one variable for each cell, printed in rows and columns\n " << endl;
		outfiles = 3;
	}
	else
	{
		cout << "\nThere can be three output files (*.txt):\n";
		cout << " 1. [ _log] documentation of the rain data used,\n";
		cout << " 2. [ _DLC] daily values (rain, #plants, soil psi) averaged across cells,\n";
		cout << " 3. [ _per] years of population persistence,\n";
		cout << " 4. [ _YLC] annual means across cells, printed in columns.\n"<< endl;
		outfiles = 1;
	}

	return outfiles;
}

void rainMessage (string scenario)
{
	cout << scenario;
}

void trialsMessage (int trials, int i)
{
	if (trials > 1)
		cout << "Now doing trial " << i+1 << endl;
}

int repeatMessage (void)
{
	char choice;
		
	cout << "Continue? [Y/N]" << endl;
	cin >> choice;
	
  if (choice == 'Y' || choice == 'y' || choice == '1') return 1;
  else return 0;
}

void startMessage (void)
{
	time_t currentTime;
	time (&currentTime);
	cout << " Started at " << ctime(&currentTime) << endl;
}

void finishedMessage (void)
{
	time_t currentTime;
	time (&currentTime);
	cout << "\n\n"
		<< "Finished at " << ctime(&currentTime) << endl;
}
