/* contains basic build specification abstraction
* create, update, and access build specifications
*/

#include "buildrep.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
* Create a target structure from the parsed array of input strings
* Each string array will be:
* target_name: dep1 dep2 ... depn 
* command1 ...
* ..
* commandm ..
*/
Target *create(char *name, char** dependencies, int num_depends, char** commands, int num_commands) {

    // malloc target struct
    Target *t;
    t = malloc(sizeof(Target));
    if (NULL==t) {
        fprintf(stderr,"Error while allocating target\n");
        exit(1);
    }

    printf("%s\n", "MADE IT");
    t->name = name;
    t->dependencies = dependencies;
    t->num_dependencies = num_depends;
    t->command_lines = commands;
    t->num_command_lines = num_commands;

    // set visited to false (0)
    t->visited = 0;
    // set initial mod time to zero
    t->modTime = 0; 

    return t;
}

void update() {

}

void access() { 

}
