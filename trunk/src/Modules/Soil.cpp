/*
 *  Soil.cpp
 *  intraspecific
 *
 *  Created by Martin Köchy on Thu Feb 06 2003.
 *  Copyright (c) 2003 __MyCompanyName__. All rights reserved.
 *
 */

#include <math.h> // for exp(), sqrt(), sin(), fmod()
#include <iostream>
#include "MK_round.h"
#include "MyTime.h"
#include "Grid.h"
#include "Soil.h"

/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
*/

const float SOIL::pi = 3.1415926;
const float SOIL::FKPsi_MPa = maxPsi; // geändert 2005-01-28
const float SOIL::PsiMin_MPa = -150.0;
float SOIL::theTIndex = 0.0;
float SOIL::theTemperature = 20.0;
float SOIL::theRainfall = 0.0;

void SOIL::setWeather(float TIndex, float T, float rain)
{
  theTIndex = TIndex, theTemperature = T, theRainfall = rain;
}


SOIL::SOIL (void)
{
  theTopoHeterogeneity = 1.0; // reset in setSCharacteristics(), called from GRID
  theStoniness = 0.0; // reset in setSCharacteristics(), called from GRID
  theRelLight = 1.0;
}

SOIL::~SOIL ()
{ delete pSeedbank; delete pIndividual;}

/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
  some parameters cannot be initialized in constructor because some variables (in P)  are not known yet
*/

void SOIL::setParameters(SOILPARAMETERS* p_SoilP)
{
  pP = p_SoilP;
  
  // calculate effective layer depth taking into account stones
  theDepthO  = pP->DepthO  * (1.0-theStoniness);
  theDepthA1 = pP->DepthA1 * (1.0-theStoniness);
  theDepthA2 = pP->DepthA2 * (1.0-theStoniness);
  theDepthA3 = pP->DepthA3 * (1.0-theStoniness);
  theDepthA4 = pP->DepthA4 * (1.0-theStoniness);
  
  theVolPcFK = FKVol();
  
  // calculate capacity of soil layers assuming an average capacity
  theOCapacity  = theDepthO * theVolPcFK;
							// capacity of top 0.2 dm of soil

  theA1Capacity = theDepthA1 * theVolPcFK;
							// capacity of soil below surface
  theA2Capacity = theDepthA2 * theVolPcFK;
							// capacity of soil below surface
  theA3Capacity = theDepthA3 * theVolPcFK;
			// others
  theA4Capacity = theDepthA4 * theVolPcFK;
  
  theOWaterMin = calcVolumetricWater(PsiMin_MPa,theDepthO);
  theA1WaterMin = calcVolumetricWater(PsiMin_MPa,theDepthA1);
  theA2WaterMin = calcVolumetricWater(PsiMin_MPa,theDepthA2);
  theA3WaterMin = calcVolumetricWater(PsiMin_MPa,theDepthA3);
  theA4WaterMin = calcVolumetricWater(PsiMin_MPa,theDepthA4);
  
  theOWater = theOWaterMin;
  theA1Water = theA1WaterMin;
  theA2Water = theA2WaterMin;
  theA3Water = theA3WaterMin;
  theA4Water = theA4WaterMin;
  theCWater = 0.0;
  
  thePotO  =  PsiMin_MPa;
  thePotA1 =  PsiMin_MPa;
  thePotA2 =  PsiMin_MPa;
  thePotA3 =  PsiMin_MPa;
  thePotA4 =  PsiMin_MPa;
  
}

/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm

_setSPointers_

Sets some pointers that are used by other functions in SOIL or that are passed on to PLANT and SEED. The function is called from within the GRID constructor.

*/

void SOIL::setSPointers (TIME* p_Time, GRID* p_Grid, int col, int row)
{
	pTIME = p_Time;
	pGRID = p_Grid;
	theCol = col;
	theRow = row;
}

void SOIL::setSNbrhood(void)
{
  pIndividual->setSPPointers(pTIME, pGRID, theCol, theRow, this);
  pSeedbank->setSPPointers(pTIME, pGRID, theCol, theRow, this);
}

/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
_setSpecies_
*/

void SOIL::setSpecies(SEED_PARAMETERS* pSeedP, PLANT_PARAMETERS* pPlantP)
{
  pSeedbank = new SEEDS; pIndividual = new PLANT;
  pSeedbank->setParameters(pSeedP); pIndividual->setParameters(pPlantP);
}

/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
_setShrub_
*/
void SOIL::setShrub (int ID, float r, float relLight)
{
  theVegetation = shrub;
  theShrubID = ID;
  theShrubR = r;
  theRelLight = relLight;
}

/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm

_updateSoil_

Encapsulation function for all processes related to soil

*/

void SOIL::updateSoil (int day, float runon)
{ 
  if(!pP->doRunon) runon = 0.0; // exclude runon to next cell for certain scenarios
  bool isGrowing = false;
  theOAWaterET = 0.0;
  theOldResourceSum = theNewResourceSum;
  theNewResourceSum = 0.0;
  
  if (day == 0)
  {  theCWater = 0.0;
    if (theVegetation == hus) theVegetation = shrub;
		else if (theVegetation == herb) theVegetation = bare;
  }
  
  theRunoff = addWater(theRainfall, runon);

  theOAWaterET += evaporation();
    
 
  // remove for soil testing
  isGrowing =
      pIndividual->updatePlant(day, pSeedbank->isGerminated());

			// plant growth before germination so that seeds must wait 
			//  at least one day before they start growing
	pSeedbank->updateSeedbank(day, theTemperature, theTIndex, getPotentialO(), isGrowing);
  
  if (pIndividual->getMass() > 10.0)
    if (theVegetation >= shrub)
      theVegetation = hus;
    else
      theVegetation = herb;
 // end: remove for soil testing

}


/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm

_addWater_

This function adds infiltrating water to the water stored in the soil cylinder; the field capacity is measured in mm = vol% (see Kuntze et al. 1988, p. 238, Tab. 72);

*/

float SOIL::addWater (float rainVolume, float runon)
{
	float surfaceWater = 0.0;
	
  if (theVegetation == shrub)
    surfaceWater = runon + throughfall(rainVolume); // included in runoff measurements
  else
    surfaceWater = runon + rainVolume;
	
  // effect of variable infiltration rates and surface topography
	if (surfaceWater < 10.0)
	  surfaceWater *= theTopoHeterogeneity;

	surfaceWater = runoff(surfaceWater);
	return surfaceWater;
}


/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm

_throughfall_

effect of shrubs

*/

float SOIL::throughfall (float water)
{
  float throughfall = 0.0;
//  throughfall = pP->throughfall * water; //; // 0.7 = Belmonte Saerrato & Romero Diaz 1998
//  theOAWaterET += ((1.0 - pP->throughfall) * water);
	throughfall = water > 0.4? water - 0.4 : 0.0;
	theOAWaterET+= water - throughfall; // LAI ≈ 0.8 (see Wadiscape), leaves retain c. 0.5 mm of water
	
  return throughfall;
}


/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm

_runoff_

This function provides space for developing a run-off model. 
The return value is the amount of water that infiltrates the soil.

*/

float SOIL::runoff (float water)
{
  float drain  = 0.0;
  float runoff = 0.0;
  float infRate = 0.0;
  float moistureV [2] = {theA1Water/theA1Capacity, theA2Water/theA2Capacity}; // changed 20041201
  
//---- overland flow generated by excess over infiltration (Hortonian)
  
  float minMoisture = MK_min(moistureV,2);
  
  if (theVegetation >= shrub) {    // under shrubs or edge
    infRate = pP->infRateShrub;
	infRate = infRate - 0.8 * pP->deltaInfRate * minMoisture; }
  else if (theVegetation == herb) {
    infRate = pP->infRateHerb;
	infRate = infRate - 0.9 * pP->deltaInfRate * minMoisture; }
  else
  {  infRate = pP->infRateBare;
	infRate = infRate - 1.0 * pP->deltaInfRate * minMoisture; // according to Cerdà & Sara 1998
  }
  drain = infRate * water;
  
  runoff = water - drain;
  runoff = runoff<0.0?0.0:runoff; // check
  
//---- overland flow generated by saturation
	runoff += infiltration (drain);
  
	return runoff;
}


/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm

_infiltration_

This function carries out the infiltration process. Infiltration is immediate. The upper 
 layer is filled up first, then the next layer is filled (tipping-bucket model). The 
 return value could be used for modelling groundwater recharge. "Abflussbildung und 
 Bodenfeuchtedynamik zwischen Feldkapazität und Sättigung läuft nach unseren Messungen 
 (wir arbeiten in 5-Minutenauflösung) in der Hangskale auf alle Fälle in wenigen Minuten 
 ab." (Jens Lange, Freiburg). Therefore, soil water drops immediately to FK after 
 infiltration. (changed in version 2.4.6)
*/

float SOIL::infiltration (float drainWater)
{
  drainWater = calcDrainWater(theOWater, drainWater, theOCapacity); // to next layer
  drainWater = calcDrainWater(theA1Water, drainWater, theA1Capacity);
  drainWater = calcDrainWater(theA2Water, drainWater, theA2Capacity);			
  drainWater = calcDrainWater(theA3Water, drainWater, theA3Capacity);        
  drainWater = calcDrainWater(theA4Water, drainWater, theA4Capacity);            
  theCWater += (pP->permeabilityC * drainWater);
  return (1.0-pP->permeabilityC)*drainWater;
}

/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
*/
float SOIL:: calcDrainWater (float & water, float inflow, float FK)
{		float totalWater = water + inflow;
    float outflow = 0.0;
		if (totalWater < FK)	
		  water = totalWater;
		else {									// soil is saturated
			water = FK;
			outflow = totalWater-FK; }
    return outflow;
}

/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm

_evaporation_

for theOWater: calculated from Meidan 1990, Fig. 3-4
for theA1Water: my guess. 

*/

float SOIL::evaporation (void)
{
  float OAWaterBeforeET = theOWater + theA1Water + theA2Water + theA3Water + theA4Water;
  float mass = pIndividual->getMass();

  //evaporation factors for each layer, bare ground
  // ef1 ≥ 2.0 !!! otherwise, not enough water can evaporate per day!!!
  float efO = pP->EvapoO, ef1 = pP->EvapoA1, ef2 = 1.0, ef3 = 1.0, ef4 = 1.0;
  
 // transpiration from herbaceaus vegetation
/*  if (mass > 1000.0) {ef1 += 0.5; ef2 += 0.5; ef3 += 0.5; ef4 += 0.2;}
  else if (mass > 100.0) {ef1 += 0.3; ef2 += 0.3; ef3 += 0.3;}
  else if (mass > 10.0) {ef1 += 0.1; ef2 += 0.1;}
*/  
  if (mass > 200.0) {ef1 *= 1.2; ef2 *= 1.4; ef3 *= 1.4; ef4 *= 1.2;}
  else if (mass > 100.0) {ef1 *= 1.1; ef2 *= 1.3; ef3 *= 1.3;}
  else if (mass > 10.0) {ef1 *= 1.05; ef2 *= 1.1;}
  
 // shrubs reduce evaporation
 // no water uptake by shrubs from A4, otherwise all soil layers too dry
  if (theVegetation >= shrub)
  {  efO *= 0.4; ef1 *= 0.5; ef2*=1.0; ef3*=1.05; ef4*=1.25;}
  
  efO *= theTemperature; 
	efO = efO<=0? 0.1: efO; // prevent negative values, MK 2013-12-02
  
  // evaporation from O layer
  theOWater = reducePotential(theOWater, theDepthO, efO);

  // evapotranspiration from A1 layer
  theA1Water = reducePotential(theA1Water, theDepthA1, ef1);
  balancePsi (theA1Water, theOWater, theDepthA1, theDepthO); // changed v2.6 20070126
  
  // transpiration from A2 layer
  theA2Water  = reducePotential(theA2Water, theDepthA2, ef2);
  balancePsi (theA2Water, theA1Water, theDepthA2, theDepthA1); // changed v2.6 20070126
  
  // transpiration from A3 layer
  theA3Water  = reducePotential(theA3Water, theDepthA3, ef3);
 balancePsi (theA3Water, theA2Water, theDepthA3, theDepthA2); // changed v2.6 20070126

 // transpiration from A4 layer (c. 15-50 cm)
  theA4Water  = reducePotential(theA4Water, theDepthA4, ef4);
  balancePsi (theA4Water, theA3Water, theDepthA4, theDepthA3); // changed v2.6 20070126
  
  // update the water potentials
  thePotO  = calcPotentialO();
  thePotA1  = calcPotentialA1();
  thePotA2  = calcPotentialA2();
  thePotA3  = calcPotentialA3();
  thePotA4  = calcPotentialA4();
    
  float OAWaterAfterET = theOWater + theA1Water + theA2Water + theA3Water + theA4Water;
  return OAWaterBeforeET - OAWaterAfterET;
}

/* mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm  */

float SOIL::reducePotential (float water, float depth, float factor)
{
  float psi  = calcPotential(water, depth, theVolPcFK);
  if (psi > PsiMin_MPa) {
	psi *= factor;
	if (psi < PsiMin_MPa) psi = PsiMin_MPa;
    water = calcVolumetricWater (psi, depth);
  }
  return water;
}

/* mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm  
The function is supposed to balance the difference in water potential between 
two layers by moving water. BUG: When the thinner or equally thick layer has more water than the other layer

*/

void SOIL::balancePsi (float & waterLower, float & waterUpper, 
					   float depthLower, float depthUpper)
{
  float psiUpper = calcPotential(waterUpper, depthUpper, theVolPcFK);
  float psiLower = calcPotential(waterLower, depthLower, theVolPcFK);
  float deltaWater = 0.0;
  float psiMean = 0.0;
  
  psiMean = -pow(-psiUpper,depthUpper/(depthUpper+depthLower))*pow(-psiLower,depthLower/(depthUpper+depthLower)); // weighted geom. mean

  // simplified code v2.6 20070126, no change in strategy
  // but added a decision when the layers are equally thick
  deltaWater = pP->permeabilityA * (calcVolumetricWater (psiMean, min(depthLower, depthUpper)) - 
		(depthLower<depthUpper?
			  waterLower:
		 (((depthLower==depthUpper)&&(psiLower<psiUpper))?
		   waterLower:
		   waterUpper)
		  )); // without the brackets around the ?:terms the term is ignored; this seems to violate c++ standards

    if (depthLower < depthUpper)
    { waterLower += deltaWater;
	  waterUpper -= deltaWater;
    }
	else if ((depthLower == depthUpper) && (psiLower < psiUpper))
	{ waterLower += deltaWater;
	  waterUpper -= deltaWater;
	}
    else
    { waterLower -= deltaWater;
	  waterUpper += deltaWater;
    }
	
  // end changed v2.6 20070126
}

/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm

_FKVol_

Field capacity is measured in l/dm^3 = dm^3/dm^3 = dm/dm = 100 mm/dm = % = vol%

*/

float SOIL::FKVol (void) const
{
  float theta = calcVolumetricWater(FKPsi_MPa);
  return theta;
}

/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm

_calcPotential_

van Genuchten equation (http://ahti.hut.fi/~tkarvone/sgh_7pf.htm)
  theta = thetaR  +  (thetaS-thetaR) / [1+(alpha+psi)^beta]^(1-1/beta)
  theta: volumetric soil moisture; thetaR: residual soil moisture; 
  thetaS soil moisture at saturation; psi: soil moisture potential
  
  van Genuchten, M. Th., (1980). A closed form equation for predicting 
  the hydraulic conductivity of unsaturated soils. Soil Sci. Soc. Am. J. 
  44: 892-898.
  
The water is concentrated in a layer of 1 dm. When the layer is full (>P.mmFK), it spills over into the next layer. I assume that the roots take up water from the layer where it is best available. Therefore, I calculate Psi for the layer (≤1) with the most water.

*/

float SOIL::calcPotential (float theta, float d, float FKv) const
{	
  float psi = PsiMin_MPa;

  if (d > 0.0)
  {
    double temp = 0.0;
	float thetaR = pP->thetaR;
	
    theta = theta/d/100.0; // recalculate for 1 dm and %
    if (theta < thetaR) theta = thetaR;
    if (theta>FKv) theta = FKv; // spill-over into next layer
      
    temp = (pP->thetaS - thetaR) / (theta - thetaR);
	if (temp >= 0)
    temp = pow(temp, double (1.0/( 1.0 - 1.0/pP->beta ))) - 1.0; //make sure temp is not negative
	else std::cerr << "thetaR ("<< thetaR << ") must not be greater than thetaS (" << pP->thetaS << ")!" << std::endl;
    temp = pow(temp, double (1.0/pP->beta));
    temp = temp/pP->alpha;
    psi = -temp;
        
    if (psi < PsiMin_MPa) psi = PsiMin_MPa; // avoid large negative numbers
 	}
 	return psi;
}

float SOIL::calcPotentialO (void) const {	
  return calcPotential(theOWater, theDepthO, theVolPcFK);}
float SOIL::calcPotentialA1 (void) const {	
  return calcPotential(theA1Water, theDepthA1, theVolPcFK);}
float SOIL::calcPotentialA2 (void) const {	
  return calcPotential(theA2Water, theDepthA2, theVolPcFK);}
float SOIL::calcPotentialA3 (void) const {	
  return calcPotential(theA3Water, theDepthA3, theVolPcFK);}
float SOIL::calcPotentialA4 (void) const {	
  return calcPotential(theA4Water, theDepthA4, theVolPcFK);}

/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm

_getVolumetricWater_

inverse of getPotential()

*/

float SOIL::calcVolumetricWater (float psi, float d) const
{
  if (psi < PsiMin_MPa) psi = PsiMin_MPa;
  float theta = pP->thetaR;
  double saturation = 0.0;

  saturation = 1.0 + pow(double(pP->alpha * -psi), double(pP->beta));
  saturation = pow( saturation, double(1.0 -1.0 /pP->beta));
  theta = pP->thetaR + (pP->thetaS - pP->thetaR) / saturation;
  theta *= d; // adjust to layer thickness
  
  return theta*100.0;
}
/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm

_setSCharacteristics

called from GRID

*/

void SOIL::setSCharacteristics (float topoV, float stones)
{
  theTopoHeterogeneity = topoV;
  theStoniness = stones;
  theVegetation = bare;
  theRunoff = 0.0;
  theShrubR = 0.0;
  theNewResourceSum = 0.0;
}

/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm

access functions to soil state variables

*/
void SOIL::setResourceShare (float weight) {
  theNewResourceSum += weight;
}

float SOIL::getRelLight (void) const {
  if (theVegetation >= shrub)
  return theRelLight;
else
  return 1.0;}

float SOIL::getRunoff(void) const {
  return theRunoff;}

float SOIL::getWaterO  (void) const {
  return theOWater; }
float SOIL::getWaterA1 (void) const {
  return theA1Water; }
float SOIL::getWaterA2 (void) const {
  return theA2Water; }
float SOIL::getWaterA3 (void) const {
  return theA3Water; }
float SOIL::getWaterA4 (void) const {
  return theA4Water; }
float SOIL::getWaterC  (void) const {
  return theCWater; }

float SOIL::getVolWaterO  (void) const {
  return theOWater/theDepthO; }
float SOIL::getVolWaterA1 (void) const {
  return theA1Water/theDepthA1; }
float SOIL::getVolWaterA2 (void) const {
  return theA2Water/theDepthA2; }
float SOIL::getVolWaterA3 (void) const {
  return theA3Water/theDepthA3; }
float SOIL::getVolWaterA4 (void) const {
  return theA4Water/theDepthA4; }

float SOIL::getPotentialO (void) const {	
  return thePotO;}
float SOIL::getPotentialA1 (void) const {	
  return thePotA1;}
float SOIL::getPotentialA2 (void) const {	
  return thePotA2;}
float SOIL::getPotentialA3 (void) const {	
  return thePotA3;}
float SOIL::getPotentialA4 (void) const {	
  return thePotA4;}

float SOIL::getOAWaterET (void) const {
  return theOAWaterET;}

PLANT SOIL::getPlant(void) const {
	return *pIndividual;}
PLANT* SOIL::getPPlant(void){
  return pIndividual;}
SEEDS SOIL::getSeedbank(void) const{
  return *pSeedbank;}
SEEDS* SOIL::getPSeedbank(void){
  return pSeedbank;}

float SOIL::getResourceShare (float mass) const {
 if (pIndividual->isEstablished() || theOldResourceSum == 0.0)
//	if (pIndividual->getMass() > mass || theOldResourceSum == 0.0)
	return 0.0;
  else
	return mass/theOldResourceSum;}

NSupplyQ SOIL::getNSupply (void) const{
  return pP->NSupply;}

cover SOIL::getVegetation(void) const{
	return theVegetation;}

int SOIL::getShrubID(void) const{
	return theShrubID;}
