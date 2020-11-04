#include "filerep.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
* Create a file struct with file name and visited status
*/
File *create_file(char *name) {

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

int count_files(Target **target_list, int num_targets) {

    int file_count = 0;
    for (int i=0; i<num_targets; i++) {
        Target *curr = target_list[i];
        file_count = file_count + curr->num_dependencies;
    }
    return file_count;
}

/*
* Create a function to see if a file name is contained in array of file pointers 
* Return 1 if yes, 0 if no, 2 if file name not found
*/
int file_visited(char *name, File **file_list, int *num_files) {
    for (int i=0; i<num_files; i++) {
	File *curr = file_list[i];
	if (strcmp(curr->name, name)==0) return curr->visited;
    }
    return 2;
}

int createFileStructs(File **file_list, int file_count, Target **target_list, int *num_targets) {

    int num_unique_files = 0;

    for (int i=0; i<num_targets; i++) {

	Target *curr = target_list[i];
	for (int j=0; j<curr->num_dependencies; j++) {

	    char *dep_name = curr->depencencies[i];
	    int flag = fileExists(file_list, num_unique_files, dep_name);
	    if (flag==0) {
                File *f;
                f = malloc(sizeof(File));
                if (NULL==f) {
                    fprintf(stderr,"Error while allocating file\n");
                    exit(1);
                }
		file_list[num_unique_files] = f;
		num_unique_files++;
	    }
 	}
    }
   
    return num_unique_files;
}

/*
* Function to see if file name is already contained in array of file pointers
* Return 1 if yes, 0 if file name not found
*/
int fileExists(File **file_list, int file_count, char *name) {

    for (int i=0; i<file_count; i++) {
	File *curr = file_list[i];
        if (strcmp(curr->name, name)==0) return 1;
    }
    return 0;
}

