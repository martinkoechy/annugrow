/*
 *  RainParameters.cpp
 *  annuals
 *
 *  Created by Forschung on Wed Apr 20 2005.
 *  Copyright (c) 2005 __MyCompanyName__. All rights reserved.
 *
 */
#include "RainParameters.h"

using namespace std;

RAINPARAMETERS::RAINPARAMETERS (void)
{isReGen = false;}

std::string RAINPARAMETERS::getLongRFileName(void)
{
  std::string path = RFilePath;
  path += RFileName;
  return path;
}
