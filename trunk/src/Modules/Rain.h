/*
 *  Rain.h
 *  intraspecific
 *
 *  Created by Martin Kšchy on Thu Feb 06 2003.
 *  Copyright (c) 2003 __MyCompanyName__. All rights reserved.
 *
 */

#include <valarray>
#include <vector>
#include "Parameters.h"
#include "RainParameters.h"

//--------------------------------------------------------------------
#ifndef RainH
#define RainH
//--------------------------------------------------------------------

using namespace std;

class TIME; // advance declarations: Breymann, p. 196

class RAIN
{	
public:
		RAIN(void){}; 
		virtual ~RAIN(){};
		
		float	getStationID (void) const;	// code of Israel Meteorological
											//  Service divided by 100
		int	getStationYR (void) const;		// year (starting Aug 1) of 
											//  rain archive
		
		float getRain (int day);
		float getAnnualRain (void) const;
		virtual void drawYear (void) = 0;
		
		
	protected:
		int		theYear;
		int		theYearsInDB;
		float theAnnualRain;
		vector <valarray <float> > theRainDB;
		vector <valarray <float> > theRainID;
		TIME*	pTIME;				// pointer to the time object
		RAINPARAMETERS* pP;
		class FileNotFound {}; // for error handling
}; //------------------------------------------------------------------
class PreFile : public RAIN
{
public:
		PreFile(TIME* pTIME, RAINPARAMETERS* p_RainP);
  // first number in each col represents station ID, 
  //  the second  number calendar year;
  //  years must be in rows, days in columns;
  //  data must be separated by tabs
  // rain year starts July 31 = day 0
  // mean of annual rain volume
  // shape of distribution of annual rain
  ~PreFile(){};
  void	drawYear (void);
protected:
	void manipulateRain (valarray <float> & rain, float meanRain, valarray <float> & ID);
};

class ReGen : public RAIN
{
public: 
  ReGen (TIME* pTIME, RAINPARAMETERS* p_RainP);
  ~ReGen(){};
  void drawYear(void);
protected:
	float theDays[days_in_year];
	void calcRain(void);
	valarray <float> calcGauss (valarray <float> days, float height, float location, float width, float exponent = 2.0);
};

#endif
