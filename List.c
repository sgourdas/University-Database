#include "Functions.h"
//#include <math.h>

List LCreate(Student student) {	// Create a list used in the inverted index's dummy nodes
	// Allocate space and init values
	List l = (List) malloc(sizeof(ListNode));
	l->student = student;
	l->link = NULL;

	return l;

}

void LInsert(List list, Student student) {	// Insert a 'Student' node to the list

	// Allocate space
	List l = (List) malloc(sizeof(ListNode));
	l->student = student;
	l->link = list->link;
	// Linking
	list->link = l;

}

int LRemove(List l, char *id, InvIndex *inv) { // Remove the node with the correct 'id'
	
	if(!strcmp(l->student->studentID, id)) {
		// if the first node of the list needs to be removed, we correctly link the inv pointer from the upper level
		// We do not need StudentDestroy(l->student), because it will be done on HTRemove()
		if((*inv) != NULL)
			(*inv)->list = l->link;
		free(l);

		return 0;

	}

	List temp = l->link, backup = l;
	// Cycle all list nodes
	while(temp != NULL) {

		if(!strcmp(temp->student->studentID, id)) {	// ID matching
			// We do not need StudentDestroy(temp->student), because it will be done on HTRemove()
			backup->link = temp->link;	// Link the gap that will be created
			free(temp);		// Free space allocated for this node
			return 0;
		
		}

		backup = temp;
		temp = temp->link;

	}

	return -1;

}

IDList LTop(List l, int size) {

	IDList final;
	int flag = 1;
	// Create an identical list
	List li = LCreate(l->student), temp = l;

	while((temp = temp->link) != NULL)
		LInsert(li, temp->student);

	// Hold the start of the list in an InvIndex -- used also for LRemove
	InvIndex start = (InvIndex) malloc(sizeof(DummyNode));
	start->list = li;
	// Make a pivot to set as initial value
	Student pivot = (Student) malloc(sizeof(inf)), max;
	pivot->GPA = -1;

	for(int i = 0 ; i < size ; i++) {	// Search in the "li" list, for size times -- as many as the items we want to get

		max = pivot;		// Set the max as the pivot
		temp = start->list;	// Start of the indentical list

		while(temp != NULL) {	// Parse the remaining items

			if(temp->student->GPA > max->GPA)		// Find the largest
				max = temp->student;

			temp = temp->link;

		}
		// Add to final output list
		if(flag == 1) {	// If flag is raised we have not yet started added items so create a list and start adding

			final = IDLCreate(max->studentID);
			flag = 0;
		
		} else {

			IDLInsert(final, max->studentID);

		}

		if(i != size - 1)	// Remove the entry that we just added to the final list from the search list
			LRemove(start->list, max->studentID, &start);

	}
	// Free remaining space
	LDestroy(start->list);
	free(start);
	free(pivot);

	return final;

}

float LAverage(List l) {	// Return average GPA value of a list

	List temp = l;
	float average = 0;
	int counter = 0;
	// Cycle all nodes -- keep sum and count
	while(temp != NULL) {
		
		average += temp->student->GPA;
		counter++;
		temp = temp->link;

	}

	return average / counter;

}

IDList LMinimum(List l) {

	float tempGPA, minGPA;
	Student min = l->student;
	List temp = l->link;
	// Cycle through all nodes
	while(temp != NULL) {

		if(temp->student->GPA < min->GPA)	// Find the student node with the minimum GPA in the list
			min = temp->student;

		temp = temp->link;

	}

	temp = l;
	IDList list = IDLCreate(min->studentID);	// Create a list to store students
	minGPA = (min->GPA * 100) / 100;

	while(temp != NULL) {
		// Round up GPAs to 2 decimal places for comparing -- source: https://stackoverflow.com/questions/1343890/how-do-i-restrict-a-float-value-to-only-two-places-after-the-decimal-point-in-c
		tempGPA = (temp->student->GPA * 100) / 100;
		
		if(tempGPA == minGPA && strcmp(min->studentID, temp->student->studentID))			// Check if the student has the minimum GPA and is not the one we entered manually for list creation
			IDLInsert(list, temp->student->studentID);

		temp = temp->link;

	}

	return list;

}

void LDestroy(List l) {		// Free all space used by the list
	// Free space recursively
	if(l->link != NULL)
		LDestroy(l->link);
	// Free space of current node
	free(l);

}