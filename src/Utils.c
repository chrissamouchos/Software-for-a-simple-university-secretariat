#include <stdio.h>
#include "Utils.h"

/*----------------- VARIOUS FUNCTIONS-------------------*/
void red(){
 	printf("\033[1;31m");
}

void green(){
	printf("\033[1;32m");
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
/*----------------- END OF FUNCTIONS--------------------*/