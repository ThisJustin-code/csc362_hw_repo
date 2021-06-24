/* Justin Gallagher
   CSC 362 - 001
   Programming Assignment #2
   Monday, September 30th 2019 */

/* This program predicts the outcome of football games. It inputs from a file the ratings of various teams
   that have played each other. It then calls a function that compute prediction values given the data.
   An update function totals the number of predictions made and how many games were won by the home team.
   Output is then written to an text file that contains the predicted result of the games and the overall
   summary that includes how many games were predicted and the percentage won by the home teams. */ 

#include "header.h"																// include the header file

main() {

	FILE* fp1, * fp2;															// input and output files
	fp1 = fopen("football2.txt", "r");											// open input file for football data
	fp2 = fopen("output2.txt", "w");											// open output file for predicitons

	char HT[20], VT[20];														// home-team and visiting-team names
	int difference, totalGames = 0, homeWins = 0;							    // difference based on predictions,
																				//   total games predicted, total home-team wins
	int HTO, HTD, HTS, HTH, HTC;												// home-team offensive strength, defensive strength, special
																				//   teams strength, strength at home, home field advantage
	int VTO, VTD, VTS, VTR;														// visiting-team offensive strength, defensive strength, 
																				//   special teams strength, road strength
	double predictor1, predictor2, predictor3, predictor4, predictor5;			// 5 prediction values for computing difference


	while (!feof(fp1)) {													// set c to the character returned by getc of fp1; 
																				//   while c is not the end of file
		grabInput(fp1, HT, &HTO, &HTD, &HTS, &HTH, &HTC,						// grab names of teams and ratings data from fp1
			VT, &VTO, &VTD, &VTS, &VTR);
		compute(HTO, HTD, HTS, HTH, HTC, VTO, VTD, VTS, VTR,					// compute predictor values based off ratings data
			&predictor1, &predictor2, &predictor3, &predictor4, &predictor5);
		score(predictor1, predictor2, predictor3,								// calculate difference in score based off predictors
			predictor4, predictor5, &difference);
		output(fp2, HT, VT, difference);										// output to fp2 the results
		update(&totalGames, &homeWins, difference);								// update the number of predictions of home wins
	}

	summary(fp2, totalGames, homeWins);											// output to fp2 the final summary, # of predictions
																				//   and % of home wins
	fclose(fp1);																// close input file
	fclose(fp2);																// close output file
}