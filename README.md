# Software-for-a-simple-university-secretariat
A C programm that uses efficient ways to store data of students for quick data querries.

The object that represents the students is called Student and it is implemented as a struct with values that fully decribe the student's identity (id, zip, year of study, gpa, last and first name). I try to maximize data abstraction in order to protect the user from changing the functionality of the programm by mistake.
## Data structure
For the implementation of this basic api, i used two main data structures.
- a hash table
- an inverted index

###### The hash table
This data structure is responsible of decreasing the complexity of insertion, searching and deletion of data to O(1). The model that is being used is that of separate chaining. The hash table is being handled with a pointer to it's wrapper, that points to hashtable which contains Student objects. The **hash function** is defined, as the module operation of the student_id (primary key) with the size of the hash_table(dynamically allocation of memory, by counting lines of input files, with respect to configured load factor). If hash_key index of an object is the same with that of an existing one, then i create a simple linked list of Students in order to insert the object. Searching has the same logic as insertion.

###### The Inverted Index
Inverted Index is a simple linked list that stores pointers to Student objects that are already inside the hashtable. However, this data structure is sorted based on the year of study. This is used for the various functions that are implemented.

## Compile, Run and User Interface
