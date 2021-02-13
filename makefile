SOURCE	= main.c util.c HashTable.c List.c InvIndex.c Database.c IDList.c YList.c ZList.c
OBJS 	= main.o util.o HashTable.o List.o InvIndex.o Database.o IDList.o YList.o ZList.o
HEADER  = Functions.h Types.h
OUT  	= mngstd
CC	    = gcc
CFLAGS  = -g -Wall -Werror

make: $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) -o $(OUT)
	
main.o: main.c Functions.h Types.h
	$(CC) -c $(CFLAGS) main.c

util.o: util.c Functions.h Types.h
	$(CC) -c $(CFLAGS) util.c

HashTable.o: HashTable.c Functions.h Types.h
	$(CC) -c $(CFLAGS) HashTable.c

List.o: List.c Functions.h Types.h
	$(CC) -c $(CFLAGS) List.c

InvIndex.o: InvIndex.c Functions.h Types.h
	$(CC) -c $(CFLAGS) InvIndex.c

Database.o: Database.c Functions.h Types.h
	$(CC) -c $(CFLAGS) Database.c

IDList.o: IDList.c Functions.h Types.h
	$(CC) -c $(CFLAGS) IDList.c

YList.o: YList.c Functions.h Types.h
	$(CC) -c $(CFLAGS) YList.c

ZList.o: ZList.c Functions.h Types.h
	$(CC) -c $(CFLAGS) ZList.c

clean:
	rm -f $(OBJS) $(OUT)
