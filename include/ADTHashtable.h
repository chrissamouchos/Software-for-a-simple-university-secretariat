/*-----------------------------------------------------------
/	Implementation of basic Data Structures that are needed	/
/	in project. Here are only the function prototypes and	/
/	neccessary structs and data types of hashtable 			/
/ 	Implementation.											/
-----------------------------------------------------------*/

#pragma once			/*During compilation, include this file only once*/

#include <string.h>
#include "Student.h"

/*----------------------START OF Hash table --------------------*/
typedef struct hashnode hashnode;	/*Define struct as data type*/

struct hashnode{	/*Struct that is contained in each slot of */
	Student value;	/* hashtable. It contains a pointer to the */
	hashnode* next;	/*stored student and pointer to implement  */
};					/* seperate chaining					   */


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