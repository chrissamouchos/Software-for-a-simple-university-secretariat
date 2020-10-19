#include <stdlib.h>

#include "ADTInvertedIndex.h"
#include "Student.h"

InvIndex invindex_create(void){
	InvIndex inv = malloc(sizeof(*inv)); /*Create an invnode 		*/
	inv -> year = -1;					 /*When no students are enrolled, -1 as flag	*/
	inv -> size = 0;
	inv -> students = NULL;
	inv -> next = NULL;

	return inv;
}

innerlist* innerlist_create(Student s){
	innerlist* temp = malloc(sizeof(*temp));	/*Create innerlist node*/
	temp -> next = NULL;
	temp -> student = s;

	return temp;
}

/*Insert in SORTED inner - list with respect to student_gpa*/
void innerlist_insert(innerlist** list, Student s){
	innerlist* temp = *list;	/*Create copy of pointer because *list is passed by reference*/
	if(*list == NULL){			/*If no student is enrolled									 */
		*list = innerlist_create(s);
		(*list) -> next = temp;
	}
	else if( (*list) -> student -> gpa < s -> gpa){	/*if we want to enroll in top of inner list*/
		temp = innerlist_create(s);
		temp -> next = *list;
		*list = temp;
	}
	else{	/*any other case*/
		innerlist* prev = temp;
		temp = temp -> next;
		while(temp != NULL && temp -> student -> gpa > s -> gpa){
			prev = temp;
			temp = temp -> next;
		}
		prev -> next = innerlist_create(s);
		prev -> next -> next = temp;
	}
}

/*Insert in SORTED inner - list with respect to year*/
void invindex_insert(InvIndex* ihead, Student s){
	InvIndex prev, inv = *ihead;
	if(	((inv -> students == NULL) && (inv -> next == NULL)) || inv -> year == s -> year){	/*List is empty or we want to enroll in first node*/
		inv -> year = s -> year;
		inv -> size++;
		innerlist_insert(&(inv -> students), s);
	}
	else if(s -> year < inv -> year){	/*we need to add invnode as the head of the list*/
		prev = inv;
		inv = invindex_create();
		inv -> year = s -> year;
		inv -> size++;
		inv -> next = prev;
		innerlist_insert(&(inv -> students), s);	/*enroll to new invnode			*/
		*ihead = inv;
	}
	else{
		prev = inv;
		inv = prev -> next;
		while(inv != NULL){
			if(inv->year == s->year){
				inv -> size++;
				innerlist_insert(&(inv -> students),s);
				return;
			}
			else if(inv -> year > s -> year ){
				prev -> next = invindex_create();
				prev -> next -> year = s -> year;
				prev -> next -> size++;
				innerlist_insert(&(prev -> next -> students), s);
				prev -> next -> next = inv;
				return;
			}
			prev = inv;
			inv = inv -> next;
		}
		inv = invindex_create();
		inv -> year = s -> year;
		inv -> size++;
		prev -> next = inv;
		innerlist_insert(&(inv -> students), s);
	}
}



void invindex_destroy(InvIndex inv){
	InvIndex big_list_iter = inv;
	innerlist* small_list_iter = inv -> students;
	int count = 0;

	while(big_list_iter != NULL){
		innerlist* temp;
		small_list_iter = big_list_iter -> students;
		while(small_list_iter != NULL){

			temp = small_list_iter -> next;
			free(small_list_iter);
			count++;
			small_list_iter = temp;
		}
		
		inv = big_list_iter -> next;
		free(big_list_iter);
		big_list_iter = inv;
	}
}