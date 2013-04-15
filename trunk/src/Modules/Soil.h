/*
 *  Soil.h
 *  intraspecific
 *
 *  Created by Martin Kšchy on Thu Feb 06 2003.
 *  Copyright (c) 2003 __MyCompanyName__. All rights reserved.
 *
 */

#include "Results.h"
#include "Seeds.h"
#include "Plant.h"
#include "Parameters.h"
#include "SoilParameters.h"

//------------------------------------------------------------------
#ifndef SoilH
#define SoilH
//------------------------------------------------------------------

class TIME;	// advance declarations
class GRID; 
						
class SOIL
{					
	public:
    static const float FKPsi_MPa;
		static const float PsiMin_MPa;
		static void calcRLEvapoRate (TIME* p_Time);
//z		static void setParameters (SOILTYPE soil);
		static void setWeather (float TIndex, float T, float rain);

		SOIL (void);
		~SOIL ();
		
		void	setParameters(SOILPARAMETERS* p_SoilP);
		void	setSPointers (TIME* p_Time, GRID* p_Grid, int col, int row);
		void	setSNbrhood (void);
		void	setSCharacteristics (float topoV, float stoniness);
		void	setSpecies (SEED_PARAMETERS* , PLANT_PARAMETERS*);
    void	setShrub (int ID, float r_cm, float relLight);
	void   setResourceShare (float weight);
		void	updateSoil (int day, float runon);
    int		getShrubID (void) const;
    float	getRunoff (void) const;
		float	getWaterO (void) const;
		float	getWaterA1 (void) const;
		float	getWaterA2 (void) const;
		float	getWaterA3 (void) const;
		float	getWaterA4 (void) const;
		float	getWaterC (void) const;
		float	getVolWaterO (void) const; // volumetric water content %
		float	getVolWaterA1 (void) const;
		float	getVolWaterA2 (void) const;
		float	getVolWaterA3 (void) const;
		float	getVolWaterA4 (void) const;
		float getOAWaterET (void) const;
		float	getPotentialO (void) const;
		float	getPotentialA1 (void) const;
		float	getPotentialA2 (void) const;
		float	getPotentialA3 (void) const;
		float	getPotentialA4 (void) const;
//		float	getPotentialC (void) const;
		float   getResourceShare (float weight) const;
    NSupplyQ getNSupply (void) const;
	float getRelLight (void) const;
		PLANT	getPlant (void) const;
		SEEDS	getSeedbank (void) const;
    cover getVegetation (void) const;
		PLANT*	getPPlant (void);
		SEEDS*	getPSeedbank (void);

	protected:
		static const float pi;
		friend void RESULTS::saveParameters (CLIMATE* pCLIMATE, SOILPARAMETERS* pSoilP, SEED_PARAMETERS* pSeedP, PLANT_PARAMETERS* pPlantP);
		static float theRainfall;
		static float theTIndex;
		static float theTemperature;
				
		float	addWater (float rainVolume, float runon);
		float	infiltration (float water_In);
		float calcDrainWater (float & water, float inflow, float saturated);
		float	FKVol (void) const;			// in mm or l
		float	evaporation (void);
		float	runoff (float rainVolume);	// in mm or l
		float	throughfall (float rainVolume);
		float	calcPotentialO (void) const;
		float	calcPotentialA1 (void) const;
		float	calcPotentialA2 (void) const;
		float	calcPotentialA3 (void) const;
		float	calcPotentialA4 (void) const;
		float	calcPotential (float theta, float depth, float volumetricFK) const; // depth in dm
		float	calcVolumetricWater (float psi, float thickness = 1.0) const; // thickness in dm
		float reducePotential(float water, float depth, float factor);
		void balancePsi(float & waterThis, float & waterUpper, 
										float depthThis, float depthUpper); // changed v2.6 20070126
		
		int		theCol;
		int		theRow;
    int		theShrubID;
	float theRelLight;
		float theDepthO;
		float theDepthA1;
		float theDepthA2;
		float theDepthA3;
		float theDepthA4;
		float theVolPcFK;

    float theRunoff;
		float	theOWater;		// in mm or l
		float	theA1Water;		// in mm or l
    float theA2Water;
		float	theA3Water;
		float	theA4Water;
		float	theCWater;			// in mm or l -- Water in ShrubRootLayer
		float theOAWaterET;		// water lost to evapotranspiration in OA layer, positive value

		float	theOWaterMin;
		float	theA1WaterMin;
		float	theA2WaterMin;
		float	theA3WaterMin;
		float	theA4WaterMin;

		float	theOCapacity;		// in mm or l
		float	theA1Capacity;	// in mm or l
		float	theA2Capacity;
		float	theA3Capacity;
		float	theA4Capacity;
			
		float	theTopoHeterogeneity;
		float theStoniness;
		float	theA1Evapo;
		float	theA2Evapo;
		float	theA3Evapo;
		float	theA4Evapo;
    
		float thePotO;
		float thePotA1;
		float thePotA2;
		float thePotA3;
		float thePotA4;
		float thePotC;
		float theNewResourceSum;	
  		float theOldResourceSum;	
  float theShrubR; // shrub radius in cm
		
		TIME*	pTIME;
		GRID*	pGRID;
		SEEDS*	pSeedbank;
		PLANT* 	pIndividual;
		SOILPARAMETERS* pP;
    cover theVegetation;
};
#endif
