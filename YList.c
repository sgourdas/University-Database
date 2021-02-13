#include "Functions.h"


YList YLCreate(int year, int count) {	// YList create
	// Allocate space and assign values
	YList l = (YList) malloc(sizeof(yl));
	l->year = year;
	l->count = count;
	l->link = NULL;

	return l;

}

void YLInsert(YList list, int year, int count) {	// YList insertion

	// Allocate space and assign values
	YList l = (YList) malloc(sizeof(yl));
	l->year = year;
	l->count = count;
	l->link = list->link;
	// Linking
	list->link = l;

}

void YLPrint(YList list) {	// YList printing

	YList temp = list;
	// Parse all nodes
	while(temp != NULL) {

		printf("{%d , %d} ", temp->year, temp->count);
		temp = temp->link;
	
	}

	printf("\n");

}

void YLDestroy(YList list) {	// Free space of a YList 
	// Recursively free extra nodes
	if(list->link != NULL)
		YLDestroy(list->link);
	// Free current node space
	free(list);

}