/*File that contains source code of various functions*/
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
	FILE* fp = fopen(input, "r");	/*Create pointer to opened file*/
	int counter = 0;
	int value;
	while((value = fgetc(fp)) != EOF){	/*Each time new line is found increase counter*/
		if(value == '\n')	counter++;
	}
	fclose(fp);						/*Close file and free allocated space*/
	
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
			args[j] = strtok(line, delim);	/*Parse data with respect to delim character*/
		}

		/*Insert acquired data as a student object to already existing hashtable*/
		hashtable_insert(student_create(atoi(args[0]), args[1], args[2], atoi(args[3]), atoi(args[4]), atoi(args[5])), head);
		free(line);
	}

	fclose(fp);

	return;
}

void usage(const char* command){		/*Print expected command format*/
	cyan();
	printf("%s -i <input file> -c <config file>\n",command);
	reset();
}

void exiting(Headhash head){
	printf(">>");
	cyan();
	printf("\t exit program\n");
	reset();
	hashtable_destroy(head);
}

void trim(char* line){
	int counter = strlen(line);
	if(line[counter - 1] == '\n')	line[counter - 1] = '\0';
}

int commandcode(char* line){
	for(int i = 0; i <= kCOMSNUM; i++){
		if(strcmp(line, commands[i]) == 0) return i;
	}
	return kFALSECOM;
}

/*----------------- END OF FUNCTIONS--------------------*/