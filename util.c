#include "Functions.h"


void configure(int argc, char **argv) {		// Function for -i argument

	if(argc > 1) {

		FILE *filePath;
		char *config;

		/*
			argv choices:
				-i	inputfile
				-c	configfile
		*/
		// Go through all arguments
		for (int i = 1 ; i < argc ; i++) {
			// Check if we have -c as argument
			if(!strcmp("-c", argv[i])) { /* if we have -c */

				char *a1, *a2;
				// Store config file name
				config = argv[i+1];
				// Open a stream to the file
				filePath = fopen(config, "r");
				// Reserve space to store line readings
				char inputf[1000];
				// Go through all line readings untill we reach end of file
				while(fgets(inputf, 1000, filePath) != NULL && inputf != (char *) EOF) {
					// Copy parameters 1 and 2 to a2 and a2 respectively
					a1 = subStr(inputf, 1, ' ');
					a2 = subStr(inputf, 2, ' ');
					// If parameters are set for tablesize, change the value accordingly
					if(!strcmp("TABLESIZE", a1) || !strcmp("tablesize", a1))
						TABLESIZE = atoi(a2);
					// Free space from subStr
					free(a1);
					free(a2);

				}
				// Close file stream
				fclose(filePath);

			}

		}

	}

}

void input(int argc, char **argv, Database db) {	// Function for -i argument

	if(argc > 1) {

		FILE *filePath;
		char *input;

		/*
			argv choices:
				-i	inputfile
				-c	configfile
		*/
		// Go through all arguments
		for (int i = 1 ; i < argc ; i++) {
			// Check if we have -i as argument
			if(!strcmp("-i", argv[i])) { /* if we have -i */

				char *a1, *a2, *a3, *a4, *a5, *a6;
				// Store input file name
				input = argv[i+1];
				// Open a stream to the file
				filePath = fopen(input, "r");
				// Reserve space to store line readings
				char inputf[1000];
				// Go through all line readings untill we reach end of file
				while(fgets(inputf, 1000, filePath) != NULL && inputf != (char *) EOF) {
					// Copy all parameters needed to a(rgument)# variables
					a1 = subStr(inputf, 1, ' ');
					a2 = subStr(inputf, 2, ' ');
					a3 = subStr(inputf, 3, ' ');
					a4 = subStr(inputf, 4, ' ');
					a5 = subStr(inputf, 5, ' ');
					a6 = subStr(inputf, 6, ' ');
					// Try to insert the entry to the database and print the according message based on return 
					if(!DBInsert(db, a1, a2, a3, a4, atoi(a5), atof(a6)))
						printf("- Student %s inserted\n", a1);
					else
						printf("- Student %s exists\n", a1);
					// Free space from subStr
					free(a1);
					free(a2);
					free(a3);
					free(a4);
					free(a5);
					free(a6);

				}
				// Close file stream
				fclose(filePath);

			}

		}

	}

}


int navigate(Database db) {		// Continuous command insertion function for determining appropriate actions

	char *temp, cmd[1000];
	
	do {
	
		printf("Database> ");
		// Read the Command
		scanf("%[^\n]%*c",cmd);
		// Get the first word of the complete command, to determine the category
		temp = subStr(cmd, 1, ' ');
		/* Decide what the Command is and act accordingly 
			-- every single one of these outside ifs 
			correspond to a different in-game command     */
		if(!strcmp(temp, "insert") || !strcmp(temp, "i")) {
			if(partCount(cmd) == 7) {// check this
				// Assign each parameter of insert command to a variable for insertion
				char *a2 = subStr(cmd, 2, ' ');
				char *a3 = subStr(cmd, 3, ' ');
				char *a4 = subStr(cmd, 4, ' ');
				char *a5 = subStr(cmd, 5, ' ');
				char *a6 = subStr(cmd, 6, ' ');
				char *a7 = subStr(cmd, 7, ' ');
				// Try to insert the entry to the database and print the according message based on return 
				if(!DBInsert(db, a2, a3, a4, a5, atoi(a6), atof(a7)))
					printf("- Student %s inserted\n", a2);
				else
					printf("- Student %s exists\n", a2);
				// Free all space reserved
				free(a2);
				free(a3);
				free(a4);
				free(a5);
				free(a6);
				free(a7);

			} else {

				printf("Correct usage: <i(nsert) studentid lastname firstname zip year gpa>\n");

			}
	 
		} else if(!strcmp(temp, "look-up") || !strcmp(temp, "l")) {
				
			if(partCount(cmd) == 2) {
				// Store the second argument (id)
				char *id = subStr(cmd, 2, ' ');
				// Call HTGet() with the appropriate paramaters for lookup
				Student res = HTGet(db->hash, id);
				// Print message according to HTGet() return value
				if(res == NULL)
					printf("- Student <%s> does not exist\n", id);
				else
					printf("- %s %s %s %s %d %f\n", res->studentID, res->lastName, res->firstName, res->zip, res->year, res->GPA);
				// Free space used for argument
				free(id);

			} else {

				printf("Correct usage: <l(ook-up) studentid>\n");

			}

		} else if(!strcmp(temp, "delete") || !strcmp(temp, "d")) {

			if(partCount(cmd) == 2) {
				// Store the second argument (id)
				char *id = subStr(cmd, 2, ' ');
				// Call DBRemove() with the appropriate arguments and print accordingly to return value
				if(DBRemove(db, id) == 0)
					printf("- Record %s deleted\n", id);
				else
					printf("- Student %s does not exist\n", id);
				// Free space used for argument
				free(id);

			} else {

				printf("Correct usage: <d(elete) studentid>\n");

			}

		} else if(!strcmp(temp, "number") || !strcmp(temp, "n")) {

			if(partCount(cmd) == 2) {
				// Store the second argument (year)
				char *year = subStr(cmd, 2, ' ');
				// Call DBNum() with the appropriate arguments
				int num = DBNum(db, atoi(year));
				// Print according to the value returned from DBNum()
				if(num == -1)
					printf("- No students enrolled in %s\n", year);
				else
					printf("- %d student(s) in %s\n", num, year);
				// Free space used for argument
				free(year);

			} else {

				printf("Correct usage: <n(umber) year>\n");

			}

		} else if(!strcmp(temp, "top") || !strcmp(temp, "t")) {	// add list return
				
			if(partCount(cmd) == 3) {
				// Store the second and third arguments (num & year)
				char *num = subStr(cmd, 2, ' ');
				char *year = subStr(cmd, 3, ' ');
				// Call DBTop() with the appropriate arguments
				IDList top = DBTop(db, atoi(num), atoi(year));
				// Print according to the value returned from DBTop()
				if(top == NULL) {

					printf("- No students enrolled in %s\n", year);

				} else {

					printf("- ");
					IDLPrint(top);
					IDLDestroy(top);

				}
				// Free space used for arguments
				free(num);
				free(year);

			} else {

				printf("Correct usage: <t(op) num year>\n");

			}

		} else if(!strcmp(temp, "average") || !strcmp(temp, "a")) {

			if(partCount(cmd) == 2) {
				// Store the second argument (year)
				char *a = subStr(cmd, 2, ' ');
				// Convert argument from char* to int
				int year = atoi(a);
				// Free space used for argument
				free(a);
				// Call DBAverage() with the correct arguments
				float average = DBAverage(db, year);
				// Print according to the value returned from DBTop()
				if(average == -1)
					printf("- No students enrolled in %d\n", year);
				else
					printf("- %.2f\n", average);

			} else {

				printf("Correct usage: <a(verage) year>\n");

			}

		} else if(!strcmp(temp, "minimum") || !strcmp(temp, "m")) {
				
			if(partCount(cmd) == 2) {
				// Store the second argument (year)
				char *year = subStr(cmd, 2, ' ');
				// Call DBMinimum() with the correct arguments
				IDList data = DBMinimum(db, atoi(year));
				// Print and free memory according to returned value
				if(data == NULL) {

					printf("- No students enrolled in %s\n", year);

				} else {

					printf("- ");
					IDLPrint(data);
					IDLDestroy(data);

				}
				// Free space used for argument
				free(year);

			} else {

				printf("Correct usage: <m(inimum) year>\n");

			}

		} else if(!strcmp(temp, "count") || !strcmp(temp, "c")) {
				
			if(partCount(cmd) == 1) {
				// Call DBCount() to retrieve the data needed
				YList list = DBCount(db);
				// Print and free memory according to returned value
				if(list == NULL) {

					printf("- No students enrolled\n");

				} else {

					printf("- ");
					YLPrint(list);
					YLDestroy(list);

				}

			/*} else if(partCount(cmd) == 2) {

				char *a = subStr(cmd, 2, ' ');

				if(!strcmp(a, "*"))
					printf("- %d\n", db->entries);

				free(a);*/	// Extra feature -- use "count *" to show all entries -- uncomment for enable
			
			} else {

				printf("Correct usage: <c(ount)>\n");

			}

		} else if(!strcmp(temp, "postal") || !strcmp(temp, "p")) {
			// Recognize type of input
			if(!strcmp(temp, "p")) {

				if(partCount(cmd) == 2) {

					IDList output = NULL;

					char *rank = subStr(cmd, 2, ' ');

					output = DBPostal(db, atoi(rank));
					// Print and free memory according to returned value
					if(output == NULL) {
						
						printf("- No students enrolled\n");
					
					} else {

						printf("- ");
						IDLPrint(output);
						IDLDestroy(output);

					}
					// Free space used for argument
					free(rank);

				} else {

					printf("Correct usage: <p(ostal code) rank>\n");

				}

			} else if(!strcmp(temp, "postal")) {

				IDList output = NULL;

				if(partCount(cmd) == 3) {
					// Get the second argument
					char *a = subStr(cmd, 2, ' ');
				
					if(!strcmp(a, "code")) {
						// Get the third argument
						char *rank = subStr(cmd, 3, ' ');

						output = DBPostal(db, atoi(rank));
						// Print and free memory according to returned value
						if(output == NULL) {
					
							printf("- No students enrolled\n");
						
						} else {

							printf("- ");
							IDLPrint(output);
							IDLDestroy(output);

						}

						free(rank);
					
					} else {

						printf("Correct usage: <p(ostal code) rank>\n");

					}
					// Free space used for argument
					free(a);
				
				} else {

					printf("Correct usage: <p(ostal code) rank>\n");

				}


			}


		} else if(!strcmp(temp, "exit") || !strcmp(temp, "e")) {
			// Destroy Database
			DBDestroy(db);
			// Free the space used for command argument
			free(temp);

			printf("- exit program\n");

			return 0;

		} else { printf("Uknown Command!\n"); }
		// Free the space used for command argument
		free(temp);

	} while(1);

}

char *subStr(char *str1, int part, char seperator) { 		/*    subStr is a function that copies the part
													     		substring of str1 to str2 and returns str2's 
													  address - "parts" are strings seperated by a 'seperator' char 
													  	  we could have used default ' ' seperator but it is here 
													  					for expandability purposes             */
	int i = 0, j = 0;
	char *str2 = malloc(1000);

	while(part > 1) {

		while(str1[i] != seperator) // Cycle through parts 
			i++;

		i++;
		part--;

	}

	// Here we have reached the part we want to copy

	while(!(str1[i] == seperator || str1[i] == '\0')) {	// Copy chars until we find a seperator or end of string

		str2[j] = str1[i];
		i++;
		j++;

	}
	// Put string ending character at the end, after finishing copying
	str2[j] = '\0';

	return str2;

}

int partCount(char *str) { // partCount function just counts how many parts str has (counts spaces + 1) 

	int parts = 1, i = 0;
	// While we have not reached the end of the string
	while(str[i] != '\0') {
		// Up parts if char was space
		if(str[i] == ' ')
			parts++;
		// Up character index
		i++;

	}

	return parts;

}