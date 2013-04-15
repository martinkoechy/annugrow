/*
 *  SParameters.cpp
 *  intraspecific
 *
 *  Created by Martin Kšchy on Sat May 03 2003.
 *  Copyright (c) 2003 __MyCompanyName__. All rights reserved.
 *
 */

#include <iostream>
#include <fstream>
#include <string>
#include "MK_round.h"
#include "SeedParameters.h"

void SEED_PARAMETERS::setForAllSpecies (void)
{
  constSeedbank = true; // set to 'false' for simulating population persistence
	iniSeedNbr =  15000.0;	// 200/m2
	iniSeedNbrV = 0.11; // ± 0.11 *100% < Marcelo's data 2002/2003
	survRate	= 0.30; //0.25; 0.74-0.78 Russi et al. 1992
	survRateV	=  0.05;		// 0.05
	seedbankPersistence = 0.9; //0.8;
	granivoryThreshold = 20000.0;
	DD =  0.77; // 1 + slope in Goldberg et al. 2001; no systematic variation with climate, changed 2.6.0
	DDv = 0.02; // 0.02
	PsiB50m	=  0.00;	// 0.033 from Allen et al. 2000
	PsiB50b	= -1.0;	// -1.325 from Allen et al. 2000
	PsiB50S	=  0.5;		// 0.345 from Allen et al. 2000
	thetaH		= 30.0; 	// 35 from Allen et al. 2000
	Tmin		=  0.0;		// 0 from Allen et al. 2000
	DryDaysMax	=  7;		// very long, 1 yr, J. Kigel. pers. comm
	// for irregular dormancy
	float aAX [8] = {0.0, 45.0, 105.0, 135.0, 165.0, 225.0, 285.0, 0.0};
	float aAY [8] = {0.2,  0.4,   0.7,   0.9,   0.7,   0.4,   0.1, 0.0};
	for (int i = 0; i < 8; i++)
	{
	  AX[i]=aAX[i]; AY[i] = aAY[i];
	}
	ActivityV	=  0.05;	// ±0.0
	maxGerm = 1.0;
}

void SEED_PARAMETERS::documentation (char* filename) const
{
  ofstream ParameterDocu;
  ParameterDocu.open (filename, std::ios::app);
  
  ParameterDocu << "------ Seed Parameters ------" << endl;
  ParameterDocu << "Species: \t" << N << endl;
  ParameterDocu << "constSeedbank: \t" << (constSeedbank?"yes":"no") << endl;
  ParameterDocu << "iniSeedNbr (seeds/m2): \t" << iniSeedNbr << endl;
  ParameterDocu << "iniSeedNbr rel. range ±[0,1]: \t" << iniSeedNbrV << endl;
  ParameterDocu << "persistence of old SB [0,1]: \t" << seedbankPersistence << endl;
  ParameterDocu << "survRate [0,1]: \t" << survRate << endl;
  ParameterDocu << "survRate range ±[0,1]: \t" << survRateV << endl;
  ParameterDocu << "granivory threshold (seeds/m2): \t" << granivoryThreshold << endl;
  ParameterDocu << "density control: \n";
  ParameterDocu << " exponent: \t" << DD << endl;
  ParameterDocu << " variation: \t" << DDv << endl;
  ParameterDocu << "PsiB50m: \t" << PsiB50m << endl;
  ParameterDocu << "PsiB50b: \t" << PsiB50b << endl;
  ParameterDocu << "PsiB50S: \t" << PsiB50S << endl;
  ParameterDocu << "PsiBMin: \t" << PsiBMin << endl;
  ParameterDocu << "thetaH: \t" << thetaH << endl;
  ParameterDocu << "Tmin: \t" << Tmin << endl;
  ParameterDocu << "DryDaysMax: \t" << DryDaysMax << endl;
  ParameterDocu << "maxGerm: \t" << maxGerm << endl;
//  ParameterDocu << "ActivityV: \t" << ActivityV << endl;
    
  ParameterDocu.close();
}

SEED_PARAMETERS::SEED_PARAMETERS(void)
{
  strcpy(N,"generic annual");
  setForAllSpecies();
}

cSPTypMes::cSPTypMes (void)
{
  strcpy(N,"typical mesic Mediterranean"); //Brachypodium, Avena
  setForAllSpecies();
  
  //iniSeedNbr =  38400.0;		// 2002-09, Marcelo
  //iniSeedNbr = 44000; // 2003-09, Marcelo
  iniSeedNbr = 30000.0; // mean 2001...2003
  DD =  0.77; DDv = 0.02; // 0.77 for 'En Ya'aqov 2002
  PsiB50m	=  0.00;	//
  PsiB50b	= -0.67;	// -1.4 etwa Mittelwert
  PsiB50S	=  0.5;		// 0.35 <Allen et al. 2000
  thetaH	= 23; 	// 120 etwa Mittelwert
  Tmin		=  0.0;		// 0 <Allen et al. 2000
  DryDaysMax	=  7;		// very long, 1 yr, J. Kigel. pers. comm
  
  maxGerm = 1.0; // 0.65: 2001, 2002: Marcelo
  ActivityV	=  0.05;	// ±0.0
  
  float aAX [8] = {0.0, 45.0, 105.0, 135.0, 170.0, 210.0, 285.0, 0.0};
  float aAY [8] = {0.2, 0.83, 0.5, 0.4, 0.4, 0.4, 0.4, 0.0}; // Bromus fasc.
  for (int i = 0; i < 8; i++)
  {
    AX[i]=aAX[i]; AY[i] = aAY[i];
  }
}

cSPTypMed::cSPTypMed (void)
{
  strcpy(N,"typical Mediterranean"); // Brachypodium, Avena sterilis, Crithopsis
  setForAllSpecies();
  
  //iniSeedNbr =  23000.0;		// 2002-09, Marcelo
  //iniSeedNbr = 16000.0;   // 2003-09, Marcelo
  iniSeedNbr = 17000.0; // mean 2001...2003
  
  DD = 0.77; DDv = 0.02; // 0.75 for Matta 2002
  PsiB50m	=  0;
  PsiB50b	= -0.86; // -1.33 etwa Mittelwert
  PsiB50S	=  0.5;	// Allen et al. 2000
  thetaH	= 28; 	// 120 Mittelwert
  Tmin		=  0.0;		// Allen et al. 2000
  DryDaysMax	=  7;   // very long, 1 yr, J. Kigel. pers. comm
  maxGerm = 1.0; // 0.75
	
  ActivityV	=  0.05;	// ±0.0
  float aAX [8] = {0.0, 45.0, 105.0, 135.0, 170.0, 225.0, 285.0, 0.0};
  float aAY [8] = {0.0,  0.20,  0.3,   0.4,  0.45,  0.35,  0.2,  0.0};
  for (int i = 0; i < 8; i++)
  {
    AX[i]=aAX[i]; AY[i] = aAY[i];
  }
}
cSPTypSem::cSPTypSem (void)
{
  strcpy(N,"typical semiarid");
  setForAllSpecies();
  
  // iniSeedNbr =  8000.0;		// 2002-09, Marcelo
  // iniSeedNbr = 18000.0;   // 2003-09, Marcelo
  iniSeedNbr = 11000.0; // mean 2001...2003
  DD = 0.77; DDv = 0.02; // 0.94 for Lahav 2002
  PsiB50m	=  0.00;	//
  PsiB50b	= -0.87;	// -1.07 © Katja Ts germination experiment
  PsiB50S	=  0.5;		// 0.35 <Allen et al. 2000
  thetaH	= 31.0; 	// 28.0 © Katja Ts germination experiment
  Tmin		=  0.0;		// 0 <Allen et al. 2000
  DryDaysMax	=  7;		// very long, 1 yr, J. Kigel. pers. comm
							//iniSeedNbr =  60000.0;		// 200/m2
  maxGerm = 1.0; // 0.8: 2001, 2002: Marcelo
//  survRate	=  0.5;	// 0.5 Lahav

  float aAX [8] = {0.0, 45.0, 75.0, 105.0, 170.0, 225.0, 285.0, 0.0};
  float aAY [8] = {0.0,  0.0,  0.4,   0.8,   0.8,  0.65,  0.0,  0.0};
  
  for (int i = 0; i < 8; i++)
  {
    AX[i]=aAX[i]; AY[i] = aAY[i];
  }
  ActivityV	=  0.05;	// ±0.0
}

cSPTypAri::cSPTypAri (void)
{
  strcpy(N,"typical arid");
  setForAllSpecies();
  
  //iniSeedNbr =  400.0;		// 400; 2002-09, Marcelo
  //iniSeedNbr = 1000.0;   // 2003-09, Marcelo
  iniSeedNbr = 500.0;// mean 2001...2003
  iniSeedNbrV = 0.5;		// 0.5; 2002-09, Marcelo
  DD = 0.77; DDv = 0.02; // 0.95 for SedeBoqer 2002
  PsiB50m	=  0.000;	// fitted to Kigel et al.; 0.0 from Allen et al. 2000
  PsiB50b	= -1.03;	// fitted to Kigel et al.; -0.73 from Allen et al. 2000
  PsiB50S	=  0.5;		// 0.33 from Allen et al. 2000
  thetaH	= 24.7; 	// 27 from Allen et al. 2000
  Tmin		=  0.0;		// 0 from Allen et al. 2000
  DryDaysMax	=  7;		// very long, 1 yr, J. Kigel. pers. comm
							//iniSeedNbr =  60000.0;		// 200/m2
  float aAX [8] = {0.0, 45.0, 105.0, 135.0, 165.0, 225.0, 285.0, 0.0};
  float aAY [8] = {0.0, 0.11, 0.12, 0.13, 0.14, 0.11, 0.07, 0.0};
  for (int i = 0; i < 8; i++)
  {
    AX[i]=aAX[i]; AY[i] = aAY[i];
  }
  maxGerm = 1.0; // 0.85: 2001, 2002: Marcelo
  ActivityV	=  0.05;	// ±0.0
}

cSPAveSteri::cSPAveSteri (void)
{
  strcpy(N,"Avena sterilis");
  setForAllSpecies();
  
//  iniSeedNbr =  10000.0;		// 200/m2
  
  PsiB50m	=  0.00;	//
  PsiB50b	= -1.0;	// guestimate
  PsiB50S	=  0.35;		// 0.35 <Allen et al. 2000
  thetaH	= 40.0; 	// guestimate
  Tmin		=  0.0;		// 0 <Allen et al. 2000
  DryDaysMax	=  7;		// very long, 1 yr, J. Kigel. pers. comm
							//iniSeedNbr =  60000.0;		// 200/m2
//  maxGerm = 0.96; // Kew, Adkins & Peters 2000, 
  ActivityV	=  0.05;	// ±0.0
  
  float aAX [8] = {0.0, 45.0, 105.0, 135.0, 170.0, 210.0, 270.0, 0.0};
  float aAY [8] = {0.0,  0.30,  0.6,   0.54,  0.24,  0.18,  0.12,0.0};
  for (int i = 0; i < 8; i++)
  {
    AX[i]=aAX[i]; AY[i] = aAY[i];
  }
}

cSPBiscDid::cSPBiscDid (void)
{
  strcpy(N,"Biscutella didyma");
  setForAllSpecies();
  
//  iniSeedNbr =  20000.0;		// 200/m2
  PsiB50m	=  0.00;	//
  PsiB50b	= -0.94;	// -0.94 © Katja Ts germination experiment
  PsiB50S	=  0.35;		// 0.35 <Allen et al. 2000
  thetaH		= 21.0; 	// 21.0 © Katja Ts germination experiment
  Tmin		=  0.0;		// 0 <Allen et al. 2000
  DryDaysMax	=  7;		// very long, 1 yr, J. Kigel. pers. comm
							//iniSeedNbr =  60000.0;		// 200/m2
  float aAX [8] = {0.0, 45.0, 105.0, 135.0, 170.0, 210.0, 270.0, 0.0};
  float aAY [8] = {0.0,  0.30,  0.6,   0.54,  0.24,  0.18,  0.12,0.0};// <Carrichtera annua, Kigel report
  for (int i = 0; i < 8; i++)
  {
    AX[i]=aAX[i]; AY[i] = aAY[i];
  }
//  maxGerm = 0.72; // Tielbšrger exp., 0.95 Marcelo pers. comm.
  ActivityV	=  0.05;	// ±0.0
}

cSPBraDist::cSPBraDist (void)
{
	strcpy(N,"Brachypodium distachyum");
  setForAllSpecies();
  
//  iniSeedNbr =  20000.0;		// 200/m2

	PsiB50m	=  0.033;	//  Allen et al. 2000
	PsiB50b	= -1.365;	// Allen et al. 2000
	PsiB50S	=  0.25;		// Allen et al. 2000
	thetaH		= 38.0; 	// Allen et al. 2000
	Tmin		=  0.0;		// Allen et al. 2000
	DryDaysMax	=  7;		// very long, 1 yr, J. Kigel. pers. comm
	maxGerm = 1.0; // Kew, Kigel et al. 2002
	ActivityV	=  0.05;	// ±0.0
	
	//iniSeedNbr =  60000.0;		// 200/m2
	float aAX [8] = {0.0, 45.0, 105.0, 135.0, 170.0, 225.0, 285.0, 0.0};
	float aAY [8] = {0.0,  0.20,  0.3,   0.4,  0.45,  0.35,  0.2,  0.0};
  for (int i = 0; i < 8; i++)
  {
    AX[i]=aAX[i]; AY[i] = aAY[i];
  }
}

cSPBromFasc::cSPBromFasc (void)
{
	strcpy(N,"Bromus fasciculatus");
  setForAllSpecies();

	PsiB50m	=  0.033;	// 0.033 Allen et al. 2000
	PsiB50b	= -1.325;	// -1.325 Allen et al. 2000
	PsiB50S	=  0.30;		// 0.3 Allen et al. 2000
	thetaH		= 30.0; 	// 30 Allen et al. 2000
	Tmin		=  0.0;		// 0 Allen et al. 2000
	DryDaysMax	=  7;		// very long, 1 yr, J. Kigel. pers. comm
	//iniSeedNbr =  200.0;		// 200/m2
	float aAX [8] = {0.0, 45.0, 105.0, 135.0, 170.0, 210.0, 285.0, 0.0};
  float aAY [8] = {0.2, 0.83, 0.5, 0.4, 0.4, 0.4, 0.4, 0.0};
  for (int i = 0; i < 8; i++)
  {
    AX[i]=aAX[i]; AY[i] = aAY[i];
  }
//  maxGerm = 0.98; // 0.98 Tielbšrger exp., 0.98 Marcelo exp.
	ActivityV	=  0.05;	// ±0.0
}

cSPCarrAnn::cSPCarrAnn (void)
{
	strcpy(N,"Carrichtera annua");
  setForAllSpecies();

	PsiB50m	=  0.0;	// fitted to Kigel et al.
	PsiB50b	= -1.4; // -1.43 < Allen et al. 2000, -1.09 © Katja Ts germination experiment
	PsiB50S	=  0.92;	// 0.92 < Allen et al. 2000
	thetaH	= 26.0; 	// 25 © Katja Ts germination experiment; 26 Allen et al. 2000
	Tmin		=  0.0;		// 0 Allen et al. 2000
	DryDaysMax	=  7;		// very long, 1 yr, J. Kigel. pers. comm
	//iniSeedNbr =  60000.0;		// 100/m2 Kigel et al. 2002
  float aAX [8] = {0.0, 45.0, 105.0, 135.0, 165.0, 185.0, 270.0, 0.0};
  float aAY [8] = {0.0, 0.06, 0.11, 0.10, 0.09, 0.03, 0.02, 0.0};
  for (int i = 0; i < 8; i++)
  {
    AX[i]=aAX[i]; AY[i] = aAY[i];
  }
//  maxGerm = 0.53; // Tielbšrger exp., 0.75 Marcelo exp.
	ActivityV	=  0.02;	// ±0.0
}

cSPCriDeli::cSPCriDeli (void)
{
  strcpy(N,"Crithopsis delileana");
  setForAllSpecies();
  
//  iniSeedNbr =  15000.0;		// 200/m2
  
  PsiB50m	=  0.00;	//
  PsiB50b	= -1.07;	// -1.07 © Katja Ts germination experiment
  PsiB50S	=  0.35;		// 0.35 <Allen et al. 2000
  thetaH		= 28.0; 	// 28.0 © Katja Ts germination experiment
  Tmin		=  0.0;		// 0 <Allen et al. 2000
  DryDaysMax	=  7;		// very long, 1 yr, J. Kigel. pers. comm
							//iniSeedNbr =  60000.0;		// 200/m2
//  maxGerm = 0.91; // Kigel et al. 2002
  
  float aAX [8] = {0.0, 45.0, 75.0, 105.0, 170.0, 225.0, 285.0, 0.0};
  float aAY [8] = {0.0,  0.0,  0.4,   0.8,   0.8,  0.65,  0.0,  0.0};
  for (int i = 0; i < 8; i++)
  {
    AX[i]=aAX[i]; AY[i] = aAY[i];
  }
  ActivityV	=  0.05;	// ±0.0
}

cSPFilDes::cSPFilDes (void)
{
	strcpy(N,"Filago desertorum");
   setForAllSpecies();
   //iniSeedNbr =  60000.0;		// 400/m2

	PsiB50m	=  0.0;
	PsiB50b	= -1.16; // -0.305 < Meidan 1990, -1.16 © Katja Ts germination experiment
	PsiB50S	=  0.344;	// 0.037 < Meidan 1990, 0.344 < Allen et al. 2000
	thetaH	= 57.0; 	// 12.6 < Meidan 1990, 57 © Katja Ts germination experiment;
	Tmin		=  0.0;		// 0;
	DryDaysMax	= 7;		// 7, my guess
  float aAX [8]  = {0.0, 45.0, 75.0, 105.0, 165.0, 195.0, 240.0, 0.0};
  float aAY [8]  ={0.0,  0.2,   0.3,   0.4,   0.4,   0.1, 0.0, 0.0};
  for (int i = 0; i < 8; i++)
  {
    AX[i]=aAX[i]; AY[i] = aAY[i];
  }
//  maxGerm = 0.40; // Tielbšrger exp., 0.86 Marcelo exp.
	ActivityV	=  0.05;	// ±0.0
}

cSPHippUni::cSPHippUni (void)
{
	strcpy(N,"Hippocrepis unisiliquosa");
   setForAllSpecies();

	PsiB50m	=  0.0;	// 
	PsiB50b	= -0.51;	// -0.5 © Katja Ts germination experiment
	PsiB50S	=  0.345;		// 0.345 < Allen et al. 2000
	thetaH		= 35.0; 	// 35.0 © Katja Ts germination experiment
	Tmin		=  0.0;		// 0 < Allen et al. 2000
	DryDaysMax	=  7;		// very long, 1 yr, J. Kigel. pers. comm
	//iniSeedNbr =  60000.0;		// 200/m2
  float aAX [8] = {0.0, 65.0, 105.0, 135.0, 165.0, 195.0, 225.0, 0.0};
  float aAY [8] = {0.0, 0.03, 0.13,   0.09, 0.08,  0.125, 0.01, 0.0};
  for (int i = 0; i < 8; i++)
  {
    AX[i]=aAX[i]; AY[i] = aAY[i];
  }
//  maxGerm = 0.13; // Tielbšrger exp., 0.48 Marcelo exp.
	ActivityV	=  0.01;	// ±0.0
}

cSPHymCir::cSPHymCir (void)
{
	strcpy(N,"Hymenocarpos circinnatus");
   setForAllSpecies();

	PsiB50m	=  0.00;		//
	PsiB50b	= -0.51;		// Hipp uni
	PsiB50S	=  0.345;	// Hipp uni
  thetaH		= 35.0; // Hipp uni
	Tmin		=  0.0;		// 0 < Allen et al. 2000
	DryDaysMax	=  7;		// very long, 1 yr, J. Kigel. pers. comm
	//iniSeedNbr =  60000.0;		// 200/m2
  float aAX [8] = {0.0, 45.0, 105.0, 135.0, 165.0, 225.0, 285.0, 0.0};
  float aAY [8] = {0.0, 0.00, 0.013, 0.175, 0.013, 0.025, 0.01, 0.0};
  for (int i = 0; i < 8; i++)
  {
    AX[i]=aAX[i]; AY[i] = aAY[i];
  }
//  maxGerm = 0.31; // Kigel report 2002, 0.50 Marcelo exp.
	ActivityV	=  0.05;	// ±0.0
}

cSPRebPin::cSPRebPin (void)
{
	strcpy(N,"Reboudia pinnata");
  setForAllSpecies();

  //iniSeedNbr =  400.0;		// 200/m2
//	iniSeedNbrV = 0.5;		// 2002-09, Marcelo
	PsiB50m	=  0.0;
	PsiB50b	= -0.92; // -0.351 <Meidan 1990, -0.92 © Katja Ts germination experiment
	PsiB50S	=  0.345;	// 0.189 <Meidan 1990; < Allen et al. 2000
	thetaH	= 23.0; 	// 41.4 <Meidan 1990, 23.0 © Katja Ts germination experiment
	Tmin		=  0.0;		// 0;
	DryDaysMax	=  7;		// 7, my guess
  float aAX [8] = {0.0, 45.0, 75.0, 105.0, 135.0, 185.0, 250.0, 0.0};
  float aAY [8] = {0.0, 0.1, 0.3, 0.54, 0.54, 0.1, 0.0, 0.0};
  for (int i = 0; i < 8; i++)
  {
    AX[i]=aAX[i]; AY[i] = aAY[i];
  }
//  maxGerm = 0.76; // Kigel report 2002
	ActivityV	=  0.05;	// ±0.0			
}

cSPSchisArab::cSPSchisArab (void)
{
	strcpy(N,"Schismus arabicus");
  setForAllSpecies();

	PsiB50m	=  0.0;
	PsiB50b	= -0.437; // -0.437, derived from Meidan 1990
	PsiB50S	=  0.345;	// 0.01;
	thetaH	= 32.4; 	// 32.4;
	Tmin		=  0.0;		// 0;
	DryDaysMax	=  7;		// 7, my guess
	//iniSeedNbr =  60000.0;		//400/m2
  float aAX [8] = {0.0, 45.0, 75.0, 105.0, 135.0, 185.0, 250.0, 0.0};
  float aAY [8] = {0.0, 0.1, 0.3, 0.43, 0.43, 0.1, 0.0, 0.0};
  for (int i = 0; i < 8; i++)
  {
    AX[i]=aAX[i]; AY[i] = aAY[i];
  }
//  maxGerm = 0.35; // Meidan 1990, 1.0 Marcelo exp.
	ActivityV	=  0.05;	// ±0.0			
}

cSPStipCap::cSPStipCap (void)
{
	strcpy(N,"Stipa capensis");
  setForAllSpecies();

	PsiB50m	=  0.000;	// fitted to Kigel et al.; 0.0 from Allen et al. 2000
	PsiB50b	= -0.73;	// fitted to Kigel et al.; -0.73 from Allen et al. 2000
	PsiB50S	=  0.33;		// 0.33 from Allen et al. 2000
	thetaH		= 27.0; 	// 27 from Allen et al. 2000
	Tmin		=  0.0;		// 0 from Allen et al. 2000
	DryDaysMax	=  7;		// very long, 1 yr, J. Kigel. pers. comm
	//iniSeedNbr =  60000.0;		// 200/m2
  float aAX [8] = {0.0, 45.0, 105.0, 135.0, 165.0, 225.0, 285.0, 0.0};
  float aAY [8] = {0.0, 0.11, 0.12, 0.13, 0.14, 0.11, 0.07, 0.0};
  for (int i = 0; i < 8; i++)
  {
    AX[i]=aAX[i]; AY[i] = aAY[i];
  }
//  maxGerm = 0.80; // Tielbšrger exp., 0.9 Marcelo exp.
	ActivityV	=  0.05;	// ±0.0
}


cSPValHis::cSPValHis (void)
{
	strcpy(N,"Valantia hispida");
  setForAllSpecies();

	PsiB50m	=  0.0;	// 0.0 from Allen et al. 2000
	PsiB50b	= -0.9;	// -0.9 < Katja's germination exp.
	PsiB50S	=  0.345;		// 0.345 median < Allen et al. 2000
	thetaH		= 46.0; 	// 46 from Allen et al. 2000
	Tmin		=  0.0;		// 0 < Katja's germination exp.
	DryDaysMax	=  7;		// very long, 1 yr, J. Kigel. pers. comm
	//iniSeedNbr =  60000.0;		// 200/m2
  float aAX [8] = {0.0, 45.0, 105.0, 135.0, 165.0, 225.0, 285.0, 0.0};
  float aAY [8] = {0.0, 0.2 ,  0.5 ,  0.76,  0.5 , 0.2 ,  0.05, 0.0};
  for (int i = 0; i < 8; i++)
  {
    AX[i]=aAX[i]; AY[i] = aAY[i];
  }
//  maxGerm = 0.76; // Tielbšrger exp., 0.98 Marcelo exp.
	ActivityV	=  0.05;	// ±0.0
}

cSPSeedBatch::cSPSeedBatch (void)
{
  strcpy(N,"Batch input");
  setForAllSpecies();  
}
