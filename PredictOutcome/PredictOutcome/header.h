/* Justin Gallagher
   CSC 362 - 001
   Programming Assignment #2
   Monday, September 30th 2019 */

/* This header file includes the following: (1) include statements, (2) prototypes, and (3) constant declarations
   that are used for predicting outcomes of football games. */

#pragma once														

// Include statements:
#include <stdio.h>													// for file functions		
#include <math.h>													// for math functions

// Prototypes:
void grabInput(FILE*, char*, int*, int*, int*, int*, int*,			// get from first line of input file the home and
	char*, int*, int*, int*, int*);									//   visiting team names and the 9 rating values
void compute(int, int, int, int, int, int, int, int, int,			// compute the 5 predictor values based off
	double*, double*, double*, double*, double*);					//   the rating values
void score(double, double, double, double, double, int*);			// caluculate score difference based off predictors
void output(FILE*, char*, char*, int);								// output which team beat who based off difference 
void update(int*, int*, int);										// update # of predictions and # of home wins 
void summary(FILE*, int, int);										// write summary statement with # of predictions and
																	//   percentage of home wins
#define _CRT_SECURE_NO_WARNINGS										// suppress warnings and errors

// Constants:
#define OFFENSIVE_FACTOR 1.15										// define offensive factor
#define SPECIAL_TEAMS_FACTOR 1.22									// define special teams factor
#define HOME_FIELD_ADVANTAGE 1.2									// define home field advantage
#define OVERALL_FACTOR 1.15											// define overall factor
#define OFFENSIVE_WORTH 0.30										// define offensive worth
#define DEFENSIVE_WORTH 0.24										// define defensive worth
#define SPECIAL_WORTH 0.17											// define special worth
#define HOME_WORTH 0.11												// define home worth
#define OVERALL_WORTH 0.13											// define overall worth



