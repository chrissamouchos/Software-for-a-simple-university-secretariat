/*File that contains the prototypes of various functions*/
#pragma once	/*Include only once*/

#include "ADTHashtable.h"

/*----------------- VARIOUS FUNCTIONS-------------------*/
void red();		/*Chane printing color to red 	*/

void green();	/*Chane printing color to green	*/

void cyan();	/*Chane printing color to cyan	*/

void reset();	/*Reset color to default		*/

int line_counter(char* input);	/*Count the lines of input file*/

void read_and_insert(char* input, int number_of_lines, Headhash head);	/*Read file and insert parsed data*/

void usage(const char* command);	/*Print expected format*/
/*----------------- END OF FUNCTIONS--------------------*/