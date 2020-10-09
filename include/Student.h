#pragma once

/*----------------------START OF STUDENT ΕΝΤΙΤΥ---------------------*/
typedef struct{
	int 	student_id;
	char* 	last_name;
	char* 	first_name;
	int 	zip;
	int 	year;
	float 	gpa;
}student;

typedef student* Student;

Student student_create(int student_id, char* first_name, char* last_name, int zip, int year, int gpa);	/*Allocate memory for student*/

void print_name(Student s);			/*print "fist name last name"			*/

void student_destroy(Student s);	/*free all allocated memory of student 	*/

int get_student_id(Student s);		/*returns the student_id of s item		*/
/*----------------------END OF STUDENT ΕΝΤΙΤΥ--------------------*/