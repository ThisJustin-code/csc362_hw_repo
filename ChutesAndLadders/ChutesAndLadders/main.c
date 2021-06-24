/* Justin Gallagher
   CSC 362 - 001
   Programming Assignment #3
   Wednesday, October 16th 2019 */

/* This program generates a game of chutes and ladders using pointers and arrays.  The program creates
   two players and puts them on a board.  The board contains characters that represent different events 
   in the game.  When a specific square is landed on, the program will calculate the moves that are 
   needed and apply the move to that player.  The user is kept updated by console output that follows and
   explains each move.  At the end of the program, the winner is determined and a text file is created 
   that has the board as text output for each move made.*/

//DEFINE CONSTANTS
#define SIZE 100																// Define constant size
//INCLUDE STATEMENTS
#include <stdio.h>																// include for file functions
//PROTOTYPES
void output(char board[SIZE], char *, char *, FILE *);							// outputs board to the output file
char * move(char *, char *, char board[SIZE], int);								// determines where the player will move
char * findHaven(char *, char board[SIZE]);										// finds the next closest haven to player
char* chuteLadder(char *, char board[SIZE]);									// calculate distance for chutes and ladders

main() {
	char* p1, * p2;																// create char pointers for player 1 and 2
	int turn;																	// turn used for keeping track of which turn is it
	char board[SIZE] = "  mHk  H l B He Flq p H  hByHlho H B  jr HFB ir j H  F ku gd  H pjB mH x  BF i H  m oB HlHFBhoH BB "; // game board
	FILE* fp1;																	// file pointer for output
	fp1 = fopen("output.txt", "w");												// open output file 'write'
	srand(time(NULL));															// seed the random num gen
	p1 = p2 = board;															// p1 and p2 point to the 0th square
	while ((p1 >= board && p1 < board + SIZE) 
		&& (p2 >= board && p2 < board + SIZE)) {								// while p1 and p2 are in the bounds of the board
		p1 = move(p1, p2, board, 1);											// call move function to move p1
		p2 = move(p2, p1, board, 2);											// call move function to move p2
		output(board, p1, p2, fp1);												// output the board results to the output file
	}
	if (p1 >= p2) {																// determine if player 1 won
		printf("\nPlayer 1 Wins the Game!!!");
	}
	else if (p2 > p1) {															// determine if player 2 won
		printf("\nPlayer 2 Wins the Game!!!");
	}
	fclose(fp1);																// close the output file
}
/* Output function takes the board, player pointers, and the output file and iterates through the board
   looking for the pointers.  If a pointer is found, the players number is printed to the text file.  If
   no pointer is found, then the board value is printed out.  At the end of the program, the output file 
   will contain all moves made on the board. */
void output(char board[SIZE], char* p1, char* p2, FILE* fp1) {
	char* bp;																	// create board pointer
	for (bp = board; bp < board + SIZE; bp++) {									// for bp starting at board[0] until board + 100
		if (bp == p1) {															// if bp points to player 1
			fprintf(fp1, "%d", 1);												// print 1
		}
		else if (bp == p2) {													// if bp points to player 2
			fprintf(fp1, "%d", 2);												// print 2
		}
		else {																	// bp doesnt point to p1 or p2
			fprintf(fp1, "%c", *bp);											// print board value
		}
	}
	fprintf(fp1, "\n");															// new line
}

/* Move function takes the player pointers, the board, and which turn it is and determines where the 
player will need to do.  The player will roll and move the amount of spaces given by roll and then 
either (1) land on a chute or ladder, in which the chuteLadder function will be called, (2) land on 
a 'B' or 'F' in which the function findHaven will be called, or (3) a collision of the two players 
in which the last player to move is moved back one space.  Updates are kept by outputing to the console
specific moves that are being made.  This function ultimately returns the players position.
*/
char * move(char *p1, char *p2, char board[SIZE], int turn) {
	int roll = rand() % 6 + 1;													// create random number 1 - 6 for dice roll
	p1 = p1 + roll;																// move p1 'roll' times
	printf("\nPlayer %d moves %d spaces and is currently at square %d ",
		turn, roll, (p1 - board));												// print where player is after roll
	if (p1 >= board && p1 < board + SIZE) {										// if player is in bounds of the board
		if (*p1 >= 'a' && *p1 <= 'm') {											// if player is on a chute
			p1 = chuteLadder(p1, board);										// call chuteLadder function
			printf("which is a chute and is moving back to square %d ",
				(p1 - board));													// output chute results
		}
		if (*p1 >= 'o' && *p1 <= 'z') {											// if player is on a ladder
			p1 = chuteLadder(p1, board);										// call chuteLadder function
			printf("which is a ladder and is moving forward to square %d ",     
				(p1 - board));													// output ladder results
		}
		if (*p1 == 'B' || *p1 == 'F') {											// if player is on a back or forward
			if (*p1 == 'B') {													// if player moves back
				p1 = findHaven(p1, board);										// call findHaven function
				printf("which is a 'B' so is moving back ");					// print back results
				if (p1 == board) {												// if no havens found
					printf("and with no more havens, lands at 0 ");				// print back results
				}
				else {															// haven found
					printf("and lands at %d ", (p1 - board));					// print back results
				}
			}
			if (*p1 == 'F') {													// if player moves back
				char* temp = p1;												// create temp pointer
				p1 = findHaven(p1, board);										// call findHaven function
				printf("which is a 'F' so is moving forward ");					// print forward results
				if (p1 == temp) {												// if player did not move
					printf(
						"and with no more havens, stays at current location "); // print forward results
				}
				else {															// player moved forward
					printf("and lands at %d ", (p1 - board));					// print forward results
				}
			}
		}
		if (p1 == p2 && (p1 != 0 || p2 != 0)) {									// if there is a collision
			p1 = p1 - 1;														// player gets moved back one square
			printf("-- Collision! %d is moving back 1 square to %d ",
				turn, (p1 - board));											// print collision results
		}
	}
	return p1;																	// return the position of player
}

/* findHaven method takes a player pointer and the board and looks for the next haven square the player 
   can move to.  If the player is moving backwards and no haven is found, then the player moves back to 
   square 0.  If the player is moving forward and no haven is found, the player stays in its current square.
   If a haven is found in either direction, the player will move to the haven.  Havens are then replaced so 
   they cannot be used again. */
char * findHaven(char * p1, char board[SIZE]) {
	char* bp;																	// create board pointer
	if (*p1 == 'B') {															// if p1 needs to move back
		for (bp = p1; bp >= board; bp--) {										// start from p1 position and search back in the board
			if (*bp == 'H') {													// if a haven is found
				p1 = bp;														// move p1 to the haven
				*bp = '*';														// replace haven
				return p1;														// return position for player 1
			}
		}
		p1 = board;																// no haven is found, set p1 to square 0
		return p1;																// return p1 position
	}
	else if (*p1 == 'F') {														// if p1 needs to move forward
		for (bp = p1; bp < board + SIZE; bp++) {								// start from p1 position and search forward in the board
			if (*bp == 'H') {													// if a haven is found
				p1 = bp;														// move p1 to the haven
				*bp = '*';														// replace haven
				return p1;														// return position for player 1
			}
		}
		return p1;																// no haven is found, return p1 position
	}
}

/* chuteLadder is a funtion that takes a player pointer and the board and calculates how far to move on the 
   board based on the ASCII value of the letter landed on subtracted by the ASCII value for 'n'.  If negative, 
   move back. Positive moves forward. This is calculated as distance and is returned as the new position of 
   the player. The chutes and ladders are also replaced so they cannot be used again. */
char* chuteLadder(char* p1, char board[SIZE]) {
	char* distance = p1 + (int)(*p1 - 'n');										// calulate distance to move player
	*p1 = '-';																	// replace the chutes and ladders
	return distance;															// return the new player position
}

