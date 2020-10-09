/*-----------------------------------------------
/	Implementation of custom library and custom	/
/	data types, source code of include file		/ 
/----------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>

#include "ADTHashtable.h"
#include "Student.h"
#include "Utils.h"

/*-------------- START OF HASHTABLE -----------------*/
Headhash hashtable_create(int n){
	Headhash head = malloc(sizeof(hashinfo));	/*Allocate memory for hashinfo, that contains the pointer to main array	*/
	head -> array = malloc(sizeof(hashnode)*n);	/*Allocate memory for n slots of hashnodes inside main array			*/
	head -> size = n;
	/*-----Initialize all pointers to NULL------*/
	Headhash temp = head;
	for(int i = 0; i < n; i++){
		temp -> array[i].value = NULL;
		temp -> array[i].next = NULL;
	}
	return head;
}

int hashfunc(int student_id, Headhash head){	/*hash index = key % size*/
	return student_id % (head -> size);
}

int hashtable_insert(Student s, Headhash head){	/*Returns 0 in normal insertion, 1 if node already exists*/
	/*--------Check if student already exists------------*/
	int hash_key = hashfunc(get_student_id(s), head);	/*Calculate hash key */
	if(head -> array[hash_key].value == NULL){			/*If head of list in desired insex is empty, then insert*/
		head -> array[hash_key].value = s;
	}
	else{
		hashnode* temp = &(head -> array[hash_key]);	/*Traverse the list till its end, then insert*/
		while(temp -> next != NULL){
			if(get_student_id(temp -> value) == get_student_id(s))	return 1;	/*Already exists*/
			temp = temp -> next;
		}
		if(get_student_id(temp -> value) == get_student_id(s))	return 1;	/*Already exists*/
		temp -> next = malloc(sizeof(hashnode));	/*Allocate memory for new node*/
		temp -> next -> value = s;
		temp -> next -> next = NULL;
	}
	return 0;	/*Inserted normally*/
}

Student hashtable_find(int student_id, Headhash head){	/*Search Student object respecting id, if not found, return NULL*/
	int hash_key = hashfunc(student_id, head);			/*Calculate hash key for hash index								*/
	if(head -> array[hash_key].value == NULL){			/*Two stages													*/
		red();
		printf("ERROR: Student not found!\n");	/*If nothing exists in this hash index, return NULL*/
		reset();
		return NULL;
	}
	hashnode* iter = &(head -> array[hash_key]);	/*Search all list*/
	while(iter){
		if(get_student_id(iter -> value) == student_id)
		{
			green();
			printf("Student found!\n");
			reset();
			return iter->value;	/*Found, return pointer to desired object*/
		}
		iter = iter->next;
	}

	red();
	printf("ERROR: Student not found!\n");	/*If all list is traversed, then object is not found, return NULL*/
	reset();
	return NULL;
}

void hashtable_destroy(Headhash head){		/*Frees all allocated memory of hashtable in stages	*/
	int counter = head -> size;				/*Get table size 									*/
	hashnode* temp, *next;
	for(int i = 0; i < counter; i++){		/*Whenever an object is found, destroy it 			*/
		temp = &(head -> array[i]);			/*temp is pointer to array index					*/
		if(temp -> value != NULL){
			student_destroy(temp -> value);	/*Edge case of first element in list				*/
		}
		temp = temp -> next;
		while(temp != NULL){				/*Traverse all list while destroying student objects*/
			next = temp -> next;
			student_destroy(temp -> value);
			free(temp);
			temp = next;
		}
	}
	free(head -> array);	/*Free pointer to hasnodes array, hashinfo	*/
	free(head);				/*Free pointer to hashtable 				*/
}
/*------------ END OF HASHTABLE ------------------*/