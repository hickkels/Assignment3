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
Target create(char* dependencies, char** commands, int num_commands) {

    // malloc target struct
    Target *t;
    t = malloc(sizeof(Target));
    if (NULL==t) {
        fprintf(stderr,"Error while allocating target\n");
        exit(1);
    }

    // get target
    // count how many dependencies there are
    char *first_line = target_strings[0];
    int first_line_len = sizeof(first_line);

    char *target_name = "";   

    int dep_count = 0;
    int target_name_len = 0;

    int target_found_flag = 0;
    for (i=0; i<first_line_len; i++) {
        while(first_line[i]!=':' && target_found_flag==0) {
	    target_name_len++;
	    i++;
	}
        target_found_flag = 1;
        if (first_line[i]==' ') {
	    dep_count++;
	}
    }

    // TODO: copy the first target_name_len chars into t->name
    t->num_dependencies = dep_count;

    // make array of char pointers for each dependency
    t->dependencies = malloc(sizeof(char*)*num_dependencies);
    if (t->dependencies==NULL) {
        fprintf(stderr,"Error while allocating dependency 2D char array\n");
        exit(1);
    }
    // TODO: copy all num_dependencies dependencies into dep array

    char *first_line_ptr = strtok(first_line, " ");

    int i=0;
    while(first_line_ptr != NULL) {
        t->dependencies[i] = first_line_ptr;
        i++;
	first_line_ptr = strtok(NULL, " ");
    }

    // make array of char pointers for each line of commands
    t->num_command_lines = num_strings-1;
    t->command_lines = malloc(sizeof(char*)*num_strings-1);
    if (t->command_lines==NULL) {
        fprintf(stderr,"Error while allocating command 2D char array\n");
        exit(1);
    }

    for (int i=0; i<num_strings-1; i++) {
        t->command_lines[i] = targetstrings[i+1];
    }

    // set visited to false (0)
    t->visited = 0;

    return t;
}

void update() {

}

void access() { 

}
