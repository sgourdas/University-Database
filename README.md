# University Database
 A University Database Simulator written in C

## Information

This is a low level University Database Simulation. It uses a variation of data structures like Hashtables and Inverted Indexes to make queries to the data in small time periods. The basic structure is the hash table which organizes entries by student id (that acts as the key). At the same time, all data is stored in an inverted index (based on year) so we can make queries based on a specific data filter lets say. 

## Using the database

### Compilation

Enter the ``` make ``` command while in the */University-Database/* directory.

### Execution 

Type ``` ./mngstd ``` while in the project's directory

### Command line arguments
You can give the following arguments in the command line:

``` -i <inputfile> ``` : Sets the size of the board (default = 11).

``` -c <configfile> ``` : Sets the game difficulty (default = 1).

### Queries
You can use the following commands to make queries to the db:


``` i(nsert) studentif lastname firstname zip year gpa ``` : Create an entry with these attributes.

``` l(ook-up) studentid ``` : Get and print the entry corresponding to this studentid.

``` d(elete) studentid ``` : Delete the entry corresponding to this studentid.

``` n(umber) year ``` : For the inserted academic year print how many students are still active. e.g find how many are still active on their 6th year

``` t(op) num year ``` : For the inserted academic year get the num top students.

``` a(verage) year ``` : For the inserted academic year get average gpa.

``` m(inimum) year ``` : For the inserted academic year find the student with the smallest gpa.

``` c(ount) ``` : For every academic year get the number of students in the system.

``` p(ostal code) rank ``` : Find the city that is rank-th in popularity based on student's residence.

``` exit ``` : Exit the program.

## About
- This is a fifth semester assignment, by professor [A. Delis](https://www.alexdelis.eu/), for the Department of Informatics and Telecommunications, UoA. It was a part of the Operating Systems course and was given as the first assignment.
