/* contains basic build specification abstraction
* create, update, and access build specifications
*/

#include "buildrep.h"

/*
* Create a target structure from the parsed array of input strings
* Each string array will be:
* target_name: dep1 dep2 ... depn 
* command1 ...
* ..
* commandm ..
*/
Target create(char** target_strings) {

    // get target name

    // make array of char pointers for each dependency
    // count how many dependencies there are

    // make array of char pointers for each line of commands
    // count how many lines of commands there are

    // set visited to false (0)

}

void update() {

}

void access() { 

}
