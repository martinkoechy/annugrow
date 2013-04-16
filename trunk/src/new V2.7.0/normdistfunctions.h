/*
 *  normdistfunctions.h
 *  annuals 2.4.9
 *
 *  Created by Forschung on Fri Feb 11 2005.
 *  Copyright (c) 2005 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef _NORMAL_DIST_FUNCT_H_
#define _NORMAL_DIST_FUNCT_H_


double random_normal();
double stdnormal_pdf(double u);
double stdnormal_cdf(double u);
double stdnormalcum_inv(double p);
double quad8_stdnormal_pdf(double a, double b, double Q);

#endif
