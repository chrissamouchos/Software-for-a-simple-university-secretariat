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
	Headhash temp = head;
	for(int i = 0; i < n; i++){
		temp -> array[i].value = NULL;
		temp -> array[i].next = NULL;
	}
	return head;
}

int hashfunc(int student_id, Headhash head){
	return student_id % (head -> size);
}

int hashtable_insert(Student s, Headhash head){

	/*--------Check if student already exists------------*/
	int hash_key = hashfunc(get_student_id(s), head);
	if(head -> array[hash_key].value == NULL){
		head -> array[hash_key].value = s;
	}
	else{
		hashnode* temp = &(head -> array[hash_key]);
		while(temp -> next != NULL){
			if(get_student_id(temp -> value) == get_student_id(s))	return 1;	/*Already exists*/
			temp = temp -> next;
		}
		if(get_student_id(temp -> value) == get_student_id(s))	return 1;	/*Already exists*/
		temp -> next = malloc(sizeof(hashnode));
		temp -> next -> value = s;
		temp -> next -> next = NULL;
	}
	return 0;	/*Inserted normally*/
}

Student hashtable_find(int student_id, Headhash head){
	int hash_key = hashfunc(student_id, head);
	if(head -> array[hash_key].value == NULL){
		red();
		printf("ERROR: Student not found!\n");
		reset();
		return NULL;
	}
	hashnode* iter = &(head -> array[hash_key]);
	while(iter){
		if(get_student_id(iter -> value) == student_id)
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
	int counter = head -> size;
	hashnode* temp, *next;
	for(int i = 0; i < counter; i++){
		temp = &(head -> array[i]);
		if(temp -> value != NULL){
			student_destroy(temp -> value);
		}
		temp = temp -> next;
		while(temp != NULL){
			next = temp -> next;
			student_destroy(temp -> value);
			free(temp);
			temp = next;
		}
	}
	free(head -> array);
	free(head);
}
/*------------ END OF HASHTABLE ------------------*/