/***
* Poisson.c
* Author - Nurgaliev Ildar
*
* Poisson distribution
****/
#include <stdlib.h>
#include <time.h>
#include <math.h>

/** one instance of Seed **/
static int first_call = 1;

int samplePoisson(double lambda){
	/* Generate a random sample from a Poisson distribution */
	/* with a given mean, lambda */
	/* Use the function rand to generate a random number */
	int count;
	double product;
	double zero_probability;
	/* Seed the random-number generator with current time so */
	/* that the numbers will be different every time we run */
   if (first_call) {
      srand( (unsigned)time( NULL ));
      first_call = 0;
   }
	count = 0;
	product = (double) rand() / (double) RAND_MAX;
	zero_probability = exp(-lambda);
	while (product > zero_probability) {
		count++;
		product = product * ((double) rand() / (double) RAND_MAX);
	}
	return(count);
}