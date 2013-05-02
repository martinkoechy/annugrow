/*
 *  r250m.h
 *  intraspecific
 *
 *  Created by Martin Kšchy on Thu Feb 06 2003.
 *  Copyright (c) 2003 __MyCompanyName__. All rights reserved.
 *
 */

//------------------------------------------------------------------
#ifndef r250mH
#define r250mH
//------------------------------------------------------------------


/*** Function prototypes for R250 random number generator, by W. L. Maier  ***/

/**** Function: r250 Description: returns a random unsigned integer k
                uniformly distributed in the interval 0 <= k < 65536.  ****/

unsigned int r250();


/**** Function: r250n Description: returns a random unsigned integer k
                uniformly distributed in the interval 0 <= k < n ****/

unsigned int r250n(unsigned n);


/**** Function: dr250 Description: returns a random float z 
		in range 0 <= z < 1.  ****/

float dr250(void); /*schafft 100000 Zahlen
                  pro sek auf intel486DX25 mit borlandc, huge */


/**** Function: r250_init Description: initializes r250 random 
		number generator.    ****/

void r250_init(int seed);

float vr250(void); // returns a random float z -1 <= z < +1
#endif

