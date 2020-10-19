/*Read from input.txt lines, parse data and create students based on them /
/ Addiotionally, create a hashtable to insert the students with respect to/
/ number of lines found in input files and SIZE_FACTOR. 				 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "ADTHashtable.h"
#include "Utils.h"
#include "ADTInvertedIndex.h"

float parse_config(char* configfile);	/*Parse the config file*/

int main(int argc, char** argv){
	float SIZE_FACTOR = 0.7;						/*Initialize SIZE_FACTOR in case of empty configfile */
	char* input_file = NULL, *config_file = NULL;
	int c;											/*possible Options 									 */
	
	/* -------------Get Optios of Command line--------------*/
	while( (c = getopt(argc,argv,"i:c:")) != -1) {
		switch(c) {
			case 'i':
				input_file = optarg;
				break;
			case 'c':
				config_file = optarg;
				break;
			case '?':
					usage(argv[0]);
					return 1;
		}	
	}
	/*---------------End of Options Parsing----------------*/

	if(!input_file){		/*Check if input file is not given, print error, terminate*/
		usage(argv[0]);
		red();
		printf("Input file is mandatory, none was given\n");
		reset();
		return 1;
	}

	if(config_file){
		float temp_sf = parse_config(config_file);				/*Parse float inside config config_file 				 */
		SIZE_FACTOR = temp_sf <= 0.0 ? SIZE_FACTOR : temp_sf;	/*if configed number is negative, use the default instead*/
	}

	int number_of_lines = line_counter(input_file);			/*count the lines of input file*/

	Headhash head = hashtable_create(line_counter(input_file)*SIZE_FACTOR);	/*Create hashtable 			*/
	InvIndex inv = invindex_create(); 										/*Create inverted index 	*/
	read_and_insert(input_file, number_of_lines, head, &inv);				/*Read file and insert data	*/


	size_t size = 0;		/*size of expected bytes to read, if 0 realloc to suitable size */
	char* line = NULL;		/*pointer to allocated memory for strings						*/
	int kill_switch = 0;	/*flag that kills loop and stops program to stdin				*/
	char* temp = NULL;		/*variable to copy line from Input 								*/

	while(kill_switch != 1){
		printf(">>");
		getline(&line, &size, stdin);	/*Get string from console*/
		trim(line);						/*Replace /n with /0	 */
		temp = strdup(line);
		switch(commandcode(command_string(temp))){
			case kINSERT:
				user_insert(line, head, &inv);
				break;

			case kLOOKUP:
				look_up(line, head);
				break;

			case kDELETE:
				deletion(inv, line);
				break;
			
			case kNUMBER:
				number_year(inv, line);
				break;

			case kTOP:
				top(inv, line);
				break;

			case kAVERAGE:
				average(inv, line);
				break;
			
			case kMINIMUM:
				min(inv, line);
				break;
			
			case kCOUNT:
				year_count(inv, line);
				break;
			
			case kPOSTALCODE:
				postal(inv, line);
				break;

			case kEXIT:
				exiting(head, inv);
				kill_switch = 1;
				break;

			case kFALSECOM:
				break;
		}
		
		free(line);		/*Free memory			*/
		free(temp);		/*allocated from getline*/
		line = NULL;
		size = 0;
	}
	return 0;
}

/*Parse the data inside the config file (1 float)*/
float parse_config(char* configfile) {
	float load_factor;
	FILE* fp = fopen(configfile, "r");
	fscanf(fp, "%f", &load_factor);
	fclose(fp);
	return load_factor;
}