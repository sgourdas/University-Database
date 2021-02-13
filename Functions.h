#include "Types.h"

/* 
	Utility functions (util.h) 
*/
void configure(int, char **);
void input(int, char **, Database);
int navigate(Database);
char *subStr(char *, int, char);
int partCount(char *);
/* 
	HashTable functions (HashTable.c) 
*/
int h(char *);
HashTable HTCreate(int);
Student HTInsert(HashNode *, char *, char *, char *, char *, int, float);
Student HTGet(HashNode *, char *);
int HTRemove(HashNode *, char *);
void HTDestroy(HashNode *);
void NodeDestroy(HashNode);
Student StudentCreate(char *, char *, char *, char *, int, float);
void StudentDestroy(Student);
/* 
	List functions (List.c) 
*/
List LCreate(Student);
void LInsert(List, Student);
int LRemove(List, char *, InvIndex *);
IDList LTop(List, int);
float LAverage(List);
IDList LMinimum(List);
void LDestroy(List);
/* 
	InvIndex functions (InvIndex.c) 
*/
InvIndex IIndexCreate(void);
void IIInsert(InvIndex, Student);
int IIRemove(InvIndex *, char *, int);
int IINum(InvIndex, int);
IDList IITop(InvIndex, int, int);
float IIAverage(InvIndex, int);
IDList IIMinimum(InvIndex, int);
YList IICount(InvIndex);
void IIDestroy(InvIndex);
int getYear(void);
/* 
	Database functions (Database.c) 
*/
Database DBCreate(int);
int DBInsert(Database, char *, char *, char *, char *, int, float);
int DBRemove(Database, char *);
int DBNum(Database, int);
IDList DBTop(Database, int, int);
float DBAverage(Database, int);
IDList DBMinimum(Database, int);
YList DBCount(Database);
IDList DBPostal(Database, int);
void DBDestroy(Database);
/* 
	IDList functions (IDList.c) 
*/
IDList IDLCreate(char *);
void IDLInsert(IDList, char *);
void IDLPrint(IDList);
void IDLDestroy(IDList);
/* 
	YList functions (YList.c) 
*/
YList YLCreate(int, int);
void YLInsert(YList, int, int);
void YLPrint(YList);
void YLDestroy(YList);
/* 
	ZList functions (ZList.c) 
*/
ZList ZLCreate(char *);
void ZLInsert(ZList, char *);
int ZLRemove(ZList l, char *zip, ZList *);
// void ZLPrint(ZList, int);	// Used for debugging
void ZLSort(ZList);
IDList ZLPostal(ZList, int);
void ZLDestroy(ZList);