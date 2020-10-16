/*Read from input.txt lines, parse data and create students based on them /
/ Addiotionally, create a hashtable to insert the students with respect to/
/ number of lines found in input files and SIZE_FACTOR. 				 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "ADTHashtable.h"
#include "Utils.h"
#include "ADTInvertedIndex.h"

#define SIZE_FACTOR 0.7 /*Factor that co-defines the size of hash table*/

int main(int argc, char** argv){

	char* input_file = NULL, *config_file = NULL;
	int c;
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

	int number_of_lines = line_counter(input_file);	/*count the lines of input file*/

	Headhash head = hashtable_create(line_counter(input_file)*SIZE_FACTOR);	/*Create hashtable 			*/
	InvIndex inv = invindex_create(); 										/*Create inverted index 	*/
	read_and_insert(input_file, number_of_lines, head, inv);				/*Read file and insert data	*/


	size_t size = 0;	/*size of expected bytes to read, if 0 realloc to suitable size */
	char* line = NULL;	/*pointer to allocated memory for strings						*/
	int kill_switch = 0;
	
	while(kill_switch != 1){
		printf(">>");
		getline(&line, &size, stdin);
		trim(line);
		switch(commandcode(line)){
			case kINSERT:
		
			case kLOOKUP:
		
			case kDELETE:
			
			case kNUMBER:
			
			case kTOP:
			
			case kAVERAGE:
			
			case kMINIMUM:
			
			case kCOUNT:
			
			case kPOSTALCODE:

			case kEXIT:
				exiting(head);
				kill_switch = 1;
				break;

			case kFALSECOM:
				break;
		}
		
		free(line);
		line = NULL;
		size = 0;
	}
	
	// Student s = student_create(1 , "d", "a", 2, 1998, 123);
	// Headhash head = hashtable_create(10);
	// InvIndex  inv = invindex_create();
	// hashtable_insert(s, head);
	// invindex_insert(inv, s);

	return 0;
}