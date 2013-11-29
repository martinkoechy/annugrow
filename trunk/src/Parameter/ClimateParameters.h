/*
 *  ClimateParameters.h
 *  intraspecific
 *
 *  Created by Martin Kšchy on Fri May 02 2003.
 *  Copyright (c) 2003 __MyCompanyName__. All rights reserved.
 *
 */
#include <string>

//------------------------------------------------------------------
#ifndef ClimateParametersH
#define ClimateParametersH
//------------------------------------------------------------------

class CLIMATE
{
	public:
	CLIMATE(void);
    CLIMATE(float, float, float, float);
	virtual ~CLIMATE() {};
	float getMeanT (void) const {return theMeanT;};
	float getRangeT (void) const {return theRangeT;};
	float getColdestDay (void) const {return theColdestDay;};
	void documentation (char* filename) const;	 
		
		char N [30];
		
		float theMeanT;
		float theRangeT;
		float theColdestDay;
		float relLight;
};

class cPCEnJaqob : public CLIMATE
{
public:
  cPCEnJaqob(void);
  ~cPCEnJaqob() {};
};

class cPCMaththa : public CLIMATE
{
public:
  cPCMaththa(void);
  ~cPCMaththa() {};
};

class cPCBetGubrin : public CLIMATE
{
public:
  cPCBetGubrin(void);
  ~cPCBetGubrin() {};
};

class cPCLahab : public CLIMATE
{
public:
  cPCLahab(void);
  ~cPCLahab() {};
};

class cPCSedeBoqer : public CLIMATE
{
public:
  cPCSedeBoqer(void);
  ~cPCSedeBoqer() {};
};

//------------------------------------------------------------------
#endif

