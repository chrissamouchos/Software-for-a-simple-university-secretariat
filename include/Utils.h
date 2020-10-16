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
	kFALSECOM = -1
};

int commandcode(char* line);

char* command_string(char* line);

void exiting(Headhash head);

void user_insert(char* line, Headhash head, InvIndex inv);

void look_up(char* line, Headhash head);

void number_year(InvIndex inv, char* line);

void year_count(InvIndex inv, char* line);

void average(InvIndex inv, char* line);
/*------------------END OF COMMANDS---------------------*/