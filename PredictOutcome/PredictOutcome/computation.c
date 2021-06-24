/* Justin Gallagher
   CSC 362 - 001
   Programming Assignment #2
   Monday, September 30th 2019 */

   /* This computation file includes the following: (1) a compute funtion that calculates 5 predictor values, 
      (2) a score function that calculates the difference in score between two teams based off predictors,
	  and (3) an update function which keeps the number of predictions and number of home-team wins updated. This file
	  is to be used with predict.c to predict football outcomes.*/

#include "header.h"																			// include the header file

// this function takes rating values and returns predictor values 
void compute(int HTO, int HTD, int HTS, int HTH, int HTC, int VTO, int VTD, int VTS, int VTR, 
	double* predictor1,	double* predictor2, double* predictor3, double* predictor4, double* predictor5) {		
	*predictor1 = HTO * OFFENSIVE_FACTOR - VTD;												// calculate predictor 1
	*predictor2 = HTD + 2 - VTO * OFFENSIVE_FACTOR;											// calculate predictor 2
	*predictor3 = HTS * SPECIAL_TEAMS_FACTOR - VTS;											// calculate predictor 3
	*predictor4 = HTH + HTC * HOME_FIELD_ADVANTAGE - VTS;									// calculate predictor 4
	*predictor5 = HTO * HTD * HTH * OVERALL_FACTOR - VTO * VTD * VTR;						// calculate predictor 5
}

// this function takes predictor values and returns the difference in score
void score(double predictor1, double predictor2, double predictor3, 
	double predictor4, double predictor5, int* difference) {
	*difference = (int)(predictor1 * OFFENSIVE_WORTH + predictor2 * DEFENSIVE_WORTH +		// calculate difference
		predictor3 * SPECIAL_WORTH + predictor4 * HOME_WORTH + predictor5 * OVERALL_WORTH);	
}

// this function keeps track the total number of games or predictions, and the number of times the home team won
void update(int* totalGames, int* homeWins, int difference) {
	*totalGames = *totalGames + 1;															// increment total games
	if (difference >= 0) {																	// if difference is 0 or positive
		*homeWins = *homeWins + 1;															// increment home wins
	}
}