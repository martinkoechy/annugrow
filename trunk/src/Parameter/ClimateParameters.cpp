/*
 *  ClimateParameters.cpp
 *  intraspecific
 *
 *  Created by Martin Kšchy on Fri May 02 2003.
 *  Copyright (c) 2003 __MyCompanyName__. All rights reserved.
 *
 */

#include <iostream>
#include <fstream>
#include "ClimateParameters.h"

using namespace std;

CLIMATE::CLIMATE(void)
{
  strcpy(N, "batch climate");
}

CLIMATE::CLIMATE(float T_mean, float T_var, float d_min, float rel_Light)
{
	strcpy(	N, "custom climate");
	theMeanT = T_mean;
	theRangeT = T_var;
	theColdestDay = d_min; // for setting X-value of minimum of cos function
	relLight = rel_Light;
}

void CLIMATE::documentation(char* filename) const
{
  ofstream ParameterDocu;
  ParameterDocu.open (filename, std::ios::app);
	
  ParameterDocu << "------ Temperature Parameters ------" << endl;
  ParameterDocu << "Climate: \t" << N << endl;

  ParameterDocu << "mean annual temperature: \t" << theMeanT << endl;
  ParameterDocu << "temperature range (coldest - warmest month): \t" << theRangeT << endl;
  ParameterDocu << "coldest day of year: \t" << theColdestDay << " after July 31" << endl;

  ParameterDocu << "------ Environment Parameters ------" << endl;
  ParameterDocu << "reduction of light: \t" << relLight << "%" << endl;

  ParameterDocu.close();
}

cPCEnJaqob::cPCEnJaqob (void)
{
  strcpy(N, "'EnJa'aqob");
  theMeanT = 20.5;
  theRangeT = 7.5;
  relLight = 0.85;
}

cPCMaththa::cPCMaththa (void)
{
  strcpy(N, "Maththa");
  theMeanT = 19.0;
  theRangeT = 7.0;
  relLight = 0.85;
}

cPCBetGubrin::cPCBetGubrin (void)
{
  strcpy(N, "BetGubrin");
  theMeanT = 19.5;
  theRangeT = 7.0;
  relLight = 0.9;
}

cPCLahab::cPCLahab (void)
{
  strcpy(N, "Lahab");
  theMeanT = 20.0;
  theRangeT = 7.0;
  relLight = 0.95;
}

cPCSedeBoqer::cPCSedeBoqer (void)
{
  strcpy(N, "SedeBoqer");
  theMeanT = 20.5;
  theRangeT = 6.5;
  relLight = 0.95;
}
