#include <stdlib.h>

#include "ADTInvertedIndex.h"
#include "Student.h"

InvIndex invindex_create(void){
	InvIndex inv = malloc(sizeof(*inv));
	inv -> year = -1;
	inv -> size = 0;
	inv -> students = NULL;
	inv -> next = NULL;

	return inv;
}

innerlist* innerlist_create(Student s){
	innerlist* temp = malloc(sizeof(*temp));
	temp -> next = NULL;
	temp -> student = s;

	return temp;
}

void innerlist_insert(innerlist** list, Student s){
	innerlist* temp = *list;
	*list = innerlist_create(s);
	(*list) -> next = temp;
}

void invindex_insert(InvIndex inv, Student s){
	InvIndex prev;
	if(	((inv -> students == NULL) && (inv -> next == NULL)) || inv -> year == s -> year){
		inv -> year = s -> year;
		inv -> size++;
		innerlist_insert(&(inv -> students),s);
	}
	else if(s -> year < inv -> year){
		prev = inv;
		inv = invindex_create();
		inv -> year = s -> year;
		inv -> size++;
		innerlist_insert(&(inv -> students), s);
	}
	else{
		prev = inv;
		inv = prev -> next;
		while(inv != NULL){
			if(inv->year == s->year){
				inv -> size++;
				innerlist_insert(&(inv -> students),s);
				break;
			}
			else if(inv -> year > s -> year ){
				prev -> next = invindex_create();
				prev -> next -> year = s -> year;
				prev -> next -> size++;
				innerlist_insert(&(prev -> next -> students), s);
				prev -> next -> next = inv;
				break;
			}
			prev = inv;
			inv = inv -> next;
		}
	}
}