/* Justin Gallagher
   CSC 362 - 002
   Programming Assignment #2
   Friday, February 28th 2020 */

/* This program will compute city ratings based on various statistics. The input will come from a
   text file. Inputs one city’s information at a time using fscanf. After input, it calls
   various functions to perform computations on that city and assigns the city a rating. An output
   function will output some of the computed values including the rating for the city. It keeps track of
   the number of cities evaluated and the sum of their ratings along with the highest scored livabilty city (both
   its rating and city name). After evaluating all of the cities in the file, the program ends by
   outputting a summary including the number of cities evaluated, the average livability rating, and the
   highest scored livabilty city’s name and rating. */

#include "header.h"                                                                // include the header file																

main() {

	FILE* fp1;																		// file pointer
	fp1 = fopen("cities2.txt", "r");												// open input file for reading
	
	// declare variables:
	// (1) strings: the city name, the name of the highest rated city, and strings used for output
	char cityName[20], greatestLivabilityCityName[20], o1[] = "City", o2[] = "Population Dens", o3[] = "Livability Score";
	// (2) integers: populaton, square milage, crime, expense, number of highways, number of cities
	int pop, squmil, pol, crime, exp, numhigh;
	int numOfCities = 0;
	// (3) doubles: population density, pollution rating, traffic rating, crime per capita, expense per capita, livability, total liv, greatest liv
	double popdens, polRating, trafficRating, crimePerCapita, expPerCapita, livability, totalLivability = 0, greatestLivabilty = 0;

	printf("%-15s %-20s %s\n", o1, o2, o3);				// printf statment that outputs to the console formatted columns for the cities, pop dens, and livability

	while (!feof(fp1)) {																// while the end of file has not been reached
		input(fp1, cityName, &pop, &squmil, &pol, &crime, &exp, &numhigh);				// call the input function
		computePD(pop, squmil, &popdens);												// call the compute population dens function
		computePTCE(pol, numhigh, crime, exp, popdens, &polRating, &trafficRating, &crimePerCapita, &expPerCapita);	// call the compute pollution, traffic, crime, and expense ratings funtion
		computeL(polRating, trafficRating, crimePerCapita, expPerCapita, &livability);	// call the compute livability function
		update(livability, cityName, greatestLivabilityCityName, &numOfCities, &totalLivability, &greatestLivabilty);	// call the update function
		output(cityName, livability, popdens);											// call the output function
	}																					// end of the loop

	summary(greatestLivabilityCityName, numOfCities, totalLivability, greatestLivabilty); // print summary statement 

	fclose(fp1);																		// close the file

}




/* (1) "cities1.txt" OUTPUT:
City            Population Dens      Livability Score
Akron                331.98               57.81
Cincinnati           276.13               75.90
Cleveland            299.32               72.28
Columbus             371.63               60.54
Dayton               278.48               74.00
Toledo               325.83               65.95

Of the 6 cities, the most livable was Cincinnati with a score of 75.90
Average livablilty amongst cities was 67.75
*/

/* (2) "cities2.txt" OUTPUT:
City            Population Dens      Livability Score
Atlanta              443.12               55.02
Boston               519.65               34.87
Cincinnati           276.13               75.90
Dallas               273.46               76.58
Las_Vegas            154.44               84.91
Los_Angeles          566.09               17.72
Minneapolis          323.74               69.47
New_York_City        829.75               1.01
Seattle              373.01               56.78
Washington_DC        493.87               41.80

Of the 10 cities, the most livable was Las_Vegas with a score of 84.91
Average livablilty amongst cities was 51.40
*/





