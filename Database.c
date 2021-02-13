#include "Functions.h"


Database DBCreate(int size) {		// Creates a database struct with a hashtable and an inverted index
	// Allocate memory needed for this
	Database data = (Database) malloc(sizeof(db));
	// Call Creation functions for hash table and inverted index
	data->hash = HTCreate(TABLESIZE);
	data->inverted = IIndexCreate();
	data->ZCodes = NULL;
	data->entries = 0;

	return data;

}

int DBInsert(Database db, char *id, char *ln, char *fn, char *zip, int year, float gpa) {
	// Check if entry exists with HTGet()
	if(HTGet(db->hash, id) != NULL)	// If entry does exist
		return -1;
	// Up entries counter
	db->entries++;
	// If there are no entries
	if(db->ZCodes == NULL)
		db->ZCodes = ZLCreate(zip);
	else
		ZLInsert(db->ZCodes, zip);
	/* 			 	Insert data to hash table with HTGet() and 
	use the Student structure return from that to insert to the inverted index */
	IIInsert(db->inverted, HTInsert(db->hash, id, ln, fn, zip, year, gpa));

	return 0;

}

int DBRemove(Database db, char *id) {		// Remove student with 'id' id from the database
	// Check if the student is already in the structure
	Student Student = HTGet(db->hash, id);

	if(Student == NULL)
		return -1;	// Student is not in database

	// Call IIRemove() to remove the entry first from the inverted index
	int ret = IIRemove(&db->inverted, id, Student->year) + ZLRemove(db->ZCodes, Student->zip, &db->ZCodes);
	// Then remove entry from the hash table and return appropriate value
	ret += HTRemove(db->hash, id);

	if(--db->entries == 0) {	// If every entry is removed self correct and complete all "missaligned" places

		db->hash[h(id)] = (HashNode) malloc(sizeof(HashNodeType));
		db->hash[h(id)]->content = NULL;
		db->hash[h(id)]->link = NULL;

		db->inverted = IIndexCreate();

		db->ZCodes = NULL;
	
	}

	return ret;

}

int DBNum(Database db, int year) {		// Find the number of students in year
	// Call lower level function of the inverted index
	return IINum(db->inverted, year);

}

IDList DBTop(Database db, int size, int year) {		// Get a list of the students with the best GPA in 'year' year of study
	// Call lower level function of the inverted index
	return IITop(db->inverted, size, year);

}

float DBAverage(Database db, int year) {	// Find the average GPA for students in 'year' of study
	// Call lower level function of the inverted index
	return IIAverage(db->inverted, year);

}

IDList DBMinimum(Database db, int year) {	// Get the list of students with the min GPA for 'year' year of study
	// Call lower level function of the inverted index
	return IIMinimum(db->inverted, year);

}

YList DBCount(Database db) {	// Get the number of students for each year of study
	// Call lower level function of the inverted index
	return IICount(db->inverted);

}

IDList DBPostal(Database db, int rank) {	// Get the rank-th zip code
	// Call lower level function of the Zip Codes List
	return ZLPostal(db->ZCodes, rank);

}

void DBDestroy(Database db) {	// Free space allocated for the database

	ZLDestroy(db->ZCodes);
	IIDestroy(db->inverted);
	HTDestroy(db->hash);
	free(db);

}