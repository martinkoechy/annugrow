/*
 *  GridParameters.h
 *  intraspecific
 *
 *  Created by Martin Kšchy on Tue May 27 2003.
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
	float moistureTopoV;
	float stoniness;
	float stoninessV;
	int shrubCover;
	int shrubRadius;
		
	void documentation (char* filename) const;	 
};

//------------------------------------------------------------------
#endif
