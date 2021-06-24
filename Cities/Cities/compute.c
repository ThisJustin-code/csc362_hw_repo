/* Justin Gallagher
   CSC 362 - 002
   Programming Assignment #2
   Friday, February 28th 2020 */

/* This computation file includes the following: (1) a funtion to compute the population density based off of the population and square mileage,
   (2) a function to compute the pollution rating, traffic rating, crime per capita, and expense per capita using the population dens, pollution, 
   crime, expense and number of highways, (3) a funtion to compute the livability based off of pollution rating, traffic rating, crime per capita, and expense per capita,
   and (4) an update function that keeps updated the number of cities input, total livability, and city with greatest livability and its value. */

#include "header.h"                                                                 // include the header file

// computePD funtion to compute the population density based off of the populationand square mileage
void computePD(int pop, int squmil, double* popdens) {
    *popdens = (double)pop / squmil;        // calculate population density, cast int to double
}

// computePTCE function to compute the pollution rating, traffic rating, crime per capita, and expense per capita using the population dens, pollution, 
// crime, expenseand number of highways
void computePTCE(int pol, int numhigh, int crime, int exp, double popdens, double* polRating, double* trafficRating, double* crimePerCapita, double* expPerCapita) {
    *polRating = (pol * popdens) / 1000;                                    // calculate pollution rating
    *trafficRating = (popdens * TRAFFIC_RATING_CONSTANT) / numhigh;         // calculate traffic rating (uses constant)
    *crimePerCapita = (crime * popdens) / CRIME_CONSTANT;                   // calculate crime per capita (uses constant)
    *expPerCapita = (exp * popdens) / EXPENSE_CONSTANT;                     // calculate expense per capita (uses constant)
}

// computeL funtion to compute the livability based off of pollution rating, traffic rating, crime per capita, and expense per capita
void computeL(double polRating, double trafficRating, double crimePerCapita, double expPerCapita, double* livability) {
    *livability = 100 - ((polRating + trafficRating + crimePerCapita + expPerCapita) / LIVABILITY_CONSTANT); // calculate livability (uses constant)
}

// update function that keeps updated the number of cities input, total livability, and city with greatest livability and its value
void update(double livability, char* cityName, char* greatestLivabilityCityName, int* numOfCities, double* totalLivability, double* greatestLivabilty) {
    *numOfCities = *numOfCities + 1;                                // increment number of cities
    *totalLivability = *totalLivability + livability;               // calculate total livability
    double temp = *greatestLivabilty;                               // create a temp value for comparing
    if (livability > temp) {                                        // if livability is greater than the greatest current livability
        *greatestLivabilty = livability;                            // set the greatest current livability to be the new livabilty 
        strcpy(greatestLivabilityCityName, cityName);               // set the name
    }
}