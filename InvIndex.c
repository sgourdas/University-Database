#include "Functions.h"


InvIndex IIndexCreate(void) {	// Create an inverted index struct
	// Allocate memory needed for this
	InvIndex inv = (InvIndex) malloc(sizeof(DummyNode));
	// Assign null values to all fields
	inv->year = 0;
	inv->count = 0;
	inv->link = NULL;
	inv->list = NULL;

	return inv;

}

void IIInsert(InvIndex inv, Student node) {	// Insert a value to the inverted index

	InvIndex index = inv, temp;
	int currYear = getYear();	// Get the current year needed for getting a students year of study

	if(index->count == 0) {	// Check if this is the first Insert
		// Field completion
		index->year = currYear - node->year + 1;
		index->count++;
		index->list = LCreate(node);
		return;

	}

	do {	// Cycle through the links to find the dummy node with the year we are searching for

		temp = index; 
		
		if(index->year == currYear - node->year + 1) {	// Found the correct year on the dummy nodes
			// Update info
			index->count++;
			LInsert(index->list, node);
			return;

		}
		// Next dummy node
		index = index->link;

	} while(index != NULL);
	// If we have reached the end without finding a dummy node with the correct year, that means we have to make a new entry
	temp->link = IIndexCreate();
	temp->link->count++;
	temp->link->year = currYear - node->year + 1;
	temp->link->list = LCreate(node);

}

int IIRemove(InvIndex *inv, char *id, int year) {	// Remove an entry from the index
	// Convert year of sign up to year of studies
	year = getYear() - year + 1;

	InvIndex temp = *inv, backup = *inv;
	// Cycle through all dummy nodes
	while(temp->year != year) {

		backup = temp;
		temp = backup->link;	// temp = temp->link; is prettier -- used backup->link here to remove -Wunused-but-set-variable :)
		// If we reach the end there is no such entry
		if(temp == NULL)
			return -1;

	}

	temp->count--;	// Decrement student in year counter
	// Remove item from the list of the inverted index dummmy
	int res = LRemove(temp->list, id, &backup->link);

	if(temp->count == 0)	{	// If all students are removed from a year delete the invindex node
	
		backup->link = temp->link;
		free(temp);

	}
	
	return res;

}

int IINum(InvIndex inv, int year) {		// Find the number of students in year

	InvIndex temp = inv;
	// Cycle through years till we find the right one
	while(temp->year != year) {

		if(temp->link == NULL)	// End of list -- no entry
			return -1;
		
		temp = temp->link;
	
	}
	// We have found the correct year so we return the dummy node counter
	return temp->count;

}

IDList IITop(InvIndex inv, int size, int year) {	// Get a list of the students with the best GPA in 'year' year of study

	InvIndex temp = inv;
	// Cycle through years
	while(temp->year != year)	
		if((temp = temp->link) == NULL)	// if we have reached the end and the while has not finished -> no such entry here
			return NULL;

	// If the size exceeds the student entries, cap it at the 'counter' value
	if(size > temp->count)
		return LTop(temp->list, temp->count);
	else
		return LTop(temp->list, size);

}

float IIAverage(InvIndex inv, int year) {	// Find the average GPA for students in 'year' year of study
	
	if(inv == NULL)	// If no insertions have been made
		return -1;

	InvIndex temp = inv;
	// Cycle through years
	while(temp->year != year) {

		temp = temp->link;
		// End of list with no success :(
		if(temp == NULL)
			return -1;

	}
	// Get the average for this 'list'
	return LAverage(temp->list);

}

IDList IIMinimum(InvIndex inv, int year) {	// Get the list of students with the min GPA for 'year' year of study

	InvIndex temp = inv;
	// Cycle through years
	while(temp->year != year) {
		// Reached the end
		if(temp->link == NULL)
			return NULL;

		temp = temp->link;

	}
	// Pass this 'list' for searching in
	return LMinimum(temp->list);

}

YList IICount(InvIndex inv) {	// Get the number of students for each year of study
	// If the count of the first node is 0 we have no entries
	if(inv->count == 0)
		return NULL;

	InvIndex temp = inv;
	// Create the list that we will return
	YList list = YLCreate(inv->year, inv->count);
	// From the next node on
	while((temp = temp->link) != NULL)
		YLInsert(list, temp->year, temp->count);	// Insert values to list

	return list;

}

void IIDestroy(InvIndex inv) {	// Free all memory used by the inverted index
	// Destroy all	dummy nodes recursively
	if(inv != NULL && inv->link != NULL)
		IIDestroy(inv->link);
	// Destroy the list
	if(inv != NULL && inv->list != NULL)
		LDestroy(inv->list);
	// Free current node space
	if(inv != NULL)
		free(inv);

}

int getYear() {
		// Idea from "https://stackoverflow.com/questions/1442116/how-to-get-the-date-and-time-values-in-a-c-program"
        time_t t = time(NULL);
  		struct tm tm = *localtime(&t);
  		return tm.tm_year + 1900;

}