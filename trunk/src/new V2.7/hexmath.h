/*
 *  hexmath.h
 *  annuals 2.4.9
 *
 *  Created by Forschung on Thu Feb 10 2005.
 *  Copyright (c) 2005 Martin Koechy. All rights reserved.
 *
 */

#ifndef HexMathH
#define HexMathH

/* ====================================================================
Operations for a hexagonal lattice

  +++			Definitions:
 +##+			0: centre = layer 0
+#0#+			#: layer at distance 1
+##+			+: layer at distance 2
+++             etc.
                perimeter: outermost layer

  ===================================================================== */

// calculate the number of cells in layer at a given distance
unsigned long NCellsOnPerimeter (unsigned long distance);

// calculate the number of cells in all layers up to and including perimeter
unsigned long NCellsWithinCircle (unsigned long distance);

// calculate the number of layers given the area in number of cells
int NLayersInArea (double cells_in_circle_area);

// calculate the number of layers given the area in number of cells
// but consider it a full layer if half of the layer is filled
int NLayersInAreaRounded (double cells_in_circle_area);

#endif
