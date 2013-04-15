/*
 *  Rain.cpp
 *  intraspecific
 *
 *  Created by Martin Koechy on Thu Feb 06 2003.
 *  Copyright (c) 2003 __MyCompanyName__. All rights reserved.
 *
 */

#include <iostream>
#include <fstream>
#include "r250m.h"
#include "MyTime.h"		// for getday()
#include "Results.h"
#include "Rain.h"
#include <math.h>

/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm

_getRain_

This function returns the amount of rain fallen on the current day. The function obtains the current day from theTime. When a new year has started (i.e. day = 0), a different rain year is randomly selected.

*/

float RAIN::getRain (int day)
{
  float rain = theRainDB [theYear] [day];
  return rain;
}

//------------------------------------------------------------------

float RAIN::getAnnualRain (void) const
{
  return theAnnualRain;
}

//------------------------------------------------------------------

float RAIN::getStationID (void) const
{
  return theRainID [theYear][0];
}

//------------------------------------------------------------------

int RAIN::getStationYR (void) const
{
  return  int(theRainID [theYear][1]);
}

/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
*/
PreFile::PreFile(TIME* p_TIME, RAINPARAMETERS* p_RainP)
{
  pTIME = p_TIME;
  pP = p_RainP;
  theYear = -1;
  theYearsInDB = 0;
  theAnnualRain = 0.0;
  
  // the constructor reads in the rain data
  ifstream rainArchive;			// declaration of input file
  try
  {
	rainArchive.open((pP->getLongRFileName()).c_str());
	if (!rainArchive)				//Fehlerabfrage
	{
	  throw FileNotFound();
	}
  }
  catch(FileNotFound){std::cerr<< "Regendatei nicht gefunden!";};
  
  while (rainArchive.eof() == false)
  {
	valarray <float> singleYearID (0.0,2);
	valarray <float> singleYearData (0.0,days_in_year);
	
	rainArchive >> singleYearID[0]; // IMS code
	rainArchive >> singleYearID[1]; // year
	
	for (int d=0; d < days_in_year; d++)
	  rainArchive >> singleYearData[d];

	manipulateRain(singleYearData, pP->meanAP, singleYearID);

	theRainDB.push_back(singleYearData);
	theRainID.push_back(singleYearID);
	
	theYearsInDB++;
  }
  
  rainArchive.close();  
}


/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
*/

void  PreFile::drawYear (void)
{
  theYear = r250n(theYearsInDB);
  theAnnualRain = (theRainDB[theYear]).sum();
}

/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
*/

void PreFile::manipulateRain (valarray <float> & rainyear, float mean, valarray <float> & ID)
{
  if (mean != -1) // this must be the code for "natural volume"
  {
    float annualRain = 0.0;
	annualRain = rainyear.sum();
    rainyear /= annualRain;
	rainyear *= mean;
	ID[1] += 1000;
  }
}

ReGen::ReGen (TIME* p_TIME, RAINPARAMETERS* p_RainP)
{ 
  pTIME = p_TIME;
  pP = p_RainP;
  theYear = 0;
  theAnnualRain = 0.0;
  theYearsInDB = 1;
  
  for (int i = 0; i < days_in_year; theDays[i] = i++);
  
  valarray <float> singleYearData (0.0,days_in_year);
  valarray <float> singleYearID (0.0,2);
  
  theRainDB.push_back(singleYearData);
  theRainID.push_back(singleYearID);
}

/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
*/

void ReGen::drawYear (void)
{
  calcRain(); 
  theAnnualRain = (theRainDB [theYear]).sum();
}

valarray <float> ReGen::calcGauss (valarray <float> days, float H, float X, float W, int d)
{
  /* R Code
# Gauss-Funktion für Ermittlung der Regenwahrscheinlichkeit und 
# der mittleren Regenmenge an einem Regentag
   gauss <- function (Tag, Amplitude, Lage, Breite, Exponent=2) {
	 Monat = (Tag/365*12 + 6 - Lage) %% 12 + Lage - 6
	 G = Amplitude*exp(-(Monat-Lage)^Exponent/(2*Breite^2))
	 return(G)
   }
   */
  days *= (12.0/365.0);
  days += (6.0 - X);
  for (int i = 0; i < days_in_year; i++)
	days[i] = fmod(days[i],12.0F);
  days += (X - 6.0);
  
  valarray <float> G = H * exp(-pow(days - X,d)/(2.0*W*W));
  return G;
}

void ReGen::calcRain (void)
{ 
  /* R Code
# --- Regenmaschine ---#
  Regen<-function (Jahre, AmplitudeR, LageR, BreiteR, AmplitudeV, LageV, BreiteV) {
	TM<-Tage(Jahre)
# W, dass es an einem Tag regnet:
	G<-gauss(TM, AmplitudeR, LageR, BreiteR)
	RT<-ifelse(runif(TM)<G & G>0.05, 1, 0)
# mittlere Regenmenge:
	RV<- gauss(TM, AmplitudeV, LageV, BreiteV, 4)
# tatsächliche Regenmenge:
	R<- RT * RV * -log(1-(runif(TM)))
	return(R)
  }
*/  
  valarray <float> days (theDays, days_in_year);
  valarray <float> rainProb (days_in_year);
  rainProb = calcGauss(days, pP->PAmplitude, pP->PLocation, pP->PWidth);

  valarray <float> rainfall (0.0, days_in_year);
  for (int i = 0; i < days_in_year; i++)
	if (dr250() < rainProb[i] && rainProb[i] > 0.05)
	  rainfall[i] = 1.0;
  
  valarray <float> meanRainVolume (days_in_year);
  meanRainVolume = calcGauss(days, pP->VAmplitude, pP->VLocation, pP->VWidth, 4);
  valarray <float> RegenVolume (days_in_year);
  valarray <float> zexp (days_in_year);
  for (int i = 0; i < days_in_year; i++)
	zexp[i] = dr250();
  zexp *= -1.0;
  zexp += 1.0;
  zexp = -log(zexp);
  
  RegenVolume = meanRainVolume;
  RegenVolume *= rainfall;
/*  for (int i = 0; i < days_in_year; i++)
	std::cout<<i<<"\t"<<RegenVolume[i]<<"\t"<<zexp[i]<<std::endl;
*/  RegenVolume *= zexp;

  theRainDB[0] = RegenVolume;
  theRainID[0][0] = 999; // Station-ID, wird hier nicht gebraucht
  theRainID[0][1] = 999; // Regenjahr, wird hier nicht gebraucht
  
}
