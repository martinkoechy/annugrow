/*
 *  PlantParameters.h
 *  intraspecific
 *
 *  Created by Martin Kšchy on Fri May 02 2003.
 *  Copyright (c) 2003 __MyCompanyName__. All rights reserved.
 *
 */
#include "Parameters.h"

#ifndef PlantParametersH
#define PlantParametersH

//----------------------------

class PLANT_PARAMETERS
{
	public:
		PLANT_PARAMETERS(void);
		virtual ~PLANT_PARAMETERS();
		
		char N [30];
				
		float MassSeed; // in mg

    float MassMax;		// maximal plant mass, mg
                        //  mass in rainy years; 
                        //  Loria & Noy-Meir 1980
                        
    float RGR_Max;		// maximal relative growth rate, 
                        //	day 7 to day 21;
                        //  Dyer et al. 2001
                        
    float RGR_shade;
    
    NSupplyQ N_tolerance;
                        
    float PsiGrowA;			// parameters for moisture-limited
    float PWP ; 					//  growth
                        //  Benecke, adapted
                        
    float MassFlowering;// threshold for seed production, mg,
                        //  smaller than mass in dry 
                        //  years;
                        //  Loria & Noy-Meir 1980
                        
    float MassFruit;	// mass (including supporting 
                        //  structures) necessary for 
                        //  the production of one seed, mg;
                        //  Loria & Noy-Meir 1980
	
	float MassEstablish; // design parameter, affects also runoff
	
	float MassAccessA2;
	float MassAccessA3;
	float MassAccessA4;
	float MassCompetition1;
	float MassCompetition2;
    float DDMortality; // density-dependent mortality                    
    float AllocationRepro;// the portion of total biomass 
                        //  allocated to reproductive 
                        //  structures;
                        //  Loria & Noy-Meir 1980
	  float Home;		  // percentage [0;1] of resources taken from home cell
												
		virtual void documentation (char* filename) const;
		virtual void setForAllSpecies(void);
		SPECIES name;
};


class cPPAveSteri : public PLANT_PARAMETERS
{
public:
  cPPAveSteri(void);
  ~cPPAveSteri() {};
};

class cPPBiscDid : public PLANT_PARAMETERS
{
		public:
				cPPBiscDid(void);
				~cPPBiscDid() {};
};

class cPPBraDist : public PLANT_PARAMETERS
{
public:
  cPPBraDist(void);
  ~cPPBraDist() {};
};

class cPPBromFasc : public PLANT_PARAMETERS
{
		public:
				cPPBromFasc(void);
				~cPPBromFasc() {};
};

class cPPCarrAnn : public PLANT_PARAMETERS
{
		public:
				cPPCarrAnn(void);
				~cPPCarrAnn() {};
};

class cPPCriDeli : public PLANT_PARAMETERS
{
public:
  cPPCriDeli(void);
  ~cPPCriDeli() {};
};

class cPPFilDes : public PLANT_PARAMETERS
{
		public:
				cPPFilDes(void);
        ~cPPFilDes() {};
};

class cPPHippUni : public PLANT_PARAMETERS
{
		public:
				cPPHippUni(void);
        ~cPPHippUni() {};
};

class cPPHymCir : public PLANT_PARAMETERS
{
		public:
				cPPHymCir(void);
        ~cPPHymCir() {};
};

class cPPRebPin : public PLANT_PARAMETERS
{
		public:
				cPPRebPin(void);
        ~cPPRebPin() {};
};

class cPPSchisArab : public PLANT_PARAMETERS
{
		public:
				cPPSchisArab(void);
        ~cPPSchisArab() {};
};

class cPPStipCap : public PLANT_PARAMETERS
{
		public:
				cPPStipCap(void);
        ~cPPStipCap() {};
};

class cPPValHis : public PLANT_PARAMETERS
{
		public:
				cPPValHis(void);
        ~cPPValHis() {};
};

class cPPTypMes : public PLANT_PARAMETERS
{
public:
  cPPTypMes(void);
  ~cPPTypMes() {};
};

class cPPTypMed : public PLANT_PARAMETERS
{
public:
  cPPTypMed(void);
  ~cPPTypMed() {};
};

class cPPTypSem : public PLANT_PARAMETERS
{
public:
  cPPTypSem(void);
  ~cPPTypSem() {};
};

class cPPTypAri : public PLANT_PARAMETERS
{
public:
  cPPTypAri(void);
  ~cPPTypAri() {};
};

class cPPPlantBatch : public PLANT_PARAMETERS
{
public:
  cPPPlantBatch(void);
  ~cPPPlantBatch() {};
};


//----------------------------
#endif

