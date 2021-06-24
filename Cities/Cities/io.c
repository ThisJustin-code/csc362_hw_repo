/* Justin Gallagher
   CSC 362 - 002
   Programming Assignment #2
   Friday, February 28th 2020 */

/* This io file includes the following: (1) an funtion that inputs one line of city data,
   (2) an output function that prints to the console on one line the the city name, its population dens and livability score,
   and (3) a summary function which prints to the console the number of cities input, the average livability, and the city
   with greatest livability and its value.  This file is to be used with main.c for computing city ratings based on various statistics. */

#include "header.h"                                                                         // include the header file

// function that grabs from first line of file the city name, population, square mileage, pollution, crime, expense, number of highways
void input(FILE* fp1, char* cityName, int* pop, int* squmil, int* pol, int* crime, int* exp, int* numhigh) {
	fscanf(fp1, "%s %d %d %d %d %d %d", cityName, pop, squmil, pol, crime, exp, numhigh);   // fscanf statment that uses the file pointer to access data from the input file
}

// function that outputs to the console on one line the city name, its population dens and livability score
void output(char* cityName, double livability, double popdens) {
	printf("%-20s %-20.2f %.2f\n", cityName, popdens, livability);  // printf statment that prints formatted data to the console
}

// function that outputs to the console the number of cities input, the average livability, and the city with greatest livability and its value
void summary(char* greatestLivabilityCityName, int numOfCities, double totalLivability, double greatestLivabilty) {
	double avgLivability = totalLivability / numOfCities;                       // calculate average livabilty using the total livabilty over the number of cities                                                                                    
	printf("\nOf the %d cities, the most livable was %s with a score of %.2f\nAverage livablilty amongst cities was %.2f\n",
        numOfCities, greatestLivabilityCityName, greatestLivabilty, avgLivability); // printf statement that prints the summary statment to the console
}