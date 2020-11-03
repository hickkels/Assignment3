#include "buildgraph.h"
#include "buildrep.h"
#include "proccreate.h"
#include "textparser.h"
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

    // iterate through array of target structures
    for (int i = 0; i<num_targets; i++) {
        // check for cycles in each structure
	    traverseGraph(target_list[i]);
    }

    // run process creation to run commands
    for (int i = 0; i < num_targets; i++) {
        run_command(target_list[i], target_list, num_targets);    
    }
}

