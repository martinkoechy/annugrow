/*
 *  batch_input.cpp
 *  annuals
 *
 *  Created by Forschung on Fri Nov 05 2004.
 *  Copyright (c) 2004 __MyCompanyName__. All rights reserved.
 *
 */

#include <iostream>
#include <fstream>
#include "batch_input.h"

PARAMCOLL::PARAMCOLL (void)
{
  thePosition = 0;
}

PARAMCOLL::~PARAMCOLL ()
{}

short PARAMCOLL::read_parameter_file (ifstream & FParameters, const char* file_name)
{
  FParameters.open(file_name, ios::in | ios::binary); // binary is necessary for Windows, or file must use Unix line-endings
  
  FParameters.seekg(thePosition); // read to "thePosition" from beginning
  FParameters.clear();
  
  char comment;
  comment=FParameters.peek();
  if (comment == '#')
  {
	const int lengthOfLine = 20*67; // max length of line = 20 char * 67 params
	char temp[lengthOfLine];
	FParameters.getline(temp,lengthOfLine);
	thePosition = FParameters.tellg();
	FParameters.close();
  	return -1;	
  }
  else
  {
	int tempN = 0;
	FParameters >> outputID;
	FParameters >> trials;
	FParameters >> years;
	FParameters >> rainP.RFileName;
	FParameters >> rainP.meanAP;
	
	if (rainP.meanAP == -2)
	  rainP.isReGen = true;
	FParameters >> rainP.PAmplitude;
	FParameters >> rainP.PLocation;
	FParameters >> rainP.PWidth;
	FParameters >> rainP.PShape;	
	FParameters >> rainP.VAmplitude;
	FParameters >> rainP.VLocation;
	FParameters >> rainP.VWidth;
	FParameters >> rainP.VShape;
	
	FParameters >> climateP.theMeanT;
	FParameters >> climateP.theRangeT;
	FParameters >> climateP.theColdestDay;
	FParameters >> climateP.relLight;
	
	FParameters >> gridP.moistureTopoV;
	FParameters >> gridP.stoniness;
	FParameters >> gridP.stoninessV;
	FParameters >> gridP.shrubCover;
	FParameters >> gridP.shrubRadius;
	
	FParameters >> soilP.EvapoO;
	FParameters >> soilP.EvapoA1;
	FParameters >> soilP.infRateShrub;
	FParameters >> soilP.infRateHerb;
	FParameters >> soilP.infRateBare;
	FParameters >> soilP.deltaInfRate;
	FParameters >> soilP.permeabilityA;
	FParameters >> soilP.permeabilityC;
	FParameters >> soilP.DepthA4;
	FParameters >> tempN;
	switch (tempN)
	{
	  case 0: soilP.NSupply = zero; break;
	  case 1: soilP.NSupply = low; break;
	  case 2: soilP.NSupply = medium; break;
	  case 3: soilP.NSupply = high; break;
	  default: soilP.NSupply = medium; 
		cerr << "\nillegal N supply: " << tempN << " set to 'medium'" << endl;
	}
	FParameters >> soilP.doRunon;
	FParameters >> soilP.alpha;
	FParameters >> soilP.beta;
	FParameters >> soilP.thetaR;
	FParameters >> soilP.thetaS;
	
	FParameters >> seedP.constSeedbank;
	FParameters >> seedP.iniSeedNbr;
	FParameters >> seedP.iniSeedNbrV;
	FParameters >> seedP.survRate;
	FParameters >> seedP.survRateV;
	FParameters >> seedP.seedbankPersistence;
	FParameters >> seedP.DDv;
	FParameters >> seedP.DD;
	FParameters >> seedP.PsiB50m;
	FParameters >> seedP.PsiB50b;
	FParameters >> seedP.PsiB50S;
	FParameters >> seedP.thetaH;
	FParameters >> seedP.Tmin;
	float temp;
	FParameters >> temp;
	seedP.DryDaysMax = int(temp+0.5);
	FParameters >> seedP.maxGerm;
	
	FParameters >> plantP.Home;
	FParameters >> plantP.MassAccessA2;
	FParameters >> plantP.MassAccessA3;
	FParameters >> plantP.MassAccessA4;
	FParameters >> plantP.MassCompetition1;
	FParameters >> plantP.MassCompetition2;
	
	FParameters >> plantP.MassSeed;
	FParameters >> plantP.MassFruit;
	FParameters >> plantP.MassEstablish;
	FParameters >> plantP.MassFlowering;
	FParameters >> plantP.MassMax;
	FParameters >> plantP.RGR_Max;
	FParameters >> plantP.PWP;
	FParameters >> plantP.AllocationRepro;
	FParameters >> tempN;
	switch (tempN)
	{
	  case 0: plantP.N_tolerance = zero; break;
	  case 1: plantP.N_tolerance = low; break;
	  case 2: plantP.N_tolerance = medium; break;
	  case 3: plantP.N_tolerance = high; break;
	  default: plantP.N_tolerance = medium; 
		cerr << "\nillegal N tolerance: " << tempN << " set to 'medium'" << endl;
	}
	FParameters >> plantP.DDMortality;
	
	thePosition = FParameters.tellg();
	FParameters.close();
	return FParameters.eof();
  }
  }
