#include <stdlib.h>
#include <string.h>

#include "ADTZipList.h"
#include "ADTInvertedIndex.h"

Ziplist zip_create(){
	Ziplist zip = malloc(sizeof(zipnode));
	zip -> Zip = -1;
	zip -> count = 0;
	zip -> next = NULL;
}

Ziplist zip_insert(InvIndex inv){
	Ziplist Hzip = zip_create();
	Ziplist zip = Hzip;
	innerlist* temp;
	int tzip = 0;

	while(inv != NULL)
	{
		temp = inv -> students;
		while(temp != NULL)
		{
			temp = temp -> next;
		}
		inv = inv -> next;
	}
	return Hzip;
}

void zip_destroy(zipnode* zip){
	zipnode* temp = zip -> next;
	while(temp != NULL){
		free(zip);
		zip = temp;
		temp = temp -> next;
	}
	free(zip);
}

Ziplist rank_zips(Ziplist zip, int num){
	Ziplist* top_zip = malloc(sizeof(**top_zip)*num);
	
	for(int i = 0; i < num + 1; i++){
		top_zip[i] = NULL;
	}
	Ziplist temp;
	int i;
	while(zip != NULL){
		temp = zip -> next;
		for(i = 0; i < num; i++){
			if(top_zip[i] == NULL){
				top_zip[i] = zip;
				zip -> next = NULL;
				break;
			}
			else if(top_zip[i] -> Zip == zip -> Zip){
				zip -> next = top_zip[i];
				top_zip[i] = zip;
			}
			else if(zip -> Zip < top_zip[i] -> Zip){
				Ziplist temp2 = top_zip[num - 1];
				memcpy(&top_zip[i+1], &top_zip[i], num-i-1); // shift i slots
				zip -> next = NULL;
				if(temp2 != NULL){
					zip_destroy(temp2);
				}
				break;
			}
		}
		if(i >= num){
			zip_destroy(zip);
		}
		zip = temp;
	}
	for(i = 0; i < num - 1; i++){
		zip_destroy(top_zip[i]);
	}
	Ziplist answer = top_zip[num - 1];
	free(top_zip);

	return answer;
}
/*------------------End of Post Command-----------------*/
