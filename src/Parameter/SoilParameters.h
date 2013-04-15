/*
 *  SoilParameters.h
 *  intraspecific
 *
 *  Created by Martin Kšchy on Sat May 03 2003.
 *  Copyright (c) 2003 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef SoilParametersH
#define SoilParametersH
//----------------------

#include "Parameters.h"

class SOILPARAMETERS
{
  public:
	SOILPARAMETERS(void){};
	SOILPARAMETERS(int);
	virtual ~SOILPARAMETERS() {};
		
	char N [30];
		
    float alpha;	// parameters for volume-to-
    float beta;		//  potential conversion
    float thetaR;	//  by van-Genuchten equation
    float thetaS;
	
    float EvapoO;
    float EvapoA1;
		
	float DepthO;
	float DepthA1;				
	float DepthA2;
	float DepthA3;
	float DepthA4;
	
	bool  doRunon;
    float infRateShrub;
    float infRateHerb;
    float infRateBare;
	float deltaInfRate;
	float permeabilityA; // approximately correlated to clay content
    float permeabilityC;
    float throughfall; 
    NSupplyQ NSupply;
    
	virtual void documentation (char* filename) const;
		
  protected:
	void setForAllTypes(void);
};

class cSPEnJaqob : public SOILPARAMETERS
{
	public:
		cSPEnJaqob(void);
		~cSPEnJaqob(){};
};

class cSPMaththa : public SOILPARAMETERS
{
	public:
		cSPMaththa(void);
		~cSPMaththa(){};
};

class cSPBetGubrin : public SOILPARAMETERS
{
	public:
		cSPBetGubrin(void);
		~cSPBetGubrin(){};
};

class cSPLahab : public SOILPARAMETERS
{
	public:
		cSPLahab(void);
		~cSPLahab(){};
};

class cSPSedeBoqer : public SOILPARAMETERS
{
	public:
		cSPSedeBoqer(void);
		~cSPSedeBoqer(){};
};

class cSPSoilBatch : public SOILPARAMETERS
{
public:
		cSPSoilBatch(void);
		~cSPSoilBatch(){};
};
//----------------------
#endif
