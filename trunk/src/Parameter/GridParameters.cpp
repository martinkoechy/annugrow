/*
 *  GridParameters.cpp
 *  intraspecific
 *
 *  Created by Martin Kšchy on Tue May 27 2003.
 *  Copyright (c) 2003 __MyCompanyName__. All rights reserved.
 *
 */


#include <iostream>
#include <string>
#include <fstream>
#include "batch_input.h"
#include "Parameters.h"
#include "GridParameters.h"

using namespace std;

GRIDPARAMETERS::GRIDPARAMETERS(void):theGridLengthC(gridLengthC), theGridLengthR(gridLengthR)
{
  strcpy(N, "Grid parameters");
  
  moistureTopoV = 0.00; // increases or decreases rain in SOIL by -x < random value < x *100%
  stoniness = 0.00; // [0;1]
  stoninessV = 0.00; // [0;1]
  shrubCover = 0; // [0;100] percent
  shrubRadius = 15; // 15 cm
}

void GRIDPARAMETERS::documentation(char* filename) const
{
  ofstream ParameterDocu;
  ParameterDocu.open (filename, std::ios::app);
  
  ParameterDocu << "------ Grid Parameters ------" << endl;
  ParameterDocu << "Grid size:  \t"<< theGridLengthC << " x " << theGridLengthR << " cells" << endl;
  ParameterDocu << " (" << theGridLengthC*theGridLengthR*cellArea/10000.0 << " m2)" << endl;
  ParameterDocu << "variation in water accumulation [0,1]:  \t" << moistureTopoV << endl;
  ParameterDocu << "stoniness [0,1]:\t" << stoniness << endl;	
  ParameterDocu << "stoniness range ±[0,1]:\t" << stoninessV << endl;	
  ParameterDocu << "shrub cover (%):\t" << shrubCover << endl;
  ParameterDocu << "shrub radius (cm):\t" << shrubRadius << endl;
  
  
  ParameterDocu.close();
}

