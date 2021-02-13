#include "Functions.h"


IDList IDLCreate(char *id) {	// IDList creation
	// Allocate space and assign values
	IDList l = (IDList) malloc(sizeof(idl));
	l->id = malloc(strlen(id) + 1);
	strcpy(l->id, id);
	l->link = NULL;

	return l;

}

void IDLInsert(IDList list, char *id) {		// IDList insertion

	// Allocate space and assign values
	IDList l = (IDList) malloc(sizeof(idl));
	l->id = malloc(strlen(id) + 1);
	strcpy(l->id, id);
	l->link = list->link;
	// Linkage
	list->link = l;

}

void IDLPrint(IDList list) {	// IDList printing

	IDList temp = list;
	// Parse all nodes
	while(temp != NULL) {

		printf("%s ", temp->id);

		temp = temp->link;
	
	}

	printf("\n");

}

void IDLDestroy(IDList list) {	// Free space of a IDList
	
	free(list->id);
	// Recursively free extra nodes
	if(list->link != NULL)
		IDLDestroy(list->link);
	// Free current node space
	free(list);

}