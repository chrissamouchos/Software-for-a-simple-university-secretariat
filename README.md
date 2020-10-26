# Software-for-a-simple-university-secretariat
A C programm that uses efficient ways to store data of students for quick data querries, while using a simple command promt for interaction with the user.

The object that represents the students is called Student and it is implemented as a struct with values that fully decribe the student's identity (id, zip, year of study, gpa, last and first name). I try to maximize data abstraction in order to protect the user from changing the functionality of the programm by mistake.
## Data structure
For the implementation of this basic api, i used two main data structures.
- a hash table
- an inverted index

#### The hash table
This data structure is responsible of decreasing the complexity of insertion, searching and deletion of data to O(1). The model that is being used is that of separate chaining. The hash table is being handled with a pointer to it's wrapper, that points to hashtable which contains Student objects. The **hash function** is defined, as the module operation of the student_id (primary key) with the size of the hash_table(dynamically allocation of memory, by counting lines of input files, with respect to configured load factor). If hash_key index of an object is the same with that of an existing one, then i create a simple linked list of Students in order to insert the object. Searching has the same logic as insertion.

#### The Inverted Index
Inverted Index is a simple linked list that stores pointers to Student objects that are already inside the hashtable. However, this data structure is sorted based on the year of study. This is used for the various functions that are implemented.

## Compile, Run and User Interface
The makefile provides several options to the user. In bin directory are all the .o files, in include directory, all the header files, in src directory, all the source files of the headers and main function. All make commands should me called in the main directory. In Input directory are included some test input for the application. It is important to mention that the input should follow strictly the format file that is given by the example files. Config file contains the load factor parameter and can be changed by the user.
-make build: compile the program
-make run1: run the program with input file 1
-make run2: run the program with input file 2
-make svalgrind: check for memory leaks for file 1
-make fvalgrind: check for memory leaks with a full analysis
-make profiling: can be called **only after run** and produces a gmon.out file. Afterwards the gprof uses that file to create the file analysis.txt that contains full information about function calls and time needed. Also, the results are printed in the screen automatically.

##Commands

The implemented command that the user can call are(either by entering the full string or by just typing the first letter):
```
void exiting(Headhash head, InvIndex inv);		/*Exit the program and free all allocate memory	*/

void user_insert(char* line, Headhash head, InvIndex* inv);	/*Insert manually via console new Student object*/

void look_up(char* line, Headhash head);	/*Search Student with id, print its values		*/

void number_year(InvIndex inv, char* line);	/*Print all student_ids of given year 			*/

void year_count(InvIndex inv, char* line);	/*Print number of students of given year 		*/

void average(InvIndex inv, char* line);		/*Compute and print average gpa given the year 	*/

void top(InvIndex inv, char* line);			/*Find and print best num students given the year*/

void min(InvIndex inv, char* line);			/*Print student with minimum gpa given the year */

void postal(InvIndex inv, char* line);		/*Print rank of num-th most common zips 		*/

void deletion(InvIndex inv, char* line);	/*Delete a student 								*/
```
*Note: deletion is to be implemented*