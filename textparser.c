/* parse lines in the makefile
* splits line into an array of strings
* check whether a line begins with tab or regular char
* filters out blank line
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <sys/stat.h>   // stat
#include "textparser.h"
#include "buildrep.h"

static int MAX_LINE = 4096;

/* for testing purposes */
int main(void)
{
    char ** output;
    int k = 0;
    while (k <= 5) {
        parse_makefile();
    }
    return 0;
}

/* parse lines in the makefile
* splits line into an array of strings
* check whether a line begins with tab or regular char
* filters out blank line
* passes dependency and command arrays to build rep module
*/
Target *parse_makefile() {
    /* makefile line variables */
    char *line = NULL; // line being read from makefile
    char *longLine; // used to print a line greater than a buffer
    FILE *makefile; // initialize makefile
    ssize_t read; // number of characters in line read
    size_t len = 0; // initial size of string
    
    /* character compare variables */
    char firstCh; // character to be iterated and read in from stdin
    char *string_without_tab; // command line string without the tab
    char *tab; // characters of tab string
    char **c;
    char **d;
        
    /* counter variables */
    int count, count2, i; // iterators 
    int linenum = 0; // makefile line number
    int num_commands = 0; // number of command lines

    int numTargets = 0;
    Target *targetArray = malloc(1000 * sizeof(Target)); // FIGURE OUT SIZE

    for (int i=0; i<1000; i++) {
	targetArray[i] = malloc(sizeof(Target));
	if (targetArray[i]==NULL) {
	    fprintf(stderr,"Error while allocating target array\n");
	    exit(1);
	}
    }
        
    // open makefile
    makefile = fopen("/u/c/e/cecelia/Assigment3/makefile", "r");
    
    // check if makefile is a valid file
    if (makefile == NULL) {
        fprintf(stderr, "Cannot open makefile, invalid file.");
        exit(1);
    }

    /* get lines in makefile */
    while ((read = getline(&line, &len, makefile)) != -1) {
        firstCh = line[0]; // get the first character of the line
        char *string = line; // set new string to the line contents
        linenum++; // increase line number
        
        printf("%s", string);    

        /* if line is too long */
        if (read > MAX_LINE) {
            // print error for line being too long
            fprintf(stderr, "%d%s", linenum, ": Line count too long: ");
            
            /* get characters up until MAX_LINE */
            i = 0;
            while (i < MAX_LINE) {
               longLine[i] = line[i];
               i++;
            }
            printf("%s\n", longLine); // print line
            exit(1);
        }
    
        /* search for null character */
        for (int i=0; i<read; ++i) {
            if (string[i] == '\0') {
                fprintf(stderr, "%d%s%s", linenum, ": Null character found: ", string);
                exit(1);
            }            
        }    
   
        /* if comment or empty line */ 
        if ((firstCh == '#') || (firstCh == '\n') ) {
            // ignore rest of line
            continue;
        } else if ((firstCh != '>') && ((isalpha(firstCh)) || isdigit(firstCh))) {
            /* dependency declarations */
            count = 0;
            char* depend = malloc(sizeof(char) * read);
            d = malloc(sizeof(char) * read);
    
            // find target name
            depend = strtok(string,":");
            
            /* if there is no target name */
            if (depend == NULL) {
                // error
                fprintf(stderr, "%d%s%s\n", linenum,": No target name, invalid line: ", string);
                exit(1);
            }

            /* if target is valid */
            while(depend != NULL) {
                printf("%s%s\n", "Dependency: ", depend);
                // get next string in the line
                depend = strtok(NULL, " ");

                /* get each string and check to see if valid dependency
                // disregard right now
                if (stat (*depend, &buffer) != 0) {
                    fprintf(stderr, "%d%s%s\n", linenum,": Dependency not valid: ", line);
                    exit(1);
                }
                */
                
                // add dependency to array
                d[count] = depend;
                count++;
            }
        } else if (firstCh == '>') {
            /* command declarations */
            count2 = 0;
            num_commands++;
            char *command = malloc(sizeof(char) * read);
            c = malloc(sizeof(char) * read);
            tab = malloc(sizeof(char) *4);
            string_without_tab = malloc(sizeof(char) * read);
            
            /* get the first 4 characters of the line */
            for (int j = 0; j < 4; j++) {
                tab[j] = string[j];
            }

            /* if tab isn't equal to the correct tab characters */
            if (tab == ">...") {    
                // error
                printf(stderr, "%d%s%s\n", linenum, ": Invalid line format: ", string);
                exit(1);
            }

            /* set a new string equal to the line without the tab characters */
            int b = 4;
            for (int k = 0; k < (read-4); k++) {
                string_without_tab[k] = string[b];
                b++;
            }

            // get the first command of the line
            command = strtok(string_without_tab, " ");
            
            /* while first command is valid */
            while(command != NULL) {
                printf("%s%s\n", "Command: ", command);
                // get the next command of the line
                command = strtok(NULL, " ");
                c[count2] = command;
                count2++;
            }
        } else {
            // if line doesn't start with a target name or tab 
            fprintf(stderr, "%d%s%s\n", linenum, ": Invalid line format: ", string);
            exit(1);
        }
        
        if (firstCh == '\n') {
            // pass array of dependencies and array of commands to build rep.
            Target *t = create(d, c, num_commands);
	    targetArray[numTargets] = malloc(sizeof(struct Target));
	    if (NULL==targetArray[numTargets]) {
		fprintf(stderr,"Error while allocating target in array\n");
		exit(1);
	    }
	    targetArray[numTargets] = t;
	    numTargets++;
            
            // reset number of command lines
            num_commands = 0;
        }
    }
    fclose(makefile);
}
