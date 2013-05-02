/*
 *  MK_round.cpp
 *  intraspecific
 *
 *  Created by Martin Kšchy on Thu Feb 06 2003.
 *  Copyright (c) 2003 __MyCompanyName__. All rights reserved.
 *
 */
#include "MK_round.h"
#include <cstdlib>

//------------------------------------------------------------------

double MK_round (double fnumber, int d)
{	
	short sign = 1;
	long p=1;	
	short units = 0;
	long truncN = 0;
	double round_n= 0;

	if(d<0) d= -d; 				// error checking

    if (fnumber < 0) {			// remember sign of number
        sign = -1;
        fnumber = -fnumber;}

	for (int i=0; i<d+1 ;i++, p*=10);	// p=10^d, no need for <math.h>
	
                                                // Beispiel
                                                // 0.867, d=2
	fnumber = fnumber * p;						// 86.7
	
	truncN = long (fnumber);					// 86
	units = truncN%10; 							// 6
	
	if (units < 5)
        round_n = truncN / (p*1.0);
    else
        round_n = (truncN-units+10) / (p*1.0); // 86-6+10 => 90 => 0.9
		
	return round_n * sign;		// restore sign
}

long MK_round (double number)
{
  if (number >=0)
    number += 0.5;
  else
    number -= 0.5;
  return long (number);
}

long MK_rRound (double number)
{
  long integerpart = long(number);
  float decimalpart = number-integerpart;
   if (dr250() < decimalpart)
	return ++integerpart;
	else
	  return integerpart;
}
//***************************************
float MK_max (float* A, int length)
{
  int position = 0;
  
  for(int i = 0; i < length; i++)
  {
    if ( *(A+position) < *(A+i) )
      position = i;
  }
  
  return A[position];
}

double MK_max (double* A, int length)
{
  int position = 0;
  
  for(int i = 0; i < length; i++)
  {
    if ( *(A+position) < *(A+i) )
      position = i;
  }
  
  return A[position];
}

long int MK_max(long* A, int length)
{
  int position = 0;
  
  for(int i = 0; i < length; i++)
  {
    if ( *(A+position) < *(A + i) )
      position = i;
  }
  
  return A[position];
}

float MK_min (float* A, int length)
{
  int position = 0;
  
  for(int i = 0; i < length; i++)
  {
    if ( *(A+position) > *(A + i) )
      position = i;
  }
  
  return A[position];
}

double MK_min (double* A, int length)
{
  int position = 0;
  
  for(int i = 0; i < length; i++)
  {
    if ( *(A+position) > *(A + i) )
      position = i;
  }
  
  return A[position];
}

long int MK_min(long* A, int length)
{
  int position = 0;
  
  for(int i = 0; i < length; i++)
  {
    if ( *(A+position) > *(A + i) )
      position = i;
  }
  
  return A[position];
}

long factorial (int n)
{
  if (n < 0) exit(876);
  if (!n) return 1;
  else {
	long p = 1;
	for (int i = n; i > 0; i--)
	  p *= i;
	return p;
  }
}

long permutation (int n, int a=0)
{
  if (a<0 || n < 0) exit(876);
  if (!n) return 1;
  else {
	long p = 1;
	for (int i = n; i > a; i--)
	  p *= i;
	p/=factorial(n-a);
	return p;
  }
}


//------------------------------------------------------------------
//#pragma package(smart_init)	// only for Borland C++ Builder
