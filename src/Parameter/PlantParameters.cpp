/*
 *  PlantParameters.cpp
 *  intraspecific
 *
 *  Created by Martin Kšchy on Fri May 02 2003.
 *  Copyright (c) 2003 __MyCompanyName__. All rights reserved.
 *
 */

#include <iostream>
#include <fstream>
#include <string>
#include "PlantParameters.h"

void PLANT_PARAMETERS::setForAllSpecies(void)
{
  Home = 0.2; // EY: 0.25, MA: 0.5
  MassAccessA2 =  3.5; // 3.5 mg
  MassAccessA3 =  4.5; // 4.5 mg
  MassAccessA4 =  6.5; // 6.5 mg
  MassCompetition1 = 30.0; // 30.0 mg, changed v 2.60
  MassCompetition2 = 55.0; // 30.0 mg, changed v 2.60
  MassSeed = 3.0; // 3.0 mg, estimate
  MassFruit = 1.27*MassSeed; // mg, estimate
  MassEstablish = 5.0; // 5 mg
  MassFlowering = 35.0; // 35 mg, changed v 2.60
  MassMax = 3500.0; // mg; estimate, changed v 2.60, changed from 500 to 3500, MK 2013-12-02
  RGR_Max = 0.17; // Dyer et al. 2001
  AllocationRepro = 0.60; // calculated from Aronson 1990;
  N_tolerance = high;
  DDMortality = 0.4; // calculated from Hadas counts 2002/2003
  RGR_shade=1.0; // RGR reduction in shade
}

PLANT_PARAMETERS::~PLANT_PARAMETERS()
{
}

void PLANT_PARAMETERS::documentation (char* filename) const
{
	std::ofstream ParameterDocu;
	ParameterDocu.open (filename, std::ios::app);

  ParameterDocu << "------ Plant Parameters ------" << std::endl;
  ParameterDocu << "Species: \t" << N << std::endl;
  ParameterDocu << "MassSeed (mg): \t" << MassSeed << std::endl;
  ParameterDocu << "MassFruit (mg): \t" << MassFruit << std::endl;
  ParameterDocu << "Mass for flowering (mg/ind.): \t" << MassFlowering << std::endl;
  ParameterDocu << "Mass for 'established' (mg/ind.): \t" << MassEstablish << std::endl;
	ParameterDocu << "Mass for access to A2 (mg/ind.): \t" << MassAccessA2 << std::endl;
  ParameterDocu << "Mass for access to A3 (mg/ind.): \t" << MassAccessA3 << std::endl;
  ParameterDocu << "Mass for access to A4 (mg/ind.): \t" << MassAccessA4 << std::endl;
  ParameterDocu << "Mass for competition with first neighbours (mg/ind.): \t" << MassCompetition1 << std::endl;
  ParameterDocu << "Mass for  competition with second neighbours (mg/ind.): \t" << MassCompetition2 << std::endl;
  ParameterDocu << "MassMax (mg/ind.): \t" << MassMax <<  std::endl;
  ParameterDocu << "Allocation to repr. tissues [0,1]: \t" << AllocationRepro << std::endl;
  ParameterDocu << "RGR Max: \t" << RGR_Max << std::endl;
  ParameterDocu << "RGR_shade (% of RGRMax): \t" << RGR_shade << std::endl;
  ParameterDocu << "PWP (MPa): \t" << PWP << std::endl;
  ParameterDocu << "Resource portion from home [0,1]: \t" << Home << std::endl;
  ParameterDocu << "Density-dependent mortality [0,1]: \t" << DDMortality << std::endl;
 
	
	ParameterDocu.close();
}

PLANT_PARAMETERS::PLANT_PARAMETERS (void)
{
  strcpy(N, "generic annual");
  
  setForAllSpecies();
  PWP = -3.0; // MPa, estimate
  MassFlowering = 35.0;
  name = annual;
}

cPPTypMes::cPPTypMes (void)
{
  strcpy(N,"typical mesic Mediterranean");
		
  setForAllSpecies();
  MassFlowering = 40.0; // 35 for 'EnYa'aqov 2002
  PWP = -1.5; // 
  name = typMes;
}

cPPTypMed::cPPTypMed (void)
{
  strcpy(N,"typical Mediterranean");
		
  setForAllSpecies();
  MassFlowering = 40.0; // 40 for Matta 2002
  PWP = -1.75; // estimate < Majerus 1975, Hadas' counts
  name = typMed;
}

cPPTypSem::cPPTypSem (void)
{
  strcpy(N,"typical semi-arid");
		
  setForAllSpecies();
  MassFlowering = 35.0; // 35 for Lahav 2002
  PWP = -5.5; // -5, estimate < Majerus 1975, Hadas' counts
  name=typSem;
}

cPPTypAri::cPPTypAri (void)
{
  strcpy(N,"typical arid");
		
  setForAllSpecies();
  MassFlowering = 20.0; // 20 for Sede Boqer
  PWP = -6.5; // -5.5, estimate < Majerus 1975, Hadas' counts
  name=typAri;
}

cPPAveSteri::cPPAveSteri (void)
{
  strcpy(N,"Avena sterilis");
  setForAllSpecies();

  MassSeed = 4.73; // Kigel et al. Report 2002
  MassFruit = 4.8; // 
  MassFlowering = 30.0; //
  MassMax = 3500.0; // Torner et al. 2000
  RGR_Max = 0.18; // high mean of all Poaceae in Dyer et al. 2001
  PWP = -2.85; // -2.85, estimate < Majerus 1975, Hadas' counts
  AllocationRepro = 0.4; // Gonzalez Ponce & Santin 2001, wet year
//  RGR_shade = 0.75; // RGR reduction in shade
  N_tolerance = high;
  name=AveSteri;
}

cPPBiscDid::cPPBiscDid (void)
{
  strcpy(N,"Biscutella didyma");
  setForAllSpecies();
		
  MassSeed = 0.74; // Cristina/Marcelo
  MassFruit = 1.7; // 1.7 fits allocation, 2.5 © Cristina/Marcelo
  MassFlowering = 25.0; // estimate
  MassMax = 600.0; // Irit/Kigel
  RGR_Max = 0.182; // high mean of all Brassicaceae in Dyer et al. 2001
  PWP = -3.5; // estimate < Majerus 1975, Hadas' counts
  AllocationRepro = 0.75 ; // GrŸnzweig & Kšrner 2001;, Aronson et al. 1993
//  RGR_shade = 0.75; // RGR reduction in shade
  N_tolerance = high;
  name=BiscDid;
}

cPPBraDist::cPPBraDist (void)
{
  strcpy(N,"Brachypodium distachyum");
		
  setForAllSpecies();
  MassSeed = 4.15; // mean (Kew, Dyer, GrŸnzweig & Kšrner, Kigel)
  MassFruit = 4.4; // difference from Kigel et al. 2002
  MassFlowering = 25.0; // 
  MassMax = 600.0; // 
  RGR_Max = 0.154; // Dyer et al. 2001
  PWP = -3.5; // estimate < Majerus 1975, Hadas' counts
  AllocationRepro = 0.74 ; // GrŸnzweig & Kšrner 2001
//  RGR_shade = 0.75; // RGR reduction in shade
  N_tolerance = high;
  name=BraDist;
}

cPPBromFasc::cPPBromFasc (void)
{
  strcpy(N,"Bromus fasciculatus");
		
  setForAllSpecies();
  MassSeed = 1.05; // mean (Kigel, Dyer)
  MassFruit = 1.25; // 1.25 mean(Kigel, Cristina, 3x Aronson)
  MassFlowering = 20.0; // 8.0, estimate < Martina & Irit
  MassMax = 120; // fitted to Martinas counts
  RGR_Max = 0.185; // Dyer et al. 2001
  PWP = -3.5; // -3.5, estimate < Majerus 1975, Hadas' counts
  AllocationRepro = 0.605; // 0.605 = mean(Aronson 1990, GrŸnzweig & Kšrner 2001);
//  RGR_shade = 0.75; // RGR reduction in shade
  N_tolerance = high;
  name=BromFasc;
}

cPPCarrAnn::cPPCarrAnn (void)
{
  strcpy(N,"Carrichtera  annua");
		
  setForAllSpecies();
  MassSeed = 0.87; // 0.87 = mean(Kew, Kigel, Cristina, Loria&Noy-Meir)
  MassFruit = 1.55; // 1.55 = mean (Kigel et al. 2002, Cristina/Martina)
  MassFlowering = 52; // 52, estimate < Martina & Irit
  MassMax = 1500; // 1000 Irit; 88 GrŸnzweig & Kšrner 2001
  RGR_Max = 0.166; // high mean of all Brassicaceae in Dyer et al. 2001
  PWP = -5.0; // -5, estimate < Majerus 1975, Hadas' counts
  AllocationRepro = 0.5; // 0.5 GrŸnzweig & Kšrner 2001;
//  RGR_shade = 0.75; // RGR reduction in shade
  N_tolerance = high;
  name=CarrAnn;
}

cPPCriDeli::cPPCriDeli (void)
{
  strcpy(N,"Crithopsis delileana");
		
  setForAllSpecies();
  MassSeed = 2.85; // 2.85 = mean(Kigel et al. 2002, GrŸnzweig & Kšrner)
  MassFruit = 5.85; // 0.511.7 = mean (Kigel et al. 2002)
  MassFlowering = 25; //
  MassMax = 600; // 
  RGR_Max = 0.166; // high mean of all Poaceae in Dyer et al. 2001
  PWP = -5.0; // -5, estimate < Majerus 1975, Hadas' counts
  AllocationRepro = 0.6; // 0.6 GrŸnzweig & Kšrner 2001;
//  RGR_shade = 0.75; // RGR reduction in shade
  N_tolerance = high;
  name=CriDeli;
}

cPPFilDes::cPPFilDes (void)
{
  strcpy(N,"Filago desertorum");
 
  setForAllSpecies();
MassSeed = 0.04;
  MassMax = 25;
	RGR_Max = 0.166; // Dyer et al. 2001
  PWP = -5.0; // -5, estimate < Majerus 1975, Hadas' counts
	MassFlowering = 2.0;
	MassFruit = 0.07;
	AllocationRepro = 0.55; // < Loria & Noy-Meir
//  RGR_shade = 0.75; // RGR reduction in shade
  N_tolerance = high;
  name=FilDes;
}
			
cPPHippUni::cPPHippUni (void)
{
  strcpy(N,"Hippocrepis unisiliquosa");
  
  setForAllSpecies();
MassSeed = 2.9; // 2.9 = mean(Kigel, Kew, Cristina, GrŸnzweig&Kšrner)
  MassMax = 1000; // 1000 fitted to Martina's counts; 250 Irit
	RGR_Max = 0.09; // 0.09 H. multisiliquosa in Dyer et al. 2001
  PWP = -4.5; // -4.5, estimate < Majerus 1975, Hadas' counts
	MassFlowering = 80.0; // 10 estimate < Martina & Irit
	MassFruit = 2.9; // 2.8 mg fruit mass/seed mean(Kigel et al. 2002,G&K/8[Martina])
	AllocationRepro = 0.864; // GrŸnzweig & Kšrner 2001
//  RGR_shade = 0.75; // RGR reduction in shade
  N_tolerance = zero;  // legume
  name=HippUni;
}
			
cPPHymCir::cPPHymCir (void)
{
  strcpy(N,"Hymenocarpos circinnatus");
  setForAllSpecies();
  MassSeed = 4.94; // 4.94 = mean(Kigel, G&K)
  MassMax = 3000.0; // 3000 fitted to Martina's counts; 370 Irit
	RGR_Max = 0.11; // Dyer et al. 2001
  PWP = -3.0; // -3, estimate < Majerus 1975, Hadas' counts
	MassFlowering = 20.0;
	MassFruit = 21.3; // 21.3 = mean(Kigel, Cristina, GrŸnzweig & Kšrner)/ 2seeds/fruit
	AllocationRepro = 0.732; // GrŸnzweig & Kšrner 2001
//  RGR_shade = 0.75; // RGR reduction in shade
  N_tolerance = zero; // legume
  name=HymCir;
}
			
cPPRebPin::cPPRebPin (void)
{
  strcpy(N,"Reboudia pinnata");
		
  setForAllSpecies();
	MassSeed = 0.23; // 0.23 = mean(Kew, Dyer et al. 2001, Kigel)
	MassMax = 4500; // 711 < Loria & Noy-Meir, 4500 < Martina
	RGR_Max = 0.166; // Dyer et al. 2001
  PWP = -7.0; // -7, estimate < Majerus 1975, Hadas' counts
  MassEstablish = 1.0; // estimate
	MassFlowering = 4.0; // 4 < Loria&Noy-Meir, Cristina
  MassFruit =  1.55; // < Cristina, Martina
	AllocationRepro = 0.43; // 0.43 < Loria & Noy-Meir; 
  RGR_shade = 0.75; // RGR reduction in shade
  N_tolerance = high;
  name=RebPin;
}

cPPSchisArab::cPPSchisArab (void)
{
  strcpy(N,"Schismus arabicus");
		
  setForAllSpecies();
  MassSeed = 0.07; // © Kew, Loria & Noy-Meir
	MassMax = 100; 
	RGR_Max = 0.166;	// 0.166, grasses < Dyer et al.
  PWP = -7.0; // -7, estimate < Majerus 1975, Hadas' counts
	MassFlowering = 4.5; // estimate
	MassFruit = 0.12; // < Loria & Noy-Meir
	AllocationRepro = 0.39; // 0.39 < Loria & Noy-Meir, Kew
  RGR_shade = 0.75; // RGR reduction in shade
  N_tolerance = high;
  name=SchisArab;
}
			
cPPStipCap::cPPStipCap (void)
{
  strcpy(N,"Stipa capensis");
		
  setForAllSpecies();
 MassSeed = 1.4; // 1.4 = mean(Kigel et al. 2002, GrŸnzweig & Kšrner 2001)
  MassFruit = 6.0; // 6 = mean(Cristina, GrŸnzweig & Kšrner 2001, Kigel et al. 2002)
  MassFlowering = 14.4; // estimate < Martina & Irit
  MassMax = 3000.0; // 3000 < Martina, 350 © Irit/Kigel, 60 GrŸnzweig & Kšrner 2001, 450 Claus
  RGR_Max = 0.18; // 0.18 < average of N-rich Poaceae in Dyer et al.
  PWP = -5.5; // -5.5, estimate < Majerus 1975, Hadas' counts
  AllocationRepro = 0.365; // 0.365 = mean (2xAronson 1990, GrŸnzweig & Kšrner)
//  RGR_shade = 0.75; // RGR reduction in shade
  N_tolerance = high;
  name=StipCap;
}

cPPValHis::cPPValHis (void)
{
  strcpy(N,"Valantia hispida");
		
  setForAllSpecies();
  MassSeed = 0.23; // 0.23 = Cristina
  MassFruit = 0.57; // 0.57 = Cristina
  MassFlowering = 16.0; // estimate < Irit
  MassMax = 200.0; // 200 = 2*99 © Irit/Kigel
  RGR_Max = 0.2; // coastal forbs in Dyer et al. 2001
  PWP = -3.0; // -3, estimate < Majerus 1975, Hadas' counts
  AllocationRepro = 0.55; // < Loria & Noy-Meir
//  RGR_shade = 0.75; // RGR reduction in shade
  N_tolerance = high;
  name=ValHis;
}

cPPPlantBatch::cPPPlantBatch (void)
{ 
  strcpy(N,"Batch input");
  setForAllSpecies();
  name=batchSpecies;
}
