#include "buildgraph.h"
#include "buildrep.h"
#include "proccreate.h"
#include "textparser.h"
#include "filerep.h"
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[]) {

    FILE *fp; // call text parser on file
    struct Target *target_list[100]; // text parser will return an array of targets
    for (int i=0; i<100; i++) {
	target_list[i] = (struct Target*) malloc(sizeof(struct Target));
        if (NULL==target_list[i]) {
            fprintf(stderr,"Error while allocating target in array\n");
            exit(1);
        }
    }

    int num_targets = 0;
    
    printf("made it here\n");

    // check for lowercase then uppercase makefiles
    if (((fp = fopen("exMakefile", "r")) != NULL)) {
        parse_makefile(fp, &num_targets, target_list);
    } else if ((fp = fopen("Makefile", "r") != NULL)) {
        parse_makefile(fp, &num_targets, target_list);
    } else {
	// print error if not found and exit
        fprintf(stderr, "Cannot open makefile, invalid file.\n");
        exit(1);
    }

    printf("------------TARGETS in main (%d total)----------\n", num_targets);
    printf("\n");
    for (int i = 0; i<num_targets; i++) {
        printf("i: %d\n", i);
        Target *curr = target_list[i];
        printf("name of target: %s\n", curr->name);
	printf("num dependencies: %d\n", curr->num_dependencies); 
        for (int i=0; i<curr->num_dependencies; i++) {
	    printf("    dep %d: %s\n", i, curr->dependencies[i]);
	}
        printf("num commands: %d\n", curr->num_command_lines);
        for (int i=0; i<curr->num_command_lines; i++) {
             printf("    comm %d: %s\n", i, curr->command_lines[i]);
        }
	printf("\n");
    }

    // count file dependencies
    int file_count = count_files(target_list, &num_targets);
    
    // create array of file structs
    struct File *file_list[file_count]; // text parser will return an array of targets
    for (int i=0; i<file_count; i++) {
        file_list[i] = (struct File*) malloc(sizeof(struct File));
        if (NULL==file_list[i]) {
            fprintf(stderr,"Error while allocating file in array\n");
            exit(1);
        }
    }
        
    // update array of file structs to have one file struct for each file
    int num_unique_files = createFileStructs(file_list, &file_count, target_list, &num_targets);

    // iterate through array of target structure
    buildGraph(target_list, num_targets);

    // run process creation to run commands
    for (int i = 0; i < num_targets; i++) {
        run_command(target_list[i], target_list, num_targets);    
    }
}

