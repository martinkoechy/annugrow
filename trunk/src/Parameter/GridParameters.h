/*
 *  GridParameters.h
 *  intraspecific
 *
 *  Created by Martin Köchy on Tue May 27 2003.
 *  Copyright (c) 2003 __MyCompanyName__. All rights reserved.
 *
 */

//------------------------------------------------------------------
#ifndef GridParametersH
#define GridParametersH
//------------------------------------------------------------------

class GRIDPARAMETERS
{
  public:
	GRIDPARAMETERS(void);
	~GRIDPARAMETERS() {};
	
	char N [30];
	
	int   theGridLengthC;
	int   theGridLengthR;    
	float moistureTopoV; // increases or decreases rain in SOIL by -x < random value < x *100%
	float stoniness; // [0;1]
	float stoninessV; // [0;1]
	int shrubCover; // [0;100] percent
	int shrubRadius; // cm
		
	void documentation (char* filename) const;	 
};
//------------------------------------------------------------------
#endif
