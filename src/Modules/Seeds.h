/*
 *  Seeds.h
 *  intraspecific
 *
 *  Created by Martin Kšchy on Thu Feb 06 2003.
 *  Copyright (c) 2003 __MyCompanyName__. All rights reserved.
 *
 */

#include "SeedParameters.h"

//----------------------------------------------------------------------------
#ifndef SeedsH
#define SeedsH
//----------------------------------------------------------------------------

// the number of immediate neighbours in a hexagonal lattice
const unsigned int cNeighbourhood = 3*(cSuppress_dist+cSuppress_dist*cSuppress_dist);

// advance declarations
class GRID;
class SOIL;
class TIME;
class SEED_PARAMETERS;

class SEEDS
{					
public:
		static long getNumberOfAllSeeds (void);
  // returns the total number of seeds in the grid
  
		static void zeroAllSeeds (void);
//		static const SEED_PARAMETERS sSP;
		
		SEEDS (void);
		virtual ~SEEDS ();
		
		void setSPPointers (TIME* p_Time, GRID* p_Grid, int col, int row, SOIL* location);
		
		// trigger seedbank processes		
		void updateSeedbank (int day, float T, float TIndex, 
							 float psi_of_surface_layer, bool Plant_established);
		
		void zeroNewSeeds (void);
		  
		// add the number of dispersed seeds to the seedbank
		void addSeeds (int number_of_seeds);
		
		// return the number of viable seeds in seedbank
		virtual long getNumber (void) const;
		
		// return the number of germinable seeds in seedbank	
		virtual long getGNumber (void) const;
		
		// return the number of dispersed seeds
		virtual long getNewSeeds (void) const;
		
		// return whether at least one seed has germinated
		virtual bool isGerminated (void) const;
		
		// return how many seeds are ready to germinate;
		virtual long getHowManyReady (int day) const;
		
		void setParameters (SEED_PARAMETERS*);
		void	prepareNewYear (void);

		
  protected:
		static 		 long theNumberOfAllSeeds;
		
		SEED_PARAMETERS* pP;
		void	initializeSeedbank(float NumberOfSeeds);
		float	controlDensity (long NumberOfReadySeeds);
		void	germination (void);
		long	predation (long newSeeds, double survivalRate, double survivalRateV);
		long	oldSeedbankSurvival (long number, double oSbRate);
		float	calcMeanPsi (float psi_of_surface_layer);
		float	calcHydroThermalTimeG (float psi_of_surface_layer, float temperature);
		float   calcHydroThermalTimeB (float psi_of_surface_layer, float temperature);
		float	activity (float TIndex);
		float	activity (int day);
	
		bool	theGerminated;
		long	theReady;
		long	theOldReady;
		long	theNumber; // number of seeds in seedbank per cell
		unsigned int	theNewSeeds; // seeds added to the seedbank
		unsigned int	theNGerminable; //non-dormant seeds
		int		theDay;
		int theRow;
		int theCol;
		TIME* pTIME;
		GRID* pGRID;
		SOIL* pHere;
		SOIL* pSNeighbourhood[cNeighbourhood];
		SEEDS* pTheNeighbours[cNeighbourhood];
		float	theTSumR;	// Tsum for after-ripening
		int		theDryDays;
		int		theWetDays;
		float	theTheta;
		float   thePsiB; // for germination of individual seeds
		float	theTSumG;	// Tsum for germination
};
/*
class cSAveSteri : public SEEDS
{
		public:
        static const cSPAveSteri sASP;
				cSAveSteri(void);
				~cSAveSteri(){};
		private:
//				static float activity (int day_of_year);
        static long theNumberofAvenaSeeds;
};

class cSBiscDid : public SEEDS
{
public:
  static const cSPBiscDid sBDP;
  cSBiscDid(void);
  ~cSBiscDid(){};
private:
	//				static float activity (int day_of_year);
	static long theNumberofBiscutellaSeeds;
};

class cSBraDist : public SEEDS
{
public:
  static const cSPBraDist sBrDP;
  cSBraDist(void);
  ~cSBraDist(){};
private:
	//				static float activity (int day_of_year);
	static long theNumberofBrachypodiumSeeds;
};

class cSBromFasc : public SEEDS
{
		public:
        static const cSPBromFasc sBFP;
				cSBromFasc(void);
				~cSBromFasc(){};
		private:
//				static float activity (int day_of_year);
        static long theNumberofBromFascSeeds;
};

class cSCarrAnn : public SEEDS
{
		public:
        static const cSPCarrAnn sCAP;
				cSCarrAnn(void);
				~cSCarrAnn(){};
		private:
//				static float activity (int day_of_year);
        static long theNumberofCarrAnnSeeds;
};

class cSCriDeli : public SEEDS
{
public:
  static const cSPCriDeli sCDP;
  cSCriDeli(void);
  ~cSCriDeli(){};
private:
	//				static float activity (int day_of_year);
	static long theNumberofCrithopsisSeeds;
};

class cSFilDes : public SEEDS
{
		public:
				static const cSPFilDes sFDP;
				cSFilDes(void);
				~cSFilDes(){};
		private:
//				static float activity (int day_of_year);
        static long theNumberofFilDesSeeds;
};

class cSHippUni : public SEEDS
{
		public:
				static const cSPHippUni sHUP;
				cSHippUni(void);
				~cSHippUni(){};
		private:
//				static float activity (int day_of_year);
        static long theNumberofHippUniSeeds;
};

class cSHymCir : public SEEDS
{
		public:
				static const cSPHymCir sHCP;
				cSHymCir(void);
				~cSHymCir(){};
		private:
//				static float activity (int day_of_year);
        static long theNumberofHymCirSeeds;
};

class cSRebPin : public SEEDS
{
		public:
				static const cSPRebPin sRPP;
				cSRebPin(void);
				~cSRebPin(){};
		private:
//				static float activity (int day_of_year);
        static long theNumberofRebPinSeeds;
};

class cSSchisArab : public SEEDS
{
		public:
				static const cSPSchisArab sSAP;
				cSSchisArab(void);
				~cSSchisArab(){};
		private:
//				static float activity (int day_of_year);
        static long theNumberofSchisArabSeeds;
};

class cSStipCap : public SEEDS
{
		public:
				static const cSPStipCap sSCP;
				cSStipCap(void);
				~cSStipCap(){};
		private:
//				static float activity (int day_of_year);
        static long theNumberofStipCapSeeds;
};

class cSValHis : public SEEDS
{
public:
  static const cSPValHis sVHP;
  cSValHis(void);
  ~cSValHis(){};
private:
	//				static float activity (int day_of_year);
	static long theNumberofValHisSeeds;
};

class cSTypMes : public SEEDS
{
public:
  static const cSPTypMes sTMesP;
  cSTypMes(void);
  ~cSTypMes(){};
private:
	//				static float activity (int day_of_year);
	static long theNumberofTypMesSeeds;
};
class cSTypMed : public SEEDS
{
public:
  static const cSPTypMed sTMedP;
  cSTypMed(void);
  ~cSTypMed(){};
private:
	//				static float activity (int day_of_year);
	static long theNumberofTypMedSeeds;
};

class cSTypSem : public SEEDS
{
public:
  static const cSPTypSem sTSemP;
  cSTypSem(void);
  ~cSTypSem(){};
private:
	//				static float activity (int day_of_year);
	static long theNumberofTypSemSeeds;
};

class cSTypAri : public SEEDS
{
public:
  static const cSPTypAri sTAriP;
  cSTypAri(void);
  ~cSTypAri(){};
private:
	//				static float activity (int day_of_year);
	static long theNumberofTypAriSeeds;
};

*/
#endif

