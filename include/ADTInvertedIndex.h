#pragma once

#include "Student.h"

/*----------------------START OF inverted index --------------------*/
typedef struct invnode invnode;
typedef struct innerlist innerlist;

/*Struct of inverted index that descrices a list with students
/ enrolled in specific years*/
struct innerlist
{
	innerlist* next;
	Student student;
};
/*Node of list of years*/
struct invnode{
	int year;
	int size;				/*students enrolled in year*/
	innerlist* students;
	invnode* next;
};
typedef invnode* InvIndex;

InvIndex invindex_create(void);					/*Create invindex and invnode 				*/

innerlist* innerlist_create(Student s);			/*Create innerlist and place student 		*/

void invindex_insert(InvIndex* inv, Student s);	/*Insert in inverted index, in general		*/

void invindex_destroy(InvIndex inv);			/*Free all the allocated memory of inv_index*/
/*----------------------END OF inverted index --------------------*/