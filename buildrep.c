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
void create(char *name, char** dependencies, int num_depends, char** commands, int num_commands, Target **target_list, int num_targets) {

    // malloc target struct
    target_list[num_targets] = malloc(sizeof(Target));
    if (NULL==target_list[num_targets]) {
        fprintf(stderr,"Error while allocating target\n");
        exit(1);
    }

    target_list[num_targets]->name = name;
    printf("THIS IS THE NAME OF THE TARGET WERE CREATING %s\n", name);
    target_list[num_targets]->dependencies = dependencies;
    target_list[num_targets]->num_dependencies = num_depends;
    target_list[num_targets]->command_lines = commands;
    target_list[num_targets]->num_command_lines = num_commands;

    // set visited to false (0)
    target_list[num_targets]->visited = 0;
    // set initial mod time to zero
    target_list[num_targets]->modTime = 0; 

}

void update() {

}

void access() { 

}
