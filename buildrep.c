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
Target *create(char* dependencies, char** commands, int num_commands) {

    // malloc target struct
    Target *t;
    t = malloc(sizeof(Target));
    if (NULL==t) {
        fprintf(stderr,"Error while allocating target\n");
        exit(1);
    }

    // count how many dependencies there are
    char *first_line = dependencies;
    int first_line_len = sizeof(first_line);

    int dep_count = 0;
    int target_name_len = 0;

    int target_found_flag = 0;
    for (int i=0; i<first_line_len; i++) {
        while(first_line[i]!=':' && target_found_flag==0) {
	    target_name_len++;
	    i++;
	}
        target_found_flag = 1;
        if (first_line[i]==' ') {
	    dep_count++;
	}
    }

    // copy the first target_name_len chars into t->name
    char targetName[target_name_len+1];
    strncpy(targetName, dependencies, target_name_len);
    targetName[target_name_len] = '\0'; // null terminator
    t->name = targetName;    

    t->num_dependencies = dep_count;

    // make array of char pointers for each dependency
    t->dependencies = malloc(sizeof(char*)*dep_count);
    if (t->dependencies==NULL) {
        fprintf(stderr,"Error while allocating dependency 2D char array\n");
        exit(1);
    }

    // copy all num_dependencies dependencies into dep array
    char *first_line_ptr = strtok(first_line, " ");

    int i=0;
    while(first_line_ptr != NULL) {
        t->dependencies[i] = first_line_ptr;
        i++;
	first_line_ptr = strtok(NULL, " ");
    }

    // make array of char pointers for each line of commands
    t->num_command_lines = num_commands-1;
    t->command_lines = malloc(sizeof(char*)*num_commands-1);
    if (t->command_lines==NULL) {
        fprintf(stderr,"Error while allocating command 2D char array\n");
        exit(1);
    }

    for (int i=0; i<num_commands-1; i++) {
        t->command_lines[i] = commands[i+1];
    }

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
