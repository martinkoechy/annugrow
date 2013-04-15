/*
 *  Results.h
 *  intraspecific
 *
 *  Created by Martin Kšchy on Thu Feb 06 2003.
 *  Copyright (c) 2003 __MyCompanyName__. All rights reserved.
 *
 */

#include "Parameters.h"
#include "SoilParameters.h"
#include "ClimateParameters.h"
#include "SeedParameters.h"
#include "PlantParameters.h"

//------------------------------------------------------------------
#ifndef ResultsH
#define ResultsH
//------------------------------------------------------------------

class RAIN;
class GRID;

class RESULTS
{	
	public:
		RESULTS (const char* baseFileName, int fileInput, const char* ID);
		~RESULTS ();
		
		void setTrial (int trial);
		void setPointers (RAIN* p_Rain, GRID* p_Grid);
		void zeroAnnualSums (void);
	  void copyDailyValues (int day);
	  void calcDailyValuesAcrossLattice (int day);
	  void calcAnnualValuesForEachCell(void);
	  void calcMeanAnnualValues (void);
	  void saveParameters (CLIMATE* pCLIMATE, SOILPARAMETERS* pSoilP, SEED_PARAMETERS* pSeedP, PLANT_PARAMETERS* pPlantP);
		void saveRainDocumentation (int year);
		bool saveDailyValues (int year);
		bool saveMeanYearlyValues (int year);
		void saveYearlyLattAsGrid (void);
    void saveYearlyRunoffAsGrid (void);
    void saveYearlyPotA1AsGrid (void);
    void saveYearlyPotA2AsGrid (void);
    void saveYearlyPotA3AsGrid (void);
    void saveYearlyPotA4AsGrid (void);
    void saveYearlyCWaterAsGrid (void);
    void saveVegCover (void);
		bool savePersistence (int maxYears, int year);
		
		class CellData
		{
		  public:
		  float psiO[gridLengthC][gridLengthR];
		  float psiA1[gridLengthC][gridLengthR];
		  float psiA2[gridLengthC][gridLengthR];
		  float psiA3[gridLengthC][gridLengthR];
		  float psiA4[gridLengthC][gridLengthR];
		  float watO[gridLengthC][gridLengthR];
		  float watA1[gridLengthC][gridLengthR];
		  float watA2[gridLengthC][gridLengthR];
		  float watA3[gridLengthC][gridLengthR];
		  float watA4[gridLengthC][gridLengthR];
		  float watC[gridLengthC][gridLengthR];
		  float runoff[gridLengthC][gridLengthR];
		  float runoffE[gridLengthC];
		  float	evtr[gridLengthC][gridLengthR];
		  int moist5[gridLengthC][gridLengthR];
		  int moist3[gridLengthC][gridLengthR];
		  int moist2[gridLengthC][gridLengthR];
		  SPECIES S[gridLengthC][gridLengthR];
		  float mass[gridLengthC][gridLengthR];
		  long seedl[gridLengthC][gridLengthR];
		  long indiv[gridLengthC][gridLengthR];
		  long mature[gridLengthC][gridLengthR];
		};
		
		CellData theDailyCell;
		CellData theAnnualSumCell;
		
		class DailyMeanValues
		{
		  public:
		  float DRain[days_in_year];
		  float DMPotentialO[days_in_year];
		  float DMPotentialA1[days_in_year];
		  float DMPotentialA2[days_in_year];
		  float DMPotentialA3[days_in_year];
		  float DMPotentialA4[days_in_year];
		 float DMWaterO[days_in_year];
		 float DMWaterA1[days_in_year];
		 float DMWaterA2[days_in_year];
		 float DMWaterA3[days_in_year];
		 float DMWaterA4[days_in_year];
		 float DMWaterC[days_in_year];
		  float DMRunoff[days_in_year];
		  float DMRunoffE[days_in_year];
		  float DMEvTr[days_in_year];
		  float   DMNbrMoistDays5[days_in_year];
		  float   DMNbrMoistDays3[days_in_year];
		  float   DMNbrMoistDays2[days_in_year];
		  float DMMassGPM2[days_in_year];
		  float DSeedlPM2[days_in_year];
		  float	DIndivPM2[days_in_year];
		  float DMaturePM2[days_in_year];
		};
		
		DailyMeanValues theMDaily;
		
		class AnnualMeanValues
		{
		  public:
		  float ARain;
		  float APotentialO;
		  float APotentialA1;
		  float APotentialA2;
		  float APotentialA3;
		  float APotentialA4;
		  float AWaterO;
		  float AWaterA1;
		  float AWaterA2;
		  float AWaterA3;
		  float AWaterA4;
		  float AWaterC;
		  float ARunoff;
		  float ARunoffE;
		  float AMoist5;
		  float AMoist3;
		  float AMoist2;
		  float AEvTr;
		  float AMassGPM2;
		  float ASeedlPM2;
		  float  AIndivPM2;
		  float AMaturePM2;
		  float ASeedsPM2;
		  float ASeedbankPM2;
		};
		  
		AnnualMeanValues theMAnnual;
		
		char theResultsDailyLattCol [48];
		char theResultsYearlyCellCol [48];
		char theResultsYearlyLattCol [48];
		char theResultsYearlyLattGrid [48];
		char theResultsYearlyRoGrid [48];
		char theResultsYearlyA1Grid [48];
		char theResultsYearlyA2Grid [48];
		char theResultsYearlyA3Grid [48];
		char theResultsYearlyA4Grid [48];
		char theResultsYearlyCWGrid [48];
		char theResultsPersist [48];
		char theResultsList [48];
		
		bool theDLCHeader;
		bool theYCCHeader;
		bool theYLCHeader;
		bool theYLGHeader;
		bool theRainHeader;
		bool thePerHeader;
		bool thePersistence;
		bool theFilebatch;
		
		int		theTrial;
		int	theGridLengthC;
		int	theGridLengthR;
		float theGridArea;
		float	theStationID;
		int		theStationYR;
		const char* theSimID;
		int theNbrOfMoistDays5[gridLengthC][gridLengthR];
		int theNbrOfMoistDays3[gridLengthC][gridLengthR];
		int theNbrOfMoistDays2[gridLengthC][gridLengthR];
		RAIN* pRAIN;
		GRID* pGRID;
		};

//------------------------------------------------------------------
#endif

