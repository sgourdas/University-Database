#include "Functions.h"


ZList ZLCreate(char *zip) {	// ZList create
	// Allocate space and assign values
	ZList l = (ZList) malloc(sizeof(zl));
	l->zip = malloc(strlen(zip) + 1);
	strcpy(l->zip, zip);
	l->count = 1;
	l->link = NULL;

	return l;

}

void ZLInsert(ZList list, char *zip) {	// ZList insertion

	ZList temp = list, backup = list;
	// Go through the list
	while(temp != NULL) {

		if(!strcmp(temp->zip, zip)) {	// If node has the zip we want

			temp->count++;
			return;

		}

		backup = temp;
		temp = temp->link;
	
	}
	// Here we are at the end of the list
	// Allocate new space and assign values
	ZList l = ZLCreate(zip);
	// Linkage
	backup->link = l;

}

int ZLRemove(ZList l, char *zip, ZList *inv) { // Remove the node with the correct 'id'

	if(!strcmp(l->zip, zip)) {	
		// if the first node of the list needs to be removed, we correctly link the inv pointer from the upper level
		// We do not need InfoDestroy(l->info), because it will be done on HTRemove()
		*inv = l->link;
		free(l->zip);
		free(l);

		return 0;

	}

	ZList temp = l->link, backup = l;
	// Cycle all list nodes
	while(temp != NULL) {

		if(!strcmp(temp->zip, zip)) {
			// We do not need InfoDestroy(temp->info), because it will be done on HTRemove()
			backup->link = temp->link;	// Link the gap that will be created
			free(temp->zip);
			free(temp);		// Free space allocated for this node
			return 0;
		
		}
		// Linking
		backup = temp;
		temp = temp->link;

	}

	return 1;

}

/* void ZLPrint(ZList list, int rank) {	// ZList printing for debugging

	ZList temp = list;
	int counter = 0, flag = 0;;
	// Parse all nodes
	while(temp != NULL) {

		counter++;

		if(counter == rank || flag == temp->count) {

			printf("{%s , %d} ", temp->zip, temp->count);
			flag = temp->count;

		}

		temp = temp->link;
	
	}

	printf("\n");

} */

void ZLSort(ZList list) {

	int a;
    char *a2;
    // For every node
    for(ZList temp1 = list ; temp1 != NULL ; temp1 = temp1->link) {
    	// For every node after the outer one
        for(ZList temp2 = temp1->link ; temp2 != NULL ; temp2 = temp2->link) {
        	// Sort based on count
            if(temp2->count > temp1->count) {
            	// Swap contents
                a = temp1->count;
                a2 = temp1->zip;
                temp1->count = temp2->count;
                temp1->zip = temp2->zip;
                temp2->count = a;
                temp2->zip = a2;

            }

        }

    }

}

IDList ZLPostal(ZList list, int rank) {	// Get the rank-th zip code
	// Sort the list for correct searhing
	ZLSort(list);

	IDList final = NULL;
	ZList temp = list;
	int counter = 0, flag = 0, previousCount = -1;
	// Parse all nodes
	while(temp != NULL) {

		if(temp->count != previousCount)	// This is here so we do not up the counter while we are on the same rank -- count only for distinct values of counters
			counter++;						// Same counter values have the same rank
		// When we find the first item we want to get, we raise the flag and continue adding until the counter value changes for a node
		if(counter == rank || flag == temp->count) {

			if(flag == 0)	// If flag is down create the list since we have not yet started 
				final = IDLCreate(temp->zip);
			else
				IDLInsert(final, temp->zip);	// Flag is up so add items to the already made list

			flag = temp->count;	// Raise the flag

		}

		previousCount = temp->count;	// Keep this for correct counting
		temp = temp->link;
	
	}
	// Return final list
	return final;

}

void ZLDestroy(ZList list) {	// Free space of a ZList 
	// Recursively free extra nodes
	if(list != NULL && list->link != NULL)	// (list != NULL) allows for instant exit after program startup
		ZLDestroy(list->link);
	// Free current node space
	if(list != NULL && list->zip != NULL)	// (list != NULL) allows for instant exit after program startup
		free(list->zip);
	// Free current node
	if(list != NULL)
		free(list);

}