#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

extern int TABLESIZE;


/* 
	ZList structure 
*/
typedef struct zlst {

	char *zip;
	int count;
	struct zlst *link;

} zl;

typedef zl *ZList;
/* 
	Student structure 
*/
typedef struct {

	char *studentID;
	char *lastName;
	char *firstName;
	char *zip;	// Can start with 0
	int year;
	float GPA;

} inf;

typedef inf *Student;
/* 
	HashTable structure 
*/
typedef struct NodeTag {

	Student content;
	struct NodeTag *link;

} HashNodeType;

typedef HashNodeType *HashNode;

typedef HashNode *HashTable;
/* 
	List structure 
*/
typedef struct lnode {

	Student student;
	struct lnode *link;

} ListNode;

typedef ListNode *List;
/* 
	InvIndex structure 
*/
typedef struct Dummy {

	int year;
	int count;
	struct Dummy *link;
	List list;

} DummyNode;

typedef DummyNode *InvIndex;
/* 
	Database structure 
*/
typedef struct {

	InvIndex inverted;
	HashTable hash;
	ZList ZCodes;
	int entries;

} db;

typedef db *Database;
/* 
	IDList structure 
*/
typedef struct idlst {

	char *id;
	struct idlst *link;

} idl;

typedef idl *IDList;
/* 
	YList structure 
*/
typedef struct ylst {

	int year;
	int count;
	struct ylst *link;

} yl;

typedef yl *YList;