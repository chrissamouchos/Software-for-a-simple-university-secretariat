/*-----------------------------------------------------------
/	Implementation of basic Data Structures that are needed	/
/	in project. Here are only the function prototypes and	/
/	neccessary structs and data types						/
------------------------------------------------------------*/

#pragma once			/*During compilation, include this file only once*/

#include <string.h>
#include "Student.h"



/*----------------------START OF Hash table ---------------------*/
typedef struct hashnode hashnode;

struct hashnode{
	Student value;
	hashnode* next;
};

typedef struct{
	hashnode* array;	/*Array of pointer to Student lists	*/
	int size;			/*how big is Array 					*/
}hashinfo;

typedef hashinfo* Headhash;							/*Element that gives access to hashtable*/

Headhash hashtable_create(int n);					/*Creates hashtable of n elemets*/

void hashtable_destroy(Headhash head); 				/*Free all allocated memory of hash table*/

int hashtable_insert(Student s, Headhash head);		/*Insert new Student to hashtable*/

Student hashtable_find(int student_id, Headhash head);	/*Search for student, if not found print error!*/
/*----------------------END OF Hash table -----------------------*/

int hashfunc(int student_id, Headhash head);	/*Function for hashing keys of hashtable*/