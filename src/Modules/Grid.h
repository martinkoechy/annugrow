/*
 *  Grid.h
 *  intraspecific
 *
 *  Created by Martin Kšchy on Thu Feb 06 2003.
 *  Copyright (c) 2003 __MyCompanyName__. All rights reserved.
 *
 */

#include "Soil.h"
#include "Results.h"
#include "GridParameters.h"

//------------------------------------------------------------------
#ifndef GridH
#define GridH
//------------------------------------------------------------------

class TIME;
class RESULTS;

class GRID
{
  public:
	GRID (TIME* p_TIME, GRIDPARAMETERS* pGridP, 
		RESULTS* p_Results, 
		SOILPARAMETERS* pSoilP, SEED_PARAMETERS* pSeedP,
		PLANT_PARAMETERS* pPlantP, CLIMATE* p_CLIMATE);
	~GRID ();
  void	updateGrid (int day, float TIndex, float T, float rain);
		void	yearlyReset (void);
		long	getNCells (int dimension);
		SOIL*	getNbrGPtr (int X, int Y,
							float	direction = 0.0, int distance = 0);
        
  private:
		const float pi;
        const int theGridLengthC;
        const int theGridLengthR;
		
        void 	setPointers (SOILPARAMETERS*, 
							 SEED_PARAMETERS* pSeedP, PLANT_PARAMETERS* pPlantP);
		void	setNeighbourhood (void);
        void	setVegetation (int percentShrubs, int shrub_radius_cm = 15, float relLight = 1.0);
		void	showShrubs (void);
        TIME*	pTIME;
        RAIN*	pRAIN;
        RESULTS* pRESULTS;
		GRIDPARAMETERS* pP;
		
        SOIL	theGrid [gridLengthC] [gridLengthR];
        
		friend void RESULTS::saveParameters(CLIMATE*, SOILPARAMETERS*, 
											SEED_PARAMETERS*, PLANT_PARAMETERS*);
		class TorusError {}; // for error handling
};
#endif

