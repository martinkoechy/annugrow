/*
 *  SoilParameters.cpp
 *  intraspecific
 *
 *  Created by Martin Kšchy on Sat May 03 2003.
 *  Copyright (c) 2003 __MyCompanyName__. All rights reserved.
 *
 */

#include <string>
#include <iostream>
#include <fstream>
#include "batch_input.h"
#include "SoilParameters.h"

using namespace std;

void SOILPARAMETERS::setForAllTypes(void)
{
  DepthO  = 0.1; // dm, surface, layer containing seed bank
  DepthA1 = 0.4; // dm, starts below surface layer, water uptake by herbs; Lavee et al. 1991
  DepthA2 = 0.5; // dm
  DepthA3 = 0.5; // dm
  throughfall = 0.9; // [0;1], 0.7 = Belmonte Saerrato & Romero Diaz 1998
  doRunon = true;
}

void SOILPARAMETERS::documentation(char* filename) const
{
	ofstream ParameterDocu;
	ParameterDocu.open (filename, std::ios::app);

  ParameterDocu << "------ Soil Parameters ------" << endl;
  ParameterDocu << "Soil type: \t" << N << endl;
  
  ParameterDocu << "FK (MPa): \t" << maxPsi << endl;
  ParameterDocu << "alpha: \t" << alpha << endl;
  ParameterDocu << "beta: \t"  << beta << endl;
  ParameterDocu << "thetaR: \t" << thetaR << endl;
  ParameterDocu << "thetaS: \t" << thetaS << endl;
  ParameterDocu << "EvapoO: \t" << EvapoO << endl;
  ParameterDocu << "EvapoA1: \t" << EvapoA1 << endl;
	ParameterDocu << "DepthO: \t" << DepthO << endl;
	ParameterDocu << "DepthA1: \t" << DepthA1 << endl;
	ParameterDocu << "DepthA2: \t" << DepthA2 << endl;
	ParameterDocu << "DepthA3: \t" << DepthA3 << endl;
	ParameterDocu << "DepthA4: \t" << DepthA4 << endl;
  char NText [6]; strcpy (NText,NSupply==low?"low":(NSupply==medium?"medium":"high"));
	ParameterDocu << "NSupply: \t" << NText << endl;
	ParameterDocu << "Runon: \t" << (doRunon?"yes":"no") << endl;	
	ParameterDocu << "infRateShrub: \t" << infRateShrub << endl;
	ParameterDocu << "infRateHerb: \t" << infRateHerb << endl;
	ParameterDocu << "infRateBare: \t" << infRateBare << endl;
//	ParameterDocu << "infRateASat: \t" << infRateASat << endl;
	ParameterDocu << "deltaInfRate: \t" << deltaInfRate<< endl;	
	ParameterDocu << "permeabilityA: \t" << permeabilityA << endl;	
	ParameterDocu << "permeabilityC: \t" << permeabilityC << endl;
	ParameterDocu << "throughfall: \t" << throughfall << endl;
	
	ParameterDocu.close();
}

SOILPARAMETERS::SOILPARAMETERS (int z)
{
  // parameters for different soil types
		/* 
		Conversion between vol% and water potential
		 with van-Genuchten equation
		 Parameters calculated by non-linear regression in JMP
		 from mass% data and bulk density obtained from Sara 
		 Pariente (pers. comm.). thetaS was set to 0.7 (best fit 
														by visual inspection) and thetaR was set to about 0.5 * 
		 vol% in summer. The data refer to sandy to clayey loam 
		 on calcareous rock. Data and parameters were similar
		 for subsurface (0-2 cm) and upper mineral soil (2-12 cm), 
		 but differed among stations.
		 */
  
  setForAllTypes();
  
  strcpy(N,"generic");	// eye-balled, from values of EY, MA, LA, SB
  
  alpha = 60;		// 24
  beta =   1.29;	//  1.29
  thetaR = 0.03;	//	0.03
  thetaS = 0.45;	//  0.45
  
  DepthA4 = 1.0; // dm, layer of water uptake by shrub roots
  
  EvapoO = 3.0;
  EvapoA1 = 2.5;
  
  // runoff coefficients
  infRateShrub	= 0.99; // 
  infRateHerb 	= 0.95; // 0.90 tuned to BS plots, 2002
  infRateBare  	= 0.95; // 
  
  permeabilityA		= 0.60;
  permeabilityC		= 1.0;
  deltaInfRate = 0.15;
  NSupply = medium;
}

cSPEnJaqob::cSPEnJaqob(void)
{
	setForAllTypes();

  strcpy(N,"'En Ja'aqob");
					// if w% ­ v% in Sara's notes
  alpha = 78;			// 60
  beta =   1.22;	//  1.177
  thetaR = 0.05;	//	0.07
  thetaS = 0.55;		//  0.7

  DepthA4 = 1.0; // dm, layer of water uptake by shrub roots
				 //original values, estimate by Hanoch
  EvapoO = 3.0;
  EvapoA1 = 2.0; // 2.0 EY

  //empirical infiltration coefficients 2002/2003 tuned to Pariente et al. Kfar Giladi poster 
  
  infRateShrub = 1.0; // 
  infRateHerb  = 0.99; // 0.90, tuned to BS plots, 2002
  infRateBare  = 0.99; // 
  deltaInfRate = 0.09;
  permeabilityA		=0.6; // EY: 0.6
  permeabilityC		=0.7; //EY: 0.7
  
  NSupply = high; // 4 ppm N September, 0.6 ppm N April, Claus/Sara
}

cSPMaththa::cSPMaththa(void)
{
  setForAllTypes();
  
  strcpy(N,"Mathth'a");
		
					// if w% ­ v% in Sara's notes
	alpha =108.0;   // 144
	beta =   1.25;	//  1.193
	thetaR = 0.04;	//	0.05
	thetaS = 0.5;   //  0.7 0.405
	
	DepthA4 = 1.5; // dm, layer of water uptake by shrub roots
	
    EvapoO = 3.0;
	EvapoA1 = 2.5;

  //empirical infiltration coefficients 2002/2003 tuned to Pariente et al. Kfar Giladi poste
  infRateShrub = 1.0; // 
  infRateHerb  = 1.0; // 1.0 tuned to BS plots, 2002
  infRateBare  = 1.0; // 
  deltaInfRate = 0.01;
  
  permeabilityA		= 0.7;//0.7
  permeabilityC		= 1.0;
  
  NSupply = high; // 4 ppm N September, 1.5 ppm N April, Claus/Sara
}

cSPBetGubrin::cSPBetGubrin(void)
{		// guestimates!
  setForAllTypes();

  strcpy(N,"Bet Gubrin");	
									//originally values of Matta
  alpha =  60.0;	
  beta =   1.26;
  thetaR = 0.04;
  thetaS = 0.45;
  
  DepthA4 = 1.0; // dm, layer of water uptake by shrub roots

  EvapoO = 3.0;
  EvapoA1 = 3.0;
 
  infRateShrub = 0.99;
  infRateHerb  = 0.96;  //0.95
  infRateBare  = 0.94; //0.95
  deltaInfRate = 0.2;
  
  permeabilityA		= 0.6;//0.6
  permeabilityC		= 1.0;
  
  NSupply = high;
}

cSPLahab::cSPLahab(void)
{
  setForAllTypes();
    
  strcpy(N,"Lahab");
	
				  // if w% ­ v% in Sara's notes
  alpha =  59.0;		// 220
  beta =   1.27;	//  1.214
  thetaR = 0.03;	//	0.04
  thetaS = 0.4;	//  0.7
 
  DepthA4 = 0.5; // dm, layer of water uptake by shrub roots
  
  EvapoO = 3.0;
  EvapoA1 = 3.0;

  //empirical infiltration coefficients 2002/2003 tuned to Pariente et al. Kfar Giladi poster 
  infRateShrub = 0.99; // 
  infRateHerb  = 0.93; // 0.88, tuned to BS plots, 2002
  infRateBare  = 0.93;
  deltaInfRate = 0.29;
  
  permeabilityA = 0.5;//0.5
  permeabilityC = 1.0;
  
  NSupply = high; // 8 ppm September, 1.0 ppm N April, Claus/Sara
}


cSPSedeBoqer::cSPSedeBoqer(void)
{
  setForAllTypes();
		
  strcpy(N,"Sede Boqer");
	
				// if w% ­ v% in Sara's notes
  alpha = 62.0;		// 232
  beta =   1.38;	//  1.319
  thetaR = 0.015;	//	0.02
  thetaS = 0.35;	//  0.7
 
  DepthA4 = 0.1; // dm, layer of water uptake by shrub roots
  
  EvapoO = 3.0;
  EvapoA1 = 3.0; //1.2 SedeBoqer

  //empirical infiltration coefficients 2002/2003 tuned to Pariente et al. Kfar Giladi poster

  infRateShrub = 0.92; // 
  infRateHerb  = 0.92; // 0.90 tuned to BS plots, 2002
  infRateBare  = 0.92;
  
  permeabilityA		= 0.3;//0.3
  permeabilityC		= 1.0;
  deltaInfRate = 0.36;
  
  NSupply = high; // 10 ppm N September, 1.1 ppm N April, Claus/Sara
}

cSPSoilBatch::cSPSoilBatch (void)
{
  setForAllTypes();
  strcpy(N,"Batch Soil");
}

