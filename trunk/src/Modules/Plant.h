/*
 *  Plant.h
 *  intraspecific
 *
 *  Created by Martin Kšchy on Thu Feb 06 2003.
 *  Copyright (c) 2003 __MyCompanyName__. All rights reserved.
 *
 */

#include "PlantParameters.h"
#include "Seeds.h"

//------------------------------------------------------------------
#ifndef PlantsH
#define PlantsH
//------------------------------------------------------------------


class TIME; // advance declarations
class SOIL;
class GRID;

class PLANT
{					
public:
  
		PLANT (void);
		virtual ~PLANT ();
		
		bool updatePlant (int day, bool hasGerminated);
		
		
		void setSPPointers (TIME* p_Time, GRID* p_Grid, 
							int col, int row, SOIL* location);
		
		void establish (void);
		// turns a germinated seed into an individual of a 
		//  certain species
		
		virtual float getOldMass (void) const;
		// returns the biomass of the day before
		
		virtual SPECIES getASpecies (void) const;
		// returns the species name
		
		virtual float getMass (void) const;
		// returns the current biomass
		
		virtual float getMaxMass (void) const;
		
		virtual short getAllSeeds (void) const;
		// returns the number of seeds produced in one year
		
		virtual int getCohorts (void) const;
		// returns the number of completed cohorts per year
		virtual bool isMature (void) const;
		// true if plant produced fruits;
		
		virtual bool isEstablished (void) const;
		virtual bool isSeedling (void) const;
		
		int getDay (void) const;
		// return the inner calendar
		
		static long getNumberOfPlants (void);
		// returns the total number of plants in the grid
		
		static long getNumberOfMaturePlants (void);
		// returns the total number of plants in the grid
		
		static float getTotalShootMass (void);
		// returns the total daily shoot mass in the grid
		
		void resourceUptake (void);
		
		static void zeroNumberOfAllPlants (void);
		static void zeroTotalDailyMass (void);
		void setParameters (PLANT_PARAMETERS*);
		
protected:
		  short	calcSeeds (void);
		
		float	relativeWetness (float potential_in_rooting_zone);
		float	growthRate (float potential_in_rooting_zone);
		float	suppression (void);
		void	wilting (void);
		void	reset (void);
		
		void	grow (float water_potential_in_rooting_zone);
		//calculates growth of biomass and seed production
		
		void	loseMass (float amount);
		// substracts biomass eaten by animals or lost to natural
		//  hazards
		
		void disperse (int number_of_seeds);
		
		PLANT_PARAMETERS* pP;
		
		bool theMatureUpdated;
		bool theIsMature;
		int theDay;
		int theCol, theRow;
		int theDiaspores, theCohort;
		
		float theMass; // mg
		float theMaxMass;
		float theReprTissue;
		float theOldMass;
		float theNLimitation;
		float theLLimitation;
		
		NSupplyQ getNSupply (void) const;
		NSupplyQ theSoilN;
		
		SOIL* pHere;
		SOIL* pSNeighbourhood[cNeighbourhood];
		PLANT* pTheNeighbours[cNeighbourhood];
		TIME* pTIME;
		GRID* pGRID;
		SPECIES theSpecies;
		static long theNumberOfAllPlants;
		static long theMatureIndividuals;
		static float theTotalDailyMass;
};

/*
 class cPAveSteri: public PLANT
 {
public:
   static const cPPAveSteri sASP;
   static long getNAllAvena() {return theNumberOfAllAvena;}
   static long getNMatureAvena() {return theMatureAvena;}
   
   cPAveSteri(void);
   ~cPAveSteri(){};
private:
	 static long theNumberOfAllAvena;
   static long theMatureAvena;
   SPECIES theSpecies;
 };
 
 class cPBiscDid: public PLANT
 {
public:
   static const cPPBiscDid sBDP;
   static long getNAllBiscutella() {return theNumberOfAllBiscutella;}
   static long getNMatureBiscutella() {return theMatureBiscutella;}
   
   cPBiscDid(void);
   ~cPBiscDid(){};
private:
	 static long theNumberOfAllBiscutella;
   static long theMatureBiscutella;
   SPECIES theSpecies;
 };
 
 class cPBraDist: public PLANT
 {
public:
   static const cPPBraDist sBrDP;
   static long getNAllBrachypodium() {return theNumberOfAllBrachypodium;}
   static long getNMatureBrachypodium() {return theMatureBrachypodium;}
   
   cPBraDist(void);
   ~cPBraDist(){};
private:
	 static long theNumberOfAllBrachypodium;
   static long theMatureBrachypodium;
   SPECIES theSpecies;
 };
 
 class cPBromFasc: public PLANT
 {
public:
   static const cPPBromFasc sBFP;
   static long getNAllBromus() {return theNumberOfAllBromus;}
   static long getNMatureBromus() {return theMatureBromus;}
   
   cPBromFasc(void);
   ~cPBromFasc(){};
private:
	 static long theNumberOfAllBromus;
   static long theMatureBromus;
   SPECIES theSpecies;
 };
 
 class cPCarrAnn: public PLANT
 {
public:
   static const cPPCarrAnn sCAP;
   static long getNAllCarrichtera() {return theNumberOfAllCarrichtera;}
   static long getNMatureCarrichtera() {return theMatureCarrichtera;}
   
   cPCarrAnn(void);
   ~cPCarrAnn(){};
private:
	 static long theNumberOfAllCarrichtera;
   static long theMatureCarrichtera;
   SPECIES theSpecies;
 };
 
 
 class cPCriDeli: public PLANT
 {
public:
   static const cPPCriDeli sCDP;
   static long getNAllCrithopsis() {return theNumberOfAllCrithopsis;}
   static long getNMatureCrithopsis() {return theMatureCrithopsis;}
   
   cPCriDeli(void);
   ~cPCriDeli(){};
private:
	 static long theNumberOfAllCrithopsis;
   static long theMatureCrithopsis;
   SPECIES theSpecies;
 };
 
 class cPFilDes: public PLANT
 {
public:
   static const cPPFilDes sFDP;
   static long getNAllFilDes() {return theNumberOfAllFilDes;}
   static long getNMatureFilDes() {return theMatureFilDes;}
   
   cPFilDes(void);
   ~cPFilDes(){};
private:
	 static long theNumberOfAllFilDes;
   static long theMatureFilDes;
   SPECIES theSpecies;
 };
 
 class cPHippUni: public PLANT
 {
public:
   static const cPPHippUni sHUP;
   static long getNAllHippUni() {return theNumberOfAllHippUni;}
   static long getNMatureHippUni() {return theMatureHippUni;}
   
   cPHippUni(void);
   ~cPHippUni(){};
private:
	 static long theNumberOfAllHippUni;
   static long theMatureHippUni;
   void setRGRmax (NSupplyQ soilN);
   SPECIES theSpecies;
 };
 
 class cPHymCir: public PLANT
 {
public:
   static const cPPHymCir sHCP;
   static long getNAllHymCir() {return theNumberOfAllHymCir;}
   static long getNMatureHymCir() {return theMatureHymCir;}
   
   cPHymCir(void);
   ~cPHymCir(){};
private:
	 static long theNumberOfAllHymCir;
   static long theMatureHymCir;
   void setRGRmax (NSupplyQ soilN);
   SPECIES theSpecies;
 };
 
 class cPRebPin: public PLANT
 {
public:
   static const cPPRebPin sRPP;
   static long getNAllRebPin() {return theNumberOfAllRebPin;}
   static long getNMatureRebPin() {return theMatureRebPin;}
   
   cPRebPin(void);
   ~cPRebPin(){};
private:
	 static long theNumberOfAllRebPin;
   static long theMatureRebPin;
 };
 
 class cPSchisArab: public PLANT
 {
public:
   static const cPPSchisArab sSAP;
   static long getNAllSchisArab() {return theNumberOfAllSchisArab;}
   static long getNMatureSchisArab() {return theMatureSchisArab;}
   
   cPSchisArab(void);
   ~cPSchisArab(){};
private:
	 static long theNumberOfAllSchisArab;
   static long theMatureSchisArab;
   SPECIES theSpecies;
 };
 
 class cPStipCap: public PLANT
 {
public:
   static const cPPStipCap sSCP;
   static long getNAllStipa() {return theNumberOfAllStipa;}
   static long getNMatureStipa() {return theMatureStipa;}
   
   cPStipCap(void);
   ~cPStipCap(){};
private:
	 static long theNumberOfAllStipa;
   static long theMatureStipa;
   SPECIES theSpecies;
 };
 
 class cPValHis: public PLANT
 {
public:
   static const cPPValHis sVHP;
   static long getNAllVala() {return theNumberOfAllVala;}
   static long getNMatureVala() {return theMatureVala;}
   
   cPValHis(void);
   ~cPValHis(){};
private:
	 static long theNumberOfAllVala;
   static long theMatureVala;
   SPECIES theSpecies;
 };
 
 class cPTypMes: public PLANT
 {
public:
   static const cPPTypMes sTMesP;
   static long getNAllTypMes() {return theNumberOfAllTypMes;}
   static long getNMatureTypMes() {return theMatureTypMes;}
   
   cPTypMes(void);
   ~cPTypMes(){};
private:
	 static long theNumberOfAllTypMes;
   static long theMatureTypMes;
   SPECIES theSpecies;
 };
 
 class cPTypMed: public PLANT
 {
public:
   static const cPPTypMed sTMedP;
   static long getNAllTypmed() {return theNumberOfAllTypMed;}
   static long getNMatureTypMed() {return theMatureTypMed;}
   
   cPTypMed(void);
   ~cPTypMed(){};
private:
	 static long theNumberOfAllTypMed;
   static long theMatureTypMed;
   SPECIES theSpecies;
 };
 
 class cPTypSem: public PLANT
 {
public:
   static const cPPTypSem sTSemP;
   static long getNAllTypSem() {return theNumberOfAllTypSem;}
   static long getNMatureTypSem() {return theMatureTypSem;}
   
   cPTypSem(void);
   ~cPTypSem(){};
private:
	 static long theNumberOfAllTypSem;
   static long theMatureTypSem;
   SPECIES theSpecies;
 };
 
 class cPTypAri: public PLANT
 {
public:
   static const cPPTypAri sTAriP;
   static long getNAllTypAri() {return theNumberOfAllTypAri;}
   static long getNMatureTypAri() {return theMatureTypAri;}
   
   cPTypAri(void);
   ~cPTypAri(){};
private:
	 static long theNumberOfAllTypAri;
   static long theMatureTypAri;
   SPECIES theSpecies;
 };
 */
#endif

