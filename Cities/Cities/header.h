/* Justin Gallagher
   CSC 362 - 002
   Programming Assignment #2
   Friday, February 28th 2020 */

/* This header file includes the following: (1) include statements, (2) prototypes, and (3) constant declarations
   that are used for computing city ratings based on various statistics. */

#pragma once

// Include statements:
#include <stdio.h>													// for file functions		
#include <string.h>                                                 // for string functions

// Prototypes:
void input(FILE*, char*, int*, int*, int*, int*, int*, int*);		// grab from first line of file the city name, population, square mileage, pollution, crime, expense, number of highways
void computePD(int, int, double*);                                  // compute the population density based off of the population and square mileage
void computePTCE(int, int, int, int, double, double*, double*, double*, double*);	// compute the pollution rating, traffic rating, crime per capita, and expense per capita using the population dens, pollution, crime, expense and number of highways
void computeL(double, double, double, double, double*);             // compute the livability based off of pollution rating, traffic rating, crime per capita, and expense per capita
void update(double, char*, char*, int*, double*, double*);          // keeps updated the number of cities input, total livability, and city with greatest livability and its value
void output(char*, double, double);	                                // outputs to the console on one line the city name, its population dens and livability score
void summary(char*, int, double, double);                           // outputs to the console the number of cities input, the average livability, and the city with greatest livability and its value

// Constants:
#define TRAFFIC_RATING_CONSTANT 1.7								    // define traffic rating equation constant
#define CRIME_CONSTANT 872.6								        // define crime per capita equation constant
#define EXPENSE_CONSTANT 1217.1									    // define expense per capita equation constant
#define LIVABILITY_CONSTANT 13.81									// define livability rating equation constant



