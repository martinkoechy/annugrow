/*
 *  MK_round.h
 *  intraspecific
 *
 *  Created by Martin Kšchy on Thu Feb 06 2003.
 *  Copyright (c) 2003 __MyCompanyName__. All rights reserved.
 *
 */

#include "r250m.h"

//------------------------------------------------------------------
#ifndef MK_roundH
#define MK_roundH
//------------------------------------------------------------------

// These functions return the nearest smaller or larger real number.
double MK_round (double number, int digits);
long	 MK_round (double number);
//returns the nearest integer with a probability equal to the decimal part
long MK_rRound (double number);

// These functions return the largest or smallest number in an array.
float MK_max (float* doublearray, int length);
double MK_max (double* doublearray, int length);
long int MK_max(long* longarray, int length);
float MK_min (float* doublearray, int length);
double MK_min (double* doublearray, int length);
long int MK_min(long* longarray, int length);
long factorial (int n);
long permutation (int n, int a);

#endif

