#include <stdio.h>
#include <stdlib.h>

#include "Utils.h"
#include "ADTHashtable.h"

/*----------------- VARIOUS FUNCTIONS-------------------*/
void red(){
 	printf("\033[1;31m");
}

void green(){
	printf("\033[1;32m");
}

void cyan(){
	printf("\033[1;36m");
}

void reset(){
 	printf("\033[0m");
}

int line_counter(char* input){
	FILE* fp = fopen(input, "r");
	int counter = 0;
	int value;
	while((value = fgetc(fp)) != EOF){
		if(value == '\n')	counter++;
	}
	fclose(fp);
	
	return counter;
}

void read_and_insert(char* input, int number_of_lines, Headhash head){
	FILE* fp = fopen(input, "r"); 		/*Open input file to parse it's data*/
	char* line = NULL;					/*Temporary store read string		*/
	size_t size = 0;

	char* args[6];		/*6 arguments to parse						*/
	char* delim = " ";	/*arguments are seperated by space character*/

	for(int i = 0; i < number_of_lines; i++){	/*Get each line of input file*/
		line = NULL;
		size = 0;
		getline(&line, &size, fp);
		for(int j = 0; j <= 5; j++){
			args[j] = strtok(line, delim);
			// line = NULL;
		}
		hashtable_insert(student_create(atoi(args[0]), args[1], args[2], atoi(args[3]), atoi(args[4]), atoi(args[5])), head);
		free(line);
	}
	fclose(fp);

	return;
}
/*----------------- END OF FUNCTIONS--------------------*/