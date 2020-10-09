/*Read from input.txt lines, parse data and create students based on them /
/ Addiotionally, create a hashtable to insert the students with respect to/
/ number of lines found in input files and SIZE_FACTOR. 				 */

#include <stdio.h>
#include <stdlib.h>

#include "ADTHashtable.h"
#include "Utils.h"

#define SIZE_FACTOR 1.3	/*Factor that co-defines the size of hash table*/

int main(int argc, char** argv){
	int number_of_lines = line_counter(argv[1]);	/*count the lines of input file*/

	Headhash head = hashtable_create(line_counter(argv[1])*SIZE_FACTOR);	/*Create hashtable*/

	FILE* fp = fopen(argv[1], "r");		/*Open input file to parse it's data*/
	char* line = NULL;					/*Temporary store read string		*/
	size_t size = 0;

	char* args[6];		/*6 arguments to parse						*/
	char* delim = " ";	/*arguments are seperated by space character*/

	for(int i = 0; i < number_of_lines; i++){	/*Get each line of input file*/
		getline(&line, &size, fp);
		for(int j = 0; j <= 5; j++){
			args[j] = strtok(line, delim);
			line = NULL;
		}
		hashtable_insert(student_create(atoi(args[0]), args[1], args[2], atoi(args[3]), atoi(args[4]), atoi(args[5])), head);
	}

	fclose(fp);		/*Close the file and free all associated memory that has been allocated*/
	hashtable_insert(student_create(78, "a","b", 1,4,5), head);
	hashtable_find(88999 , head);
	hashtable_find(78, head);
	return 0;
}