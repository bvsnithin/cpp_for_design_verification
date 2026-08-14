/*
- Use eda playground to run SystemC code with the following settings
Testbench + Design: C++/SystemC
Libraries: Select SytemC 2.3.3 (Or whatever is available)
Tools and Simulators C++
*/

#include "systemc.h" // This is the systemc library that needs to be included. 

int sc_main (int argc, char* argv[]) {
  
  cout <<"Hello World "<< endl;
  return 0;
  
}

/* sc_main -> This is the main function that is the starting point of execution. It is basically the entry point

int argc, char* argv[] -> These are command line arguments. 

argc -> Argument Count. 
- It is an integer that stores number of arguments passed to the program. 
- This count always includes the programs executable name and hence argc is always atleast 1

argv -> Argument vector
- Array of strings each representing an argument

Example: ./my_sim -v --trace
- argc = 3
- argv[0] = "./my_sim"
- argv[1] = "-v"
- argv[2] = "--trace"

*/