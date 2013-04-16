/*
 *  Grid.cpp
 *  intraspecific
 *
 *  Created by Martin Köchy on Thu Feb 06 2003.
 *  Copyright (c) 2003 __MyCompanyName__. All rights reserved.
 *
 */

#include <iostream>
#include <fstream>
#include <math.h>
#include "MK_round.h"
#include "MyTime.h"
#include "Results.h"
#include "Plant.h"
#include "r250m.h"	//	random number generator
#include "Grid.h"


/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
*/

GRID::GRID (TIME* p_Time, GRIDPARAMETERS* p_GridP, RESULTS* p_Results, 
			SOILPARAMETERS* pSoilP, SEED_PARAMETERS* pSeedP,
			PLANT_PARAMETERS* pPlantP, CLIMATE* p_CLIMATE):pi(3.1415926), 
				theGridLengthC(gridLengthC), theGridLengthR(gridLengthR)
{
  pTIME = p_Time;
  pRESULTS = p_Results;
  pP = p_GridP;

  setPointers(pSoilP, pSeedP, pPlantP);
  setNeighbourhood();

  setVegetation(pP->shrubCover, pP->shrubRadius, p_CLIMATE->relLight);
}

GRID::~GRID()
{
//  PLANT::zeroNumberOfAllPlants(); obsolete 20030506
};


/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm

 _setPointers_ 
 
 Tells each grid cell the pointer for TIME, GRID and its coordinates.

 */
 
void GRID::setPointers(SOILPARAMETERS* pSoilP, SEED_PARAMETERS* pSeedP, PLANT_PARAMETERS* pPlantP) // in GRID constructor
{
  float zMoistureTopo = 1.0;
  float zStoniness = 0.0;
  
  for (int col = 0; col < theGridLengthC; col++)
    for (int row = 0; row < theGridLengthR; row++)
		{
		  theGrid [col] [row].setParameters(pSoilP);
		  theGrid [col] [row].setSpecies(pSeedP, pPlantP);
		  theGrid [col] [row].setSPointers(pTIME, this, col, row);

		  zMoistureTopo = 1.0 + vr250() * pP->moistureTopoV;
		  zStoniness = pP->stoniness + vr250() * pP->stoninessV;

		  theGrid [col] [row].setSCharacteristics(zMoistureTopo, zStoniness);
		}
}
/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
_setNeighbourhood_

 */

void GRID::setNeighbourhood(void) // in GRID constructor
{
  for (int col = 0; col < theGridLengthC; col++)
    for (int row = 0; row < theGridLengthR; row++)
		{
      theGrid [col] [row].setSNbrhood();
		}
}

/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm

_setVegetation_

 */
 
void GRID::setVegetation (int percShrub, int r_cm, float relLight)
{
  if (percShrub>0.0)
  {
	float shrubArea_hex = r_cm*r_cm*pi / cellArea;
	
	if ((shrubArea_hex >= theGridLengthC*theGridLengthR*cellArea) || percShrub == 100.0)
	{  for (int row = 0; row < theGridLengthR; row++)
		for (int col = 0; col < theGridLengthC; col++)
		  theGrid[col][row].setShrub(1, pP->shrubRadius, relLight);}
    else
    {
      int count = 0;
      int fail = 0;
      int IDshrub = 0;
      int ncells = int (percShrub/100.0*theGridLengthC*theGridLengthR);
      SOIL* pCell;
    
      int zCol = 0, zRow = 0;
      int hexlayer = NLayersInAreaRounded(shrubArea_hex);
      int overlap = 0;
        
      if (r_cm > 15) 
          overlap = int(5.0/pow(double(cellArea/pi), (double)0.5)); // cells
      else
          overlap = int(hexlayer * 0.3);
      
      while (count < ncells && fail < 100)
      {
        zCol = r250n(theGridLengthC);
        zRow = r250n(theGridLengthR);
        
        // check whether area is still free
        for (int r = 0; r <= (hexlayer - overlap); r++)
          for (int s = 0; s < (r?(6*r):1) ; s++)
            if ( (getNbrGPtr(zCol, zRow, s*(r?(360.0/(r*6.0)):0), r))->getVegetation() == shrub)
            {
              fail++;
              goto tryAgain; // area is not free, escape from inner loop
            }
  
        // area is free, "goto" not executed, set shrub
        fail = 0;   
        IDshrub++;
  
        for (int r = 0; r <= hexlayer; r++)
          for (int s = 0; s < (r?(6*r):1); s++)
          {  
            pCell = getNbrGPtr(zCol,zRow,s*(r?(360.0/(r*6.0)):0),r);
            if (pCell->getVegetation() != shrub)
              count++;
            pCell->setShrub(IDshrub, pP->shrubRadius, relLight);
          }
        
        // from "goto", area is not free, escape from loop
        tryAgain: continue;
      }
    }
	showShrubs();
  }
}


void GRID::showShrubs (void)
{
	std::ofstream ShrubDocu;
	ShrubDocu.open (pRESULTS->theResultsList, std::ios::app);

		ShrubDocu << "SSSSS" << endl;
		for (int row = 0; row < theGridLengthR; row++)
		{
			ShrubDocu << "   ";
			for (int col = 0; col < theGridLengthC; col++)
				if(theGrid[col][row].getVegetation() == shrub)
					ShrubDocu << char((theGrid[col][row].getShrubID()-1)%26 + 65) << " ";
				else
					ShrubDocu << ". ";
			ShrubDocu << endl;
		}
		ShrubDocu << endl;
		ShrubDocu << "TTTTT" << endl;
	ShrubDocu.close();
}

/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm

_getNbrGPtr_

This function returns the address of a cell given the direction in degrees and distance from the home cell. The spatial design is a periodical hexagonal lattice.

 */
 
SOIL* GRID::getNbrGPtr (int C, int R, float direction, int distance)
{
    int maxLength = 0;
    maxLength=getNCells(3);
    distance %= maxLength; // restrict distance to length of the longest edge

		if (distance == 0)
			return & theGrid [C] [R];
		else
		{
			int hexDirection, onHexEdge;
			float sectorAngle = 360.0/float(NCellsOnPerimeter(distance));
			
			while (direction>=360.0) { direction -= 360.0; } // restrict direction
	  
			 // centre on hexagon
			hexDirection = MK_round(direction/sectorAngle); // number of cells on perimeter
			onHexEdge = hexDirection % distance; // number of cells on edge
	  
      switch (int(hexDirection/distance))
			{
        case 0: R -= distance;
                C += onHexEdge; break;
        case 1: C += distance;
                R -= distance; 
                R += onHexEdge; break;
        case 2: C += distance; 
                C -= onHexEdge;
                R += onHexEdge; break;
        case 3: R += distance; 
                C -= onHexEdge; break;
        case 4: C -= distance;
                R += distance;
                R -= onHexEdge; break;
        case 5:	C -= distance;
                C += onHexEdge;
                R -= onHexEdge; break;
	  }
		
		// wrap around torus
    while (C < 0) C += theGridLengthC;	// necessary for rectangles with unequal edge length
			C %= theGridLengthC;							// because 'distance' is restricted to the longest
    while (R < 0) R += theGridLengthR;	// edge and not the shortest.
      R %= theGridLengthR;
      
    return & theGrid [C] [R];
  }
}


/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm

_updateGrid_

 This function provides a basic cycle over all grid cells.

 */
 
void GRID::updateGrid (int day, float TIndex, float T, float rain)
{   
	SOIL::setWeather(TIndex, T, rain);
	PLANT::zeroTotalDailyMass();
  

  for (int col = 0; col < theGridLengthC; col++)
    for (int row = 0; row < theGridLengthR; row++)
      theGrid [col] [row].updateSoil(day, row? theGrid[col][row-1].getRunoff(): 0.0);

}

void GRID::yearlyReset (void)
{
  for (int col = 0; col < theGridLengthC; col++)
    for (int row = 0; row < theGridLengthR; row++)
      theGrid [col] [row].getPSeedbank()->prepareNewYear(); 
  
  for (int col = 0; col < theGridLengthC; col++)
    for (int row = 0; row < theGridLengthR; row++)
      theGrid [col] [row].getPSeedbank()->zeroNewSeeds();  
}

/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
*/

long	GRID::getNCells (int d)
{
	if (d == 1) return theGridLengthC;
	else
		if (d == 2 ) return theGridLengthR;
  else // return max
    if (d == 3) return theGridLengthR>theGridLengthC?theGridLengthR:theGridLengthC;
	else
	{	std::cout << "Fehler in getNCells, d = " << d << std::endl; return 0;}
}	

/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
*/
