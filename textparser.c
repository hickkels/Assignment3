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

/* parse lines in the makefile
* splits line into an array of strings
* check whether a line begins with tab or regular char
* filters out blank line
* passes dependency and command arrays to build rep module
*/
void parse_makefile(FILE* makefile, int *num_targets, Target **target_list) {
    /* makefile line variables */
    char *line = NULL; // line being read from makefile
    char *longLine; // used to print a line greater than a buffer
    ssize_t read; // number of characters in line read
    size_t len = 0; // initial size of string
    
    /* character compare variables */
    char firstCh; // character to be iterated and read in from stdin
    char *string_without_tab; // command line string without the tab
    char *tab; // characters of tab string
    char **c;
    char **d;
    char *name = malloc(sizeof(char) * read);
    int name_flag = 0;
        
    /* counter variables */
    int count, count2, i; // iterators 
    int linenum = 0; // makefile line number
    int num_commands = 0; // number of command lines

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
        if (firstCh == '#') {
            // ignore rest of line
            continue;
        } else if ((firstCh != '>') && ((isalpha(firstCh)) || isdigit(firstCh))) {
            /* dependency declarations */
            count = 0;
            char* depend = malloc(sizeof(char) * read);
            d = malloc(sizeof(char) * read);
    
            // find target name
            depend = strtok(string,":");
	    if (0==name_flag) {
		if (NULL==name) exit(1);
		strcpy(name, depend);
		name_flag = 1;
	    }  

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
        } else if (firstCh!='\n') {
            // if line doesn't start with a target name or tab 
            fprintf(stderr, "%d%s%s\n", linenum, ": Invalid line format: ", string);
            exit(1);
        }
        
        if (firstCh == '\n') {
            // pass array of dependencies and array of commands to build rep.
            create(name, d, count, c, num_commands);
            printf("name: %s\n", name);
	    printf("num dependencies: %d\n", count);
	    for (int i=0; i<count; i++) {
	        printf("     dep%d: %s\n", i, d[i]);           
 	    }
	    printf("num commands: %d\n", num_commands);
	    for (int i=0; i<num_commands; i++) {
		printf("     com%d: %s\n", i, c[i]);
	    }
            // reset number of command lines
            num_commands = 0;
	    name_flag = 0;
        }
    }
    fclose(makefile);
}
