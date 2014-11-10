/***
* Assignemnt2.h
* Author: Nurgaliev Ildar
*
* Test cases in 'test_scopes' folder:
*	test-1: test from given list
*
*	test-2: ignore tabs and spaces in the start or in the end or between key value data
*
*	test-3: case insensitive reading of keys
*
*	test-4: rows of key value pairs are placed in differ order
*
*	test-5: green trafic light all the time
*
*	test-6: red trafic light all the time
*
****/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* relative path to input and output files in build directory */
#define input_file_name "input.txt"
#define output_file_name "output.txt"

#define TEST_COUNT_MAX 1000
#define AUTHOR_NAME "Nurgaliev Ildar"
#define MSG_INVALID_INPUT_STRUCTURE "Invalid input structure of the input file."
/* output patterns */
#define p_arrival_rate   "Arrival rate:   %d cars per minute\n"
#define p_departure      "Departure:      %d seconds per car\n"
#define p_runtime        "Runtime:        %d minutes\n"
#define p_time_increment "Time increment: %d milliseconds\n"
#define p_light_seq      "Light sequence: Red %d seconds; Green %d seconds\n"
#define p_avg_len        "Average length: %d cars\n"
#define p_max_len        "Maximum length: %d cars\n"
#define p_avg_wait       "Average wait:   %d seconds\n"
#define p_max_wait       "Maximum wait:   %d seconds\n"

#define key_arrival "arrival"
#define key_departure "departure"
#define key_runtime "runtime"
#define key_increment "increment"
#define key_red "red"   
#define key_green "green"

#define round(dnum) (int) (dnum+0.5)
#define equal(s1,s2) strcmp(s1, s2) == 0

#define LIGHT_RED 0
#define LIGHT_GREEN 1