/***
* Assignment2.c - assignment #2 (ADS)
* Author - Nurgaliev Ildar		
*	
****/
#include "Util.h"
#include "Assignment2.h"
#include "Queue.h"
#include "Poisson.h"
#include "Logger.h"
#include <stdlib.h>

/**
* Assign appropriate row's value to a pointer in params, instead of map implementation
**/
void init_values(int *arrival, int *avg_departure, int *runtime, int *increment, int *red_timeout, int *green_timeout, FILE *f_input){
	int i, temp_value;
	char key_name[11];

	for (i=0; i<6;i++){
		/* read key name and value */
		if(!fscanf(f_input, "%s %d",key_name , &temp_value)) {\
			error(MSG_INVALID_INPUT_STRUCTURE"\n");\
		}
		/* string modification: trim and to lower case */
		trim(key_name);
		tolower_string(key_name);
		/* There is 6 defined possible keys, in order to find param's value */
		if (equal(key_name,key_arrival)) {
			*arrival = temp_value;
		}else if (equal(key_name,key_departure)){
			*avg_departure = temp_value;
		}else if (equal(key_name,key_runtime)){
			*runtime  = temp_value;
		}else if (equal(key_name,key_increment)){
			*increment = temp_value;
		}else if (equal(key_name,key_red)){
			*red_timeout  = temp_value;
		}else if (equal(key_name,key_green)){
			*green_timeout = temp_value;
		}
	}
}

/**
* traffic simulation, prints to output file results of traffic queue's information
**/
void simulate_traffic(double arrival_rate_minute, double avg_departure, double runtime, double increment, double red_timeout, double green_timeout, FILE *f_output) {
	/* values to find */
	double avr_queue_length = 0,
		avr_waiting_time = 0,
		max_waiting_time = 0;
	int max_queue_length = 0;
	
	double current_time = 0, 
		increment_per_s = increment / 1000,
		/* counts the trafic light's timeout in seconds for both lighths */
		traffic_light_timeout = 0,
		/* counts the departure timeout in seconds */
		departure_counter = 0;

	/* for Poisson distribution */
	const double lambda = (arrival_rate_minute / 60) * increment_per_s;

	/* tics under discret time peice */
	int tic_counter = 0, 		
		car_total_number = 0,
		i, j, car_incom_count, queue_length;

	/* firstly filling queue for testing traffic */
	int current_state = LIGHT_RED;

	/* declare queue and */
	ELEMENT_TYPE car;
	LIST_TYPE queue; 
	declare(&queue);

	/* while current_time is seconds doesnot overpass runtime */
	while((current_time = tic_counter * increment_per_s) < runtime * 60) {
		/* check trafic light */
		if (current_state == LIGHT_GREEN) {
			if (traffic_light_timeout < green_timeout) {
				traffic_light_timeout += increment_per_s ;
			} else {
				traffic_light_timeout = 0;
				/* special case of red_timeout = 0 */
				if (red_timeout != 0) {
					current_state = LIGHT_RED;
				}
			}
		} else {
			if (traffic_light_timeout  < red_timeout) {
				traffic_light_timeout += increment_per_s ;
			} else {
				traffic_light_timeout = 0;
				/* the traffic light changes to red on the next tic */
				departure_counter = 0;

				/* special case of green_timeout = 0 */
				if(green_timeout != 0) {
					current_state = LIGHT_GREEN;
				}
			}
		}

		/* random number of incoming cars per tic */
		car_incom_count = samplePoisson(lambda);
		car_total_number += car_incom_count;

		/* add to queue all the cars incomed while the tic */
		for(i = 0; i < car_incom_count; i++) {
			assign_element_values(&car, current_time);
			enqueue(car,&queue);
		}

		queue_length = size(&queue);
		avr_queue_length += queue_length;
		/* check max_length of th queue */
		if (max_queue_length < queue_length) {
			max_queue_length = queue_length;
		}

		/* outcoming  cars per tic while light traffic is green */
		if (current_state == LIGHT_GREEN) {
			/* in case when queue is not empty and departure time bigger than average departure time */
			if (departure_counter > avg_departure && !is_empty(&queue)) {
				/* amount of left cars depends on average departure time and time increment */
				for (j = 0; j < (departure_counter / avg_departure) && !is_empty(&queue); j++) {
					/* always cycle has not a lot of iterations it is accesible to reassign departure_counter value inside cycle
					for readability of source code */
					departure_counter = 0;

					car = dequeque(&queue);

					/* find max waiting time */
					if (max_waiting_time < current_time - car.value) {
						max_waiting_time = current_time - car.value;
					}

					avr_waiting_time += current_time - car.value;
				}
			}
		}		
		
		tic_counter++;
		departure_counter+=increment_per_s;
	}
	/* maybe not precisely true but easyest way for getting average queue's length */
	avr_queue_length = avr_queue_length / tic_counter;
	/* check the rest of the queue */
	while (!is_empty(&queue)) {
		car = dequeque(&queue);
		avr_waiting_time += current_time - car.value;

		/* check max_length of th queue */
		if (max_waiting_time < current_time - car.value) {
			max_waiting_time = current_time - car.value;
		}
	}

	/* total waiting to divide to total car amount */
	avr_waiting_time = avr_waiting_time / car_total_number;

	/* output the simulation results */
	fprintf(f_output, p_avg_len,  round(avr_queue_length));
	fprintf(f_output, p_max_len,  round(max_queue_length));
	fprintf(f_output, p_avg_wait, round(avr_waiting_time));
	fprintf(f_output, p_max_wait, round(max_waiting_time));

	empty(&queue);
	free(queue);
}

int main(void) {
	/* count of trafic tests */
	int trafic_test_count = 0;
	/* The arrival rate in vehicles per minute. */
	int arrival_rate_minute;
	/* The average departure time per car in seconds */
	int avg_departure;
	/* The running time for the simulation, specified in minutes. */
	int runtime;
	/* The time increment to use for each discrete interval of simulation, specified in milliseconds. */
	int increment;
	/* The traffic light sequencing given by the time the lights stay green and the time the
	lights stay red, both times specified in seconds. */
	int red_timeout, green_timeout;
	/* iterator's item */
	int i;

	/* files for input and output collaboration */
	FILE *f_input;
	FILE *f_output;
	if ((f_input = fopen(input_file_name, "r")) == NULL ||
		(f_output = fopen(output_file_name, "w")) == NULL){
			error("File cannot be open.");
	}

	/* get trafic_test_count */
	if (fscanf(f_input, "%d", &trafic_test_count) == 0) {
		error(MSG_INVALID_INPUT_STRUCTURE);
	} else if (!(trafic_test_count > 0 && trafic_test_count < TEST_COUNT_MAX)) {
		error("Test count's limit exception.");
	}
	/* print AUTHOR_NAME in the first row */
	fprintf(f_output, "%s\n",AUTHOR_NAME);

	for (i =0;i < trafic_test_count;i++){
		/* read data */
		init_values(&arrival_rate_minute, &avg_departure, &runtime, &increment, &red_timeout, &green_timeout,f_input);

		/* output results based on patterns defined in "Assignment2.h" */
		fprintf(f_output, p_arrival_rate, arrival_rate_minute);
		fprintf(f_output, p_departure, avg_departure);
		fprintf(f_output, p_runtime,runtime);
		fprintf(f_output, p_time_increment,increment);
		fprintf(f_output, p_light_seq,red_timeout,green_timeout);

		/* start simulation */
		simulate_traffic(arrival_rate_minute,  avg_departure,  runtime,  increment,  red_timeout,  green_timeout, f_output);
		/* empty row between traffic test results */
		fprintf(f_output, "\n");
	}
	fclose(f_input);
	fclose(f_output);
}