/*
 *  SParameters.h
 *  intraspecific
 *
 *  Created by Martin Kšchy on Sat May 03 2003.
 *  Copyright (c) 2003 __MyCompanyName__. All rights reserved.
 *
 */

#include "Parameters.h"

#ifndef SeedParametersH
#define SeedParametersH

using namespace std;
//-------------------

class SEED_PARAMETERS
{
	public:
		SEED_PARAMETERS (void);
		virtual~SEED_PARAMETERS() {};
	
		char N [30];
	
		float survRate;	// gross loss rate, {0;1}
										//  includes seed predation, rot, etc.
										//  0.45 ± 0.2 
										//  derived from C.Lortie, pers.comm.
										//  higher values increase population
										//  persistence
										
		float survRateV;// variation of loss rate
										//  higher values increase 
										//  population persistence slightly
		
		  bool constSeedbank; // use the same number of seeds each year
		float iniSeedNbr; // mean number per square metre
										//  C.Lortie, pers. comm.
										//  species with light seeds (<0.08 mg) c. 100
										//  species with heavy seeds (>0.08 mg) c.  15
										
		float iniSeedNbrV; // variation of initial seedbank [0,1]
																										
		// parameters for hydro time eq. (Bradford 1995), 
		//  values after Meidan 1990
		//     PsiB50;	// threshold soil water potential at which 50%
										//  of the seeds germinate
		float PsiB50m;  // slope of PsiB50 = m*T+b
		float PsiB50b;	// intercept of PsiB50 = m*T+b
		float PsiB50S;	// std dev of PsiB50
										//  0.011
		float PsiBMin;	// minimum psi at which germination is possible
										//  -0.1585
		float thetaH;	// potential-sum above PsiB50 necessary for 
										//  germination
										//  0.14, calculated from Fig.2
		float Tmin;		// minimum T for calculating temperature sum
		float maxGerm;	// maximum germination fraction, [0;1]
						//  rate at > continuous field capacity
					    
		float DD;  // exponent for density dependence = slope in Goldberg et al. 2001
		float DDv;
		int DryDaysMax;	// number of consecutive days with soil potential > thetaH

                    
    float AX [8]; // no longer used
    float AY [8]; // no longer used
    float seedbankPersistence;
	float granivoryThreshold; // number of seeds/m2 when granivory sets in
	float ActivityV; // variability of germinability
	
    void setForAllSpecies (void);
	virtual void documentation (char* filename) const;
};


class cSPAveSteri : public SEED_PARAMETERS
{
public:
		cSPAveSteri(void);
		~cSPAveSteri() {};
};

class cSPBiscDid : public SEED_PARAMETERS
{
public:
		cSPBiscDid(void);
		~cSPBiscDid() {};
};

class cSPBraDist : public SEED_PARAMETERS
{
	public:
		cSPBraDist(void);
		~cSPBraDist() {};
};

class cSPBromFasc : public SEED_PARAMETERS
{
	public:
		cSPBromFasc(void);
		~cSPBromFasc() {};
};

class cSPCarrAnn : public SEED_PARAMETERS
{
	public:
		cSPCarrAnn(void);
		~cSPCarrAnn() {};
};

class cSPCriDeli : public SEED_PARAMETERS
{
public:
		cSPCriDeli(void);
		~cSPCriDeli() {};
};

class cSPFilDes : public SEED_PARAMETERS
{
	public:
		cSPFilDes(void);
		~cSPFilDes() {};
};

class cSPHippUni : public SEED_PARAMETERS
{
	public:
		cSPHippUni(void);
		~cSPHippUni() {};
};

class cSPHymCir : public SEED_PARAMETERS
{
	public:
		cSPHymCir(void);
		~cSPHymCir() {};
};

class cSPRebPin : public SEED_PARAMETERS
{
	public:
		cSPRebPin(void);
		~cSPRebPin() {};
};

class cSPSchisArab : public SEED_PARAMETERS
{
	public:
		cSPSchisArab(void);
		~cSPSchisArab() {};
};

class cSPStipCap : public SEED_PARAMETERS
{
	public:
		cSPStipCap(void);
		~cSPStipCap() {};
};

class cSPValHis : public SEED_PARAMETERS
{
	public:
		cSPValHis(void);
		~cSPValHis() {};
};

class cSPTypMes : public SEED_PARAMETERS
{
public:
		cSPTypMes(void);
		~cSPTypMes() {};
};

class cSPTypMed : public SEED_PARAMETERS
{
public:
		cSPTypMed(void);
		~cSPTypMed() {};
};

class cSPTypSem : public SEED_PARAMETERS
{
public:
		cSPTypSem(void);
		~cSPTypSem() {};
};

class cSPTypAri : public SEED_PARAMETERS
{
public:
		cSPTypAri(void);
		~cSPTypAri() {};
};
class cSPSeedBatch : public SEED_PARAMETERS
{
public:
		cSPSeedBatch(void);
		~cSPSeedBatch() {};
};

//-------------------
#endif
