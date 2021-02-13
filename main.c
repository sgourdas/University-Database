#include "Functions.h"

int TABLESIZE = 50;


int main(int argc, char **argv) {
	// Get configuration such as tablesize
	configure(argc, argv);
	// Create the database
	Database db = DBCreate(TABLESIZE);
	// Get input from file -- if there is one as an arg
	input(argc, argv, db);
	// Bring up to the commands menu
	navigate(db);

	return 0;

}