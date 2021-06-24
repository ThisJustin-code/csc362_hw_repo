/* Justin Gallagher
   CSC 362 - 002
   Programming Assignment #3
   Monday, March 23rd 2020 */

   /* This program generates a race between a tortoise and a hare.  The program creates
	  the two animals and puts them on a path.  The path contains characters that represent different events
	  in the game.  When a specific sqot is landed on, the program will calculate the moves that are
	  needed and apply the move to that animal.  The user is kept updated by console output that follows and
	  explains each move.  At the end of the program, the winner is determined. */

//DEFINE CONSTANTS
#define MAX 60																// Define MAX as constant size of path
//INCLUDE STATEMENTS
#include <stdio.h>																
#include <time.h>
#include <stdlib.h>
//PROTOTYPES
char* moveTortoise(char*, char*, int*);										// moveTortoise function takes the tortoise and hare pointers and the collision flag and moves the tortiose along the path
char* moveHare(char*, char*, int*, int*);									// moveHare function takes the tortoise and hare pointers, and the collision and nap flags and moves the hare along the path
void print(char path[MAX], char*, char*, int, int, int);					// print function takes the animal pointers, the path array, the collision and nap flags, and a number representing the turn and outputs to the console the current status of the game

main() {
	char* hare, * tortoise;																// create char pointers for the hare and the tortoise
	int turn = 1, collision, nap;														// turn used for keeping track of which turn is it, collision flag used to represent two animals landing on the same square, nap flag used for hare napping
	char path[MAX] = " R  R  R  SSSSS   R  R CCCC  R   R   CCCCCCCCCC  R  SSSS  R ";	// game board (path)
	srand((unsigned int)time(NULL));													// seed the random num gen
	hare = tortoise = path;																// hare and tortoise point to the 0th square
	while ((hare >= path && hare < path + MAX)
		&& (tortoise >= path && tortoise < path + MAX)) {								// while hare and tortoise are in the bounds of the path
		tortoise = moveTortoise(tortoise, hare, &collision);							// call the function moveTortoise to determine where to move the tortoise
		hare = moveHare(hare, tortoise, &collision, &nap);								// call the function moveHare to determine where to move the hare
		print(path, tortoise, hare, turn, collision, nap);								// call the print function to display the current status of the game
		turn = turn + 1;																// increment the turn count
	}
	if (hare > tortoise) {																// determine if the hare won
		printf("Hare Wins!!!");															// output to console the result
	}
	else if (tortoise > hare) {															// determine if the tortoise won
		printf("Tortoise Wins!!!");														// output to console the result
	}
}

/*  moveTortoise function moves the tortoise. It takes the tortoise and hare pointers,
    along with a collision flag. It can moves 1-3 spaces and if the tortoise collides with the hare
	then a collision is detected, and the tortoise moves back one space. The tortoises move is complete.  */

char* moveTortoise(char* tortoise, char* hare, int* collision) {
	int move = rand() % 3 + 1;										// determine a random number 1-3 to be the move
	tortoise = tortoise + move;										// move the tortoise this amount of spaces on the path																										
	if (tortoise == hare && (tortoise != 0 || hare != 0)) {			// if the tortoise and hare point to the same spot,						
		tortoise = tortoise - 1;									// move the tortoise back one space						
		*collision = 1;												// set the collision flag to true
	}
	else {
		*collision = 0;												// else, set collision flag to false
	}
	return tortoise;												// return the updated pointer					
}

/*  moveHare function moves the hare. 
    It determines if the hare is napping (a 1 in 3 chance)
    and if so, sets the nap flag. Otherwise, if the hare is currently on ‘C’, then hare takes this turn to eat
    the carrot. The carrot is then removed from the path. Otherwise, the hare moves a
    random amount from 1-8. If this lands the hare on the tortoise,the hare moves back back 1 position. If
    the initial move, or the move backward, lands the hare on a rock or in the stream, the hare moves
	backwards until the hare is not on a rock or stream. If in moving backward, this puts the hare on
	the tortoise, the hare gets moved back one position and the hare will have completed its move.  */

char* moveHare(char* hare, char* tortoise, int* collision, int* nap) {
	int chance = rand() % 3 + 1;								// determine a random number 1-3 for the napping chance
	if (chance == 1) {											// if chance equals one of the 3 numbers (hare is napping),
		*nap = 1;												// set nap flag to true
		*collision = 0;											// set collision flag to false
		return hare;											// return the hare pointer where it originally was
	}
	else if (*hare == 'C') {									// if the hare lands on a carrot,
		*nap = 0;												// set nap flag to false
		*collision = 0;											// set collision flag to false
		*hare = ' ';											// remove the carrot from the space
		return hare;											// return the hare pointer where it originally was
	}
	else {
		*nap = 0;												// else, set nap flag to false
		int move = rand() % 8 + 1;								// determine a random number 1-8 to be used as the move for the hare
		hare = hare + move;										// move the hare along the path
		if (hare == tortoise && (hare != 0 || tortoise != 0)) {	// if the tortoise and hare point to the same spot,
			hare = hare - 1;									// move the hare back one space
			*collision = 1;										// set the collision flag to true
		}
		else {
			*collision = 0;										// else, set the collision flag to false
		}
		if (*hare == 'R' || *hare == 'S') {						// if the hare lands on a rock or in a stream,
			while (*hare == 'R' || *hare == 'S') {				// while the hare is still on a rock or still in a stream
				hare = hare - 1;								// move the hare back one space
				if (hare == tortoise && (hare != 0 || tortoise != 0)) {		// if the tortoise and hare point to the same spot,
					hare = hare - 1;							// move the hare back one space
					*collision = 1;								// set the collision flag to true
					return hare;								// return the updated hare pointer
				}
				else {
					*collision = 0;								// else, set the collision flag to flase
					return hare;								// return the updated hare pointer
				}
			}
		}
		else {
			return hare;										// else, return the updated hare pointer
		}
		return hare;											// return the updated hare pointer
	}
}

/*	print function prints the current status of the game to the console.  It takes the current path,
	the tortoise and hare pointers, the turn, and the collision and nap flags.  For each turn, a line is
	output to the console.  It specifies which turn it is, prints out the path char by char with 'T' 
	representing the Tortoise and 'H' representing the Hare.  If a collision takes place or the hare is 
	napping, it is indicated on the consolse.   */

void print(char path[MAX], char* tortoise, char* hare, int turn, int collision, int nap) {
	printf("Turn %d: ", turn);											// print the turn to the console
	char* p;															// temp pointer to point at the path		
	for (p = path; p < path + MAX; p++) {								// p starts at path[0]	
		if (p == tortoise) {											// if p is at the same spot as tortoise, 
			printf("T");												// mark it with a 'T' by printing it to the console				
		}
		else if (p == hare) {											// if p is at the same spot as hare, 		
			printf("H");												// mark it with an 'H' by printing it to the console
		}
		else {																	
			printf("%c", *p);											// else, print out the char on the board
		}
	}
	if (collision == 1) {												// if a collision took place this turn,
		printf(" - collision - ");										// print 'collision' to the console
	}
	if (nap == 1) {														// if the hare naps this turn,
		printf(" - hare napping - ");									// print 'hare napping' to the console
	}
	printf("\n");														// new line
}

/* 

*** CONSOLE OUTPUT #1 ***
Turn 1: HT  R  R  SSSSS   R  R CCCC  R   R   CCCCCCCCCC  R  SSSS  R  - hare napping -
Turn 2:  R HT  R  SSSSS   R  R CCCC  R   R   CCCCCCCCCC  R  SSSS  R  - collision -
Turn 3:  R  RT RH SSSSS   R  R CCCC  R   R   CCCCCCCCCC  R  SSSS  R
Turn 4:  R  R  TH SSSSS   R  R CCCC  R   R   CCCCCCCCCC  R  SSSS  R  - hare napping -
Turn 5:  R  R  RHTSSSSS   R  R CCCC  R   R   CCCCCCCCCC  R  SSSS  R  - hare napping -
Turn 6:  R  R  R HSSTSS   R  R CCCC  R   R   CCCCCCCCCC  R  SSSS  R
Turn 7:  R  R  R  HSSST   R  R CCCC  R   R   CCCCCCCCCC  R  SSSS  R
Turn 8:  R  R  R  SSHSST  R  R CCCC  R   R   CCCCCCCCCC  R  SSSS  R
Turn 9:  R  R  R  SSSSS T R HR CCCC  R   R   CCCCCCCCCC  R  SSSS  R
Turn 10:  R  R  R  SSSSS   T HR CCCC  R   R   CCCCCCCCCC  R  SSSS  R  - hare napping -
Turn 11:  R  R  R  SSSSS   RT R CCHC  R   R   CCCCCCCCCC  R  SSSS  R
Turn 12:  R  R  R  SSSSS   R  T CCHC  R   R   CCCCCCCCCC  R  SSSS  R
Turn 13:  R  R  R  SSSSS   R  RTCC C  R  HR   CCCCCCCCCC  R  SSSS  R
Turn 14:  R  R  R  SSSSS   R  R TC C  R  HR   CCCCCCCCCC  R  SSSS  R  - hare napping -
Turn 15:  R  R  R  SSSSS   R  R CCTC  R  HR   CCCCCCCCCC  R  SSSS  R  - hare napping -
Turn 16:  R  R  R  SSSSS   R  R CC C TR   R  HCCCCCCCCCC  R  SSSS  R
Turn 17:  R  R  R  SSSSS   R  R CC C  R T R  HCCCCCCCCCC  R  SSSS  R  - hare napping -
Turn 18:  R  R  R  SSSSS   R  R CC C  R  TR   HCCCCCCCCC  R  SSSS  R
Turn 19:  R  R  R  SSSSS   R  R CC C  R   T   HCCCCCCCCC  R  SSSS  R
Turn 20:  R  R  R  SSSSS   R  R CC C  R   R T  CCCCCCHCC  R  SSSS  R
Turn 21:  R  R  R  SSSSS   R  R CC C  R   R  T CCCCCCHCC  R  SSSS  R
Turn 22:  R  R  R  SSSSS   R  R CC C  R   R    CTCCCC CC HR  SSSS  R
Turn 23:  R  R  R  SSSSS   R  R CC C  R   R    CCCCTC CC  R HSSSS  R
Turn 24:  R  R  R  SSSSS   R  R CC C  R   R    CCCCCC TC  R HSSSS  R  - hare napping -
Turn 25:  R  R  R  SSSSS   R  R CC C  R   R    CCCCCC CCT R HSSSS  R
Turn 26:  R  R  R  SSSSS   R  R CC C  R   R    CCCCCC CC  T HSSSS  R  - hare napping -
Turn 27:  R  R  R  SSSSS   R  R CC C  R   R    CCCCCC CC  RTHSSSS  R
Turn 28:  R  R  R  SSSSS   R  R CC C  R   R    CCCCCC CC  RTHSSSS  R  - hare napping -
Turn 29:  R  R  R  SSSSS   R  R CC C  R   R    CCCCCC CC  RT SSSS HR
Turn 30:  R  R  R  SSSSS   R  R CC C  R   R    CCCCCC CC  R  TSSS HR  - hare napping -
Turn 31:  R  R  R  SSSSS   R  R CC C  R   R    CCCCCC CC  R  SSST  R
Hare Wins!!!

***CONSOLE OUTPUT #2***
Turn 1:  R TRH R  SSSSS   R  R CCCC  R   R   CCCCCCCCCC  R  SSSS  R
Turn 2:  R  T  RH SSSSS   R  R CCCC  R   R   CCCCCCCCCC  R  SSSS  R
Turn 3:  R  R  T  SSSSSH  R  R CCCC  R   R   CCCCCCCCCC  R  SSSS  R
Turn 4:  R  R  RT SSSSSH  R  R CCCC  R   R   CCCCCCCCCC  R  SSSS  R  - hare napping -
Turn 5:  R  R  R  TSSSS H R  R CCCC  R   R   CCCCCCCCCC  R  SSSS  R
Turn 6:  R  R  R  SSTSS   R HR CCCC  R   R   CCCCCCCCCC  R  SSSS  R
Turn 7:  R  R  R  SSSSST  R HR CCCC  R   R   CCCCCCCCCC  R  SSSS  R  - hare napping -
Turn 8:  R  R  R  SSSSS   T HR CCCC  R   R   CCCCCCCCCC  R  SSSS  R  - hare napping -
Turn 9:  R  R  R  SSSSS   RTHR CCCC  R   R   CCCCCCCCCC  R  SSSS  R
Turn 10:  R  R  R  SSSSS   R HRTCCCC  R   R   CCCCCCCCCC  R  SSSS  R
Turn 11:  R  R  R  SSSSS   R  R CTCCH R   R   CCCCCCCCCC  R  SSSS  R
Turn 12:  R  R  R  SSSSS   R  R CCCT HR   R   CCCCCCCCCC  R  SSSS  R
Turn 13:  R  R  R  SSSSS   R  R CCCCT R H R   CCCCCCCCCC  R  SSSS  R
Turn 14:  R  R  R  SSSSS   R  R CCCC  RTH R   CCCCCCCCCC  R  SSSS  R  - hare napping -
Turn 15:  R  R  R  SSSSS   R  R CCCC  R  HT   CCCCCCCCCC  R  SSSS  R  - collision -
Turn 16:  R  R  R  SSSSS   R  R CCCC  R  HR T CCCCCCCCCC  R  SSSS  R
Turn 17:  R  R  R  SSSSS   R  R CCCC  R   R  TCHCCCCCCCC  R  SSSS  R
Turn 18:  R  R  R  SSSSS   R  R CCCC  R   R   THCCCCCCCC  R  SSSS  R
Turn 19:  R  R  R  SSSSS   R  R CCCC  R   R   CHTCCCCCCC  R  SSSS  R  - collision -
Turn 20:  R  R  R  SSSSS   R  R CCCC  R   R   C HTCCCCCC  R  SSSS  R
Turn 21:  R  R  R  SSSSS   R  R CCCC  R   R   C HCCCTCCC  R  SSSS  R
Turn 22:  R  R  R  SSSSS   R  R CCCC  R   R   C HCCCCTCC  R  SSSS  R  - hare napping -
Turn 23:  R  R  R  SSSSS   R  R CCCC  R   R   C  CCHCCTC  R  SSSS  R
Turn 24:  R  R  R  SSSSS   R  R CCCC  R   R   C  CCHCCCCT R  SSSS  R
Turn 25:  R  R  R  SSSSS   R  R CCCC  R   R   C  CC CCHC  RT SSSS  R
Turn 26:  R  R  R  SSSSS   R  R CCCC  R   R   C  CC CCHC  R TSSSS  R
Turn 27:  R  R  R  SSSSS   R  R CCCC  R   R   C  CC CCHC  R  TSSS  R  - hare napping -
Turn 28:  R  R  R  SSSSS   R  R CCCC  R   R   C  CC CCHC  R  SSTS  R  - hare napping -
Turn 29:  R  R  R  SSSSS   R  R CCCC  R   R   C  CC CCHC  R  SSSS TR  - hare napping -
Turn 30:  R  R  R  SSSSS   R  R CCCC  R   R   C  CC CCHC  R  SSSS  RT - hare napping -
Turn 31:  R  R  R  SSSSS   R  R CCCC  R   R   C  CC CCHC  R  SSSS  R  - hare napping -
Tortoise Wins!!!

*/


