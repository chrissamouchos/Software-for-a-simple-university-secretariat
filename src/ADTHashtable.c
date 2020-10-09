/*-----------------------------------------------
/	Implementation of custom library and custom	/
/	data types, source code of include file		/ 
/----------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include "ADTHashtable.h"
#include "Student.h"
#include "Utils.h"

#define TEMP_SIZE 10

/*-------------- START OF HASHTABLE -----------------*/
Headhash hashtable_create(int n){
	Headhash head = malloc(sizeof(hashinfo));
	head -> array = malloc(sizeof(hashnode)*n);
	head -> size = n;
	head -> capacity = 0;
	Headhash temp = head;
	for(int i = 0; i < n; i++){
		temp -> array[i].key = NULL;
		temp -> array[i].value = NULL;
		temp -> array[i].next = NULL;
	}
	return head;
}

int hashfunc(int student_id, Headhash head){
	return student_id % (head -> size);
}

void hashtable_insert(Student s, Headhash head){

	/*--------Check if student already exists------------*/
	Student check = hashtable_find(get_student_id(s), head);
	if(check != NULL){
		red();
		printf("ERROR: Student aldready exists!\n");
		reset();
		return;
	}
	
	head -> capacity++;
	int hash_key = hashfunc(get_student_id(s), head);
	if(head -> array[hash_key].next == NULL){
		head -> array[hash_key].key = &(s -> student_id);
		head -> array[hash_key].value = s;
	}
	else{
		hashnode* temp = head -> array[hash_key].next;
		while(temp != NULL){
			temp = temp -> next;
		}
		temp -> next -> key = &(s -> student_id);
		temp -> next -> value = s;
		temp -> next -> next = NULL;
	}	
}

Student hashtable_find(int student_id, Headhash head){
	int hash_key = hashfunc(student_id, head);
	if(head -> array[hash_key].key == NULL){
		red();
		printf("ERROR: Student not found!\n");
		reset();
		return NULL;
	}
	hashnode* iter = &(head -> array[hash_key]);
	while(iter){
		if(*(iter->key) == student_id)
		{
			green();
			printf("Student found!\n");
			reset();
			return iter->value;
		}
		iter = iter->next;
	}

	red();
	printf("ERROR: Student not found!\n");
	reset();
	return NULL;
}

void hashtable_destroy(Headhash head){
	printf("\n");
}
/*------------ END OF HASHTABLE ------------------*/