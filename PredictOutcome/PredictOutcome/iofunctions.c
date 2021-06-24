/* Justin Gallagher
   CSC 362 - 001
   Programming Assignment #2
   Monday, September 30th 2019 */

   /* This iofunctions file includes the following: (1) a grabInput funtion that inputs one line of ratings data,
	  (2) an output function that prints to an output file the team that won and the difference in score,
	  and (3) a summary function which prints to the output file how many games were predicted and the precentage
	  of games won by the home team. This file is to be used with predict.c to predict football outcomes.*/

#include "header.h"																			// include the header file

// this funtion takes from the input file one line of ratings data
void grabInput(FILE* fp1, char* HT, int* HTO, int* HTD, int* HTS, int* HDH, int* HDC, 
	char* VT, int* VTO, int* VTD, int* VTS, int* VDR) {
	fscanf(fp1, "%s %d %d %d %d %d %s %d %d %d %d",											// scan fp1 for the team names
		HT, HTO, HTD, HTS, HDH, HDC, VT, VTO, VTD, VTS, VDR);								// and the ratings data
}

// this function prints to an output file the team that won and the difference in score
void output(FILE* fp2, char* HT, char* VT, int difference) {
	if (difference == 0) {																	// if difference is 0
		fprintf(fp2, "%s beat %s by 1\n", HT, VT);											// home team wins by 1 pt
	}
	else if (difference < 0) {																// if difference is negative
		fprintf(fp2, "%s beat %s by %d\n", VT, HT, abs(difference));						// visiting team wins by abs value 
	}																						//   of difference
	else {																					// if difference is positive
		fprintf(fp2, "%s beat %s by %d\n", HT, VT, difference);								// home team wins by difference
	}
}

// this function prints to the output file how many games were predicted and the precentage
// of games won by the home-team
void summary(FILE* fp2, int totalGames, int homeWins) {
	double percentWon = ((double)homeWins / totalGames) * 100;								// calculate home team precent won
	fprintf(fp2, "\nOf %d games, %.2f%% were won by the home team",							// print to fp2, the total games
		totalGames, percentWon);															//   and percent won by home
}