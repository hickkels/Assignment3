#include "filerep.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
* Create a file struct with file name and visited status
*/
File *create(char *name) {

    // malloc file struct
    File *f;
    f = malloc(sizeof(File));
    if (NULL==f) {
        fprintf(stderr,"Error while allocating file\n");
        exit(1);
    }

    f->name = name;
    f->visited = 0; // set visited to false (0)

    return f;
}

/*
* Create a function to see if a file name is contained in array of file pointers 
* Return 1 if yes, 0 if no, 2 if file name not found
*/
int file_visited(char *name, File **file_list, int num_files) {

    for (int i=0; i<num_files; i++) {
	File *curr = file_list[i];
	if (strcmp(curr->name, name)==0) return curr->visited;
    }
    return 2;
}

