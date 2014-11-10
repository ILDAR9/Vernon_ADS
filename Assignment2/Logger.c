/***
* Logger.c
* Author - Nurgaliev Ildar
*
* error realisation
*
****/
#include <stdio.h>
#include <stdlib.h>

/*** error handler: print message passed as argument and
 take appropriate action ***/
void error(const char *er_message) {
    printf("Error: %s\n", er_message);
	getchar();
    exit(1);
}