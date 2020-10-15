#pragma once

#include "Student.h"

/*----------------------START OF inverted index --------------------*/
typedef struct invnode invnode;
typedef struct innerlist innerlist;

struct innerlist
{
	innerlist* next;
	Student student;
};

struct invnode{
	int year;
	int size;
	innerlist* students;
	invnode* next;
};
typedef invnode* InvIndex;

InvIndex invindex_create(void);

innerlist* innerlist_create(Student s);

void invindex_insert(InvIndex inv, Student s);
/*----------------------END OF inverted index --------------------*/