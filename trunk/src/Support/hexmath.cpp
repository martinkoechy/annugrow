/*
 *  hexmath.cpp
 *  annuals 2.4.9
 *
 *  Created by Forschung on Thu Feb 10 2005.
 *  Copyright (c) 2005 Martin Koechy. All rights reserved.
 *
 */

#include <iostream>
#include <math.h>
#include "hexmath.h"

unsigned long NCellsOnPerimeter (unsigned long distance)
{
  if (distance == 0)
	return 1;
  else
	return 6 * distance;
}

unsigned long NCellsWithinCircle (unsigned long distance)
{
  return 3*(distance+distance*distance)+1;
}

int NLayersInArea (double cells_in_circle_area)
{
  if (cells_in_circle_area == 0.0)
	return 0;
  else
	return int (sqrt((cells_in_circle_area-1.0)/3.0+0.25)-0.5);
}

int NLayersInAreaRounded (double cells_in_circle_area)
{
  if (cells_in_circle_area == 0.0)
	return 0;
  else
	return int (sqrt((cells_in_circle_area-1.0)/3.0+1.0)-0.5);
}
