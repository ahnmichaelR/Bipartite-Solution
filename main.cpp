#include <iostream>

#include "PA2.h"

// INTRODUCTION:
/*This code uses PA2.h header file along with the PA2.cpp that is an implementation of the PA2 class.
 The Solver method of the PA2 class takes in a string input of the text name
and returns a 0 or 1 if the graph in the text file is an invalid or valid bipartite graph,respectively */
 /*-----------------------
 HOW TO RUN CODE:
 COMPILE INSTRUNCTIONS: 
 1. g++ -std==c++11 main.cpp PA2.cpp
 2. g++ main.o PA2.o
 */
 /*CONSOLE INTRUCTIONS
 / ./a.out {enter textfile}
 -------------------------*/


using namespace std;
int main(int argc, char * argv []){
	if(argc != 2){
	cout << "Wrong number of inputs, type in file name." << endl;
	exit(1);
	}
	string input = argv[1];
	if(Solver(input)){
		printf("This graph is 2 colorable\n");
	}
	else{
		printf("This graph is not 2 colorable\n");
	}
	return 0;

}

/*TIME RESULTS
----------
smallgraph
real 0.00
user 0.00
Sys 0.00
---------
largegraph1
real 3.16
user 3.01
Sys  0.04
---------
largegraph2
real 2.23
user 2.13
Sys  0.04
---------*/