#include "buildgraph.h"
#include "buildrep.h"
#include "proccreate.h"
#include "textparser.h"

int main(int argc, char *argv[]) {

    // check for lowercase then uppercase makefiles
	// print error if not found and exit
    
    makefile = fopen("/u/c/e/cecelia/Assigment3/makefile", "r");
    
    // call text parser on file
	// text parser will return an array of targets

    FILE *fp;
    // TODO: what is size of target array?
    char *target_array[];

    if (((fp = fopen(makefile, "r")) == NULL)) {
        target_array = parse_makefile(makefile);
    } else if ((fp = fopen(Makefile, "r") == NULL)) {
        target_array = parse_makefile(Makefile);
    } else {
        fprintf(stderr, "Cannot open makefile, invalid file.");
        exit(1);
    }

    // iterate through array of target structures
        // check for cycles in each structure
    for (int i = 0; i < t->num_dependencies; i++;) {
        traverseGraph(target_array[i]);
    }

    // TODO: find length of var
    // run process creation to run commands
    for (int i = 0; i < var; i++;) {
        run_command(target_array[i]);    
    }
}



