/*File that contains function source code related to student object*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h> // use of strdup

#include "Student.h"

/*----------------- START OF STUDENT--------------------*/
Student student_create(int student_id, char* first_name, char* last_name, int zip, int year, int gpa){
	Student student = malloc(sizeof(*student));		/*Allocate memory for a student object*/
	student -> student_id = student_id;
	student -> last_name = strdup(last_name);		/*Copy name to student field*/
	student -> first_name = strdup(first_name);
	student -> zip = zip;
	student -> year = year;
	student -> gpa = gpa;

	return student;
}

void student_destroy(Student s){
	free(s -> last_name);
	free(s -> first_name);
	free(s);
}

void print_name(Student s){
	printf("%s %s", s->first_name, s->last_name);
}

int get_student_id(Student s){
	return s -> student_id;
}
/*-------------- END OF STUDENT ---------------------*/