/*File that contains the prototypes of various functions*/
#pragma once	/*Include only once*/

#include "ADTHashtable.h"
#include "ADTInvertedIndex.h"

/*----------------- VARIOUS FUNCTIONS-------------------*/
void red();		/*Chane printing color to red 	*/

void green();	/*Chane printing color to green	*/

void cyan();	/*Chane printing color to cyan	*/

void reset();	/*Reset color to default		*/

int line_counter(char* input);	/*Count the lines of input file*/

void read_and_insert(char* input, int number_of_lines, Headhash head, InvIndex inv);	/*Read file and insert parsed data*/

void usage(const char* command);	/*Print expected format*/

void trim(char* line);
/*----------------- END OF FUNCTIONS--------------------*/

/*------------------START OF COMMANDS-------------------*/
/*Array to store all the expected commands*/
static char* commands[10] = {
	"insert",
	"look-up",
	"delete",
	"number",
	"top",
	"average",
	"minimum",
	"count",
	"postal code",
	"exit"
};

/*Enum commands to correspond them with proper operation code*/
enum COMMANDS
{
	kINSERT = 0,
	kLOOKUP,
	kDELETE,
	kNUMBER,
	kTOP,
	kAVERAGE,
	kMINIMUM,
	kCOUNT,
	kPOSTALCODE,
	kEXIT,
	kCOMSNUM,
	kFALSECOM = -1	/*Wrong input*/
};

int commandcode(char* line);		/*Get op code for given string 					*/

char* command_string(char* line);	/*From given string get string command 			*/

void exiting(Headhash head);		/*Exit the program and free all allocate memory	*/

void user_insert(char* line, Headhash head, InvIndex inv);	/*Insert manually via console new Student object*/

void look_up(char* line, Headhash head);	/*Search Student with id, print its values		*/

void number_year(InvIndex inv, char* line);	/*Print all student_ids of given year 			*/

void year_count(InvIndex inv, char* line);	/*Print number of students of given year 		*/

void average(InvIndex inv, char* line);		/*Compute and print average gpa given the year 	*/

void top(InvIndex inv, char* line);			/*Find and print best num students given the year*/

void min(InvIndex inv, char* line);			/*Print student with minimum gpa given the year */
/*------------------END OF COMMANDS---------------------*/