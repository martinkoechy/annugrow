/*
 *  RainParameters.h
 *  annuals
 *
 *  Created by Forschung on Wed Apr 20 2005.
 *  Copyright (c) 2005 __MyCompanyName__. All rights reserved.
 *
 */

#include <string>

#ifndef RainParametersH
#define RainParametersH

class RAINPARAMETERS
{
  public:
  RAINPARAMETERS (void);
  ~RAINPARAMETERS(){};
  bool isReGen;
  float meanAP;
  float PAmplitude;
  float PLocation;
  float PWidth;
  float PShape;
  float VAmplitude;
  float VLocation;
  float VWidth;
  float VShape;
  std::string RFileName;
  std::string RFilePath;
  std::string getLongRFileName(void);
};

#endif
