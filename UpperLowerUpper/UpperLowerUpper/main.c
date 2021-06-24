/* Justin Gallagher
   CSC 362 - 002
   Programming Assignment #1
   Friday, January 31st 2020 */

/* This program takes as its input a file, reads it, then based on the pattern given 
   in the instructions the program will output a character sequence. It also outputs 
   a summary, including the file names, the number of characters input and output, 
   and the percent reduction. */

#include <stdio.h>								// for file functions
#include <ctype.h>								// for char functions

void main() {

	char curr, last;							// holds the current character and last letter character
	char input[] = "prog1-in3.txt";				// the input file
	char output[] = "prog1-out3.txt";			// the output file
	int afterPeriod = 1;						// boolean to determine whether to print a capital letter (1 = after a period) 
	int numInput = 0;							// number of input letters count
	int numOutput = 0;							// number of output letters count
	FILE* fp1, * fp2;							// fp1 is a pointer to the input file, fp2 is a pointer to the output file
	fp1 = fopen(input, "r");					// open input file, read-only
	fp2 = fopen(output, "w");					// open output file, write-only

	while ((curr = getc(fp1)) != EOF) {         // get the next char from the input file until EOF is reached
		numInput++;								// increment the input count
		if (isalpha(curr)) {					// if curr is a letter,
			if (isupper(curr)) {				// if curr is an uppercase,
				if (afterPeriod == 1) {			// if curr does come after a period,
					putc(curr, fp2);			// output the curr char to the output file
					numOutput++;				// increment number of char outputs
					afterPeriod = 0;			// set afterPeriod to 0
				}
				else if (islower(last)) {		// if the last char was lowercase,
					putc(tolower(curr), fp2);	// output the lowercase curr char to the output file
					numOutput++;				// increment number of char outputs
				}
			}
			else {								// else, curr char is lowercase,
				if (isupper(last)) {			// if the last char was uppercase
					putc(curr, fp2);			// output the curr char to the output file
					numOutput++;				// increment number of char outputs
				}
			}
			last = curr;						// if curr is a letter, then last equals curr
		}
		else {									// else, curr is not a letter,
			putc(curr, fp2);					// output the curr char to the output file
			numOutput++;						// increment number of char outputs
			if (curr == '.') {					// if curr is a period,
				afterPeriod = 1;				// next uppercase should be output as uppercase, set afterPeriod to 1
			}
		}
	}
	// console output of the summary including filenames, number of characters, and percent reduction
	printf("Input File: %s\n", input);
	printf("Output File: %s\n", output);
	printf("Number of input characters: %d\n", numInput);
	printf("Number of output characters: %d\n", numOutput);
	printf("Percent reduction in output: %.2f%%\n", 100 * ((double)numOutput / numInput));
}

/* RESULTS
   
   prog1-in2 console output:

		Input File: prog1-in2.txt
		Output File: prog1-out2.txt
		Number of input characters: 348
		Number of output characters: 155
		Percent reduction in output: 44.54%

   prog1-out2:

		Information is not knowledge, knowledge is not wisdom.
		Wisdom is not truth, truth is not beauty.
		Beauty is not love, love is not music, music is the best.

   prog1-in3 console output:
	
		Input File: prog1-in3.txt
		Output File: prog1-out3.txt
		Number of input characters: 726
		Number of output characters: 672
		Percent reduction in output: 92.56%

   prog1-out3:

		Do not speak of withered trees, of lichen strangled coverings.
		And life just barely in the leaves, it will not be undone.

		Do not speak of withered trees, of lichen strangled coverings.
		And life just barely in the leaves, it will not be undone.

		Do not speak of what we've seen, of water choking algae.
		And dust where fountains used to be, it will not be undone.
		A wilderness unraveling, we've only just begun.

		Do not speak of ice retreat, of islands eaten by the sea.
		And industry economy, we've only just begun, it will not be undone.

		Do not speak, oh do not speak, your tongue is dry, your voice is weak.
		The time has passed for words to seek, it will not be undone.
*/