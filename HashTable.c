#include "Functions.h"


int h(char *str) {	// Hash function for generating number from string -- taken from an old project

	int h = 0, a = 33;

	for (; *str != '\0' ; str++)
		h = (a*h + *str) % TABLESIZE;

	return h;

}

HashTable HTCreate(int size) {	// Create a hash table structure
	// Allocate space needed
	HashTable new_table = (HashTable) malloc(size * sizeof(HashNode));
	// Init data member values
	for(int i = 0 ; i < TABLESIZE ; i++) {

		new_table[i] = (HashNode) malloc(sizeof(HashNodeType));
		new_table[i]->content = NULL;
		new_table[i]->link = NULL;

	}

	return new_table;

}

Student HTInsert(HashTable table, char *id, char *ln, char *fn, char *zip, int year, float gpa) {	// Insert data to the hash table
	// Create Student struct
	Student info = StudentCreate(id, ln, fn, zip, year, gpa);
	// Go to the correct hash table index 
	HashNode index = table[h(info->studentID)];

	if(index->content == NULL) {	//If there is nothing in this index of the hash add the new one
			
		index->content = info;

	} else {

		HashNode tmp = index;	// Used for linking

		while((index = index->link) != NULL)	// Reach the end of the list
			tmp = index;	// For going back if we reach the end
		
		if(index == NULL) {		// Add the node to the end of the index list

			HashNode new_node = (HashNode) malloc(sizeof(HashNodeType));
			new_node->content = info;
			new_node->link = NULL;
			tmp->link = new_node;

		}

	}

	return info;	

}

Student HTGet(HashTable table, char *id) {		// Used to lookup a student based on id

	HashNode index = table[h(id)];

	if(index->content == NULL)	// Return NULL if there is no entry
		return NULL;

	while(strcmp(index->content->studentID, id) && (index != NULL))	{ // Parse the system until we find a match
		
		index = index->link;

		if(!index)	// If index has reached the end (NULL)
			return NULL;

	}

	return index->content;

}

int HTRemove(HashTable table, char *id) {	// Remove student with 'id' id from the hash table

	HashNode index = table[h(id)], backup = index;

	while(strcmp(index->content->studentID, id)) {	// Parse the list untill we find a match

		backup = index;
		index = index->link;

		if(!index)	// If index has reached the end (NULL)
			return -1;
	
	}

	backup->link = index->link;		// Fill the gap created
	StudentDestroy(index->content);	// Free info space
	free(index);

	return 0;

}

void HTDestroy(HashTable table) {	// Frees space of a hash table
	// Call HashNodeDestroy for every table index
	for(int i = 0 ; i < TABLESIZE ; i++)
		NodeDestroy(table[i]);
	// Free table space
	if(table != NULL)
		free(table);

}

void NodeDestroy(HashNode node) {	// A function that destroyes nodes
	// Destroy the info portion
	if(node->content != NULL)
		StudentDestroy(node->content);
	// Destroy chain recursively
	if(node->link != NULL)
		NodeDestroy(node->link);
	// Free the space of current node
	free(node);

}

Student StudentCreate(char *id, char *ln, char *fn, char *zip, int year, float gpa) {	// Creates Student struct
	// Allocate space and copy values
	Student info = (Student) malloc(sizeof(inf));
	info->studentID = malloc(strlen(id) + 1);
	strcpy(info->studentID, id);
	info->lastName = malloc(strlen(ln) + 1);
	strcpy(info->lastName, ln);
	info->firstName = malloc(strlen(fn) + 1);
	strcpy(info->firstName, fn);
	info->zip = malloc(strlen(zip) + 1);
	strcpy(info->zip, zip);
	info->year = year;
	info->GPA = gpa;

	return info;

}

void StudentDestroy(Student info) {
	// Free all space aquired from heap
	if(info != NULL)
	free(info->studentID);
	free(info->lastName);
	free(info->firstName);
	free(info->zip);
	free(info);

}