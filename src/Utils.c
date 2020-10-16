/*File that contains source code of various functions*/
#include <stdio.h>
#include <stdlib.h>

#include "Utils.h"
#include "ADTHashtable.h"
#include "ADTInvertedIndex.h"

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

void read_and_insert(char* input, int number_of_lines, Headhash head, InvIndex inv){
	FILE* fp = fopen(input, "r"); 		/*Open input file to parse it's data*/
	char* line = NULL,*temp;					/*Temporary store read string		*/
	size_t size = 0;

	char* args[6];		/*6 arguments to parse						*/
	char* delim = " ";	/*arguments are seperated by space character*/

	for(int i = 0; i < number_of_lines; i++){	/*Get each line of input file*/
		line = NULL;
		size = 0;
		getline(&line, &size, fp);
		temp = line;
		for(int j = 0; j <= 5; j++){
			args[j] = strtok(temp, delim);	/*Parse data with respect to delim character*/
			temp = NULL;
		}

		/*Insert acquired data as a student object to already existing hashtable*/
		Student s = student_create(atoi(args[0]), args[1], args[2], atoi(args[3]), atoi(args[4]), strtof(args[5], NULL));
		hashtable_insert(s, head);
		invindex_insert(inv, s);
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

void trim(char* line){
	int counter = strlen(line);
	if(line[counter - 1] == '\n')	line[counter - 1] = '\0';
}

int commandcode(char* line){
	if(line == NULL){
		return -1;
	}
	for(int i = 0; i <= kCOMSNUM; i++){
		if(strcmp(line, commands[i]) == 0 || (line[0] == commands[i][0] && strlen(line) == 1)) return i;
	}
	return kFALSECOM;
}

char* command_string(char* line){
	char* delim = " ";	/*arguments are seperated by space character*/
	return strtok(line, delim);
}
/*----------------- END OF FUNCTIONS--------------------*/

/*------------------START OF COMMAND FUNCTIONS----------*/
void user_insert(char* line, Headhash head, InvIndex inv){
	char* args[7] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL};	/*6 arguments to parse						*/
	char* delim = " ";										/*arguments are seperated by space character*/
	for(int i = 0; i < 7; i++){
		args[i] = strtok(line, delim);	/*Parse data with respect to delim character*/
		line = NULL;
	}
	for(int i = 0; i < 7; i++){
		if( args[i] == NULL){
			red();
			printf("\t - Invalid command format\n");
			reset();
			return;
		}
	}
	Student s = student_create(atoi(args[1]), // id
		 args[2], // lname
		 args[3], //fname
		 atoi(args[4]), // zip
		 atoi(args[5]), // year
		 strtof(args[6],NULL)); // GPA

	int flag = hashtable_insert(s, head);

	if(flag == 1){
		red();
		printf("\t - Student %d exists\n", atoi(args[1]));
		reset();
	}
	else{
		green();
		printf("\t - Student %d inserted\n", atoi(args[1]));
		invindex_insert(inv, s);
		reset();
	}
}

void exiting(Headhash head){
	printf(">>");
	cyan();
	printf("\t exit program\n");
	reset();
	hashtable_destroy(head);
}

void look_up(char* line, Headhash head){
	char* args[2] = {NULL,NULL};		/*2 arguments to parse						*/
	char* delim = " ";	/*arguments are seperated by space character*/
	for(int i = 0; i < 2; i++){
		args[i] = strtok(line, delim);	/*Parse data with respect to delim character*/
		line = NULL;
	}
	for(int i = 0; i < 2; i++){
		if( args[i] == NULL){
			red();
			printf("\t - Invalid command format for %s\n", args[0]);
			reset();
			return;
		}
	}
	Student s = hashtable_find(atoi(args[1]), head);
	if(s == NULL){
		red();
		printf("\t- Student %s does not exist!\n", args[1]);	/*arg1 is string*/
		reset();
	}
	else{
		green();
		printf("\t -");
		print_student(s);
		printf("\n");
		reset();
	}
}

void number_year(InvIndex inv, char* line){
	char* args[2] = {NULL,NULL};		/*2 arguments to parse						*/
	char* delim = " ";					/*arguments are seperated by space character*/
	
	for(int i = 0; i < 2; i++){
		args[i] = strtok(line, delim);	/*Parse data with respect to delim character*/
		line = NULL;
	}
	for(int i = 0; i < 2; i++){
		if( args[i] == NULL){
			red();
			printf("\t - Invalid command format for %s\n", args[0]);
			reset();
			return;
		}
	}
	int tyear = atoi(args[1]);
	while(inv != NULL && inv->year <= tyear){
		if(inv -> year == tyear){
			printf("\t -%d student(s) in %d\n", inv->size, inv->year);
			return;
		}
		inv = inv -> next;
	}
	red();
	printf("\t -No student(s) enrolled %d\n", tyear);
	reset();
}

void year_count(InvIndex inv, char* line){	
	if(inv == NULL || inv -> year == -1){
		red();
		printf("\t -No students are enrolled \n");
		reset();
	}
	while(inv != NULL){
		printf("\t - %d\t %d \n", inv->year, inv->size);
		inv = inv -> next;
	}
}

void average(InvIndex inv, char* line){
	char* args[2] = {NULL,NULL};		/*2 arguments to parse						*/
	char* delim = " ";					/*arguments are seperated by space character*/

	for(int i = 0; i < 2; i++){
		args[i] = strtok(line, delim);	/*Parse data with respect to delim character*/
		line = NULL;
	}
	for(int i = 0; i < 2; i++){
		if( args[i] == NULL){
			red();
			printf("\t - Invalid command format for %s\n", args[0]);
			reset();
			return;
		}
	}

	int tyear = atoi(args[1]);
	float sum_gpa = 0;
	if(inv == NULL || inv -> year == -1){
		red();
		printf("\t- No students enrolled in %d\n", tyear);
		reset();
		return;
	}
	
	while(inv != NULL && inv->year <= tyear){
		if(inv -> year == tyear){
			innerlist* temp = inv -> students;
			while(temp != NULL){
				sum_gpa += (temp -> student -> gpa);
				temp = temp -> next;
			}
			sum_gpa = sum_gpa/(inv -> size);
			break;
		}
		inv = inv -> next;
	}
	if(inv != NULL && inv->year <= tyear){
		green();
		printf("\t - Average %.4f in %d\n", sum_gpa, tyear);
		reset();
	}
	else{
		red();
		printf("\t - No students enrolled in %d\n", tyear);
		reset();
	}
}

void top(InvIndex inv, char* line){
	char* args[3] = {NULL,NULL, NULL};		/*2 arguments to parse						*/
	char* delim = " ";					/*arguments are seperated by space character*/

	for(int i = 0; i < 3; i++){
		args[i] = strtok(line, delim);	/*Parse data with respect to delim character*/
		line = NULL;
	}
	for(int i = 0; i < 3; i++){
		if( args[i] == NULL){
			red();
			printf("\t - Invalid command format for %s\n", args[0]);
			reset();
			return;
		}
	}
	int counter = atoi(args[1]);
	int tyear = atoi(args[2]);
	if(inv == NULL || inv -> year == -1){
		red();
		printf("\t- No students enrolled in %d\n", tyear);
		reset();
		return;
	}
	
	while(inv != NULL && inv->year <= tyear){
		if(inv -> year == tyear){
			innerlist* temp = inv -> students;
			counter = counter < inv-> size ? counter : inv->size;
			for(int i = 0; i < counter; i++){
				printf("\t - %d\n", temp -> student -> student_id);
				temp = temp -> next;
			}
			return;
		}
		inv = inv -> next;
	}
	red();
	printf("\t- No students enrolled in %d\n", tyear);
	reset();
}

void min(InvIndex inv, char* line){
	char* args[2] = {NULL,NULL};		/*2 arguments to parse						*/
	char* delim = " ";					/*arguments are seperated by space character*/

	for(int i = 0; i < 2; i++){
		args[i] = strtok(line, delim);	/*Parse data with respect to delim character*/
		line = NULL;
	}
	for(int i = 0; i < 2; i++){
		if( args[i] == NULL){
			red();
			printf("\t - Invalid command format for %s\n", args[0]);
			reset();
			return;
		}
	}
	int tyear = atoi(args[1]);
	if(inv == NULL || inv -> year == -1){
		red();
		printf("\t- No students enrolled in %d\n", tyear);
		reset();
		return;
	}
	while(inv != NULL && inv->year <= tyear){
		if(inv -> year == tyear){
			innerlist* start, *end, *iter;
			start = end = inv -> students;
			if(start == NULL) {
				red();
				printf("\t- No students enrolled in %d\n", tyear);
				reset();
				return;
			}
			end = end-> next;
			while(end != NULL){
				if(start -> student -> gpa != end -> student -> gpa){
					start = end;
				}
				end = end -> next;
			}
			for(iter = start; iter != NULL; iter = iter -> next){
				printf("\t- %d\n", iter -> student -> student_id);
			}
			return;
		}
		inv = inv -> next;
	}
	red();
	printf("\t- No students enrolled in %d\n", tyear);
	reset();	
}


/*------------------END OF COMMAND FUNCTIONS------------*/