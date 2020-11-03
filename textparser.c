/* parse lines in the makefile
* splits line into an array of strings
* check whether a line begins with tab or regular char
* filters out blank line
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
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
    char tab_chars[] = ">...";
    ssize_t read; // number of characters in line read
    size_t len = 0; // initial size of string    

    /* character compare variables */
    char firstCh; // character to be iterated and read in from stdin
    char *string_without_tab; // command line string without the tab
    char tab[4]; // characters of tab string
    char **c;
    char **d;
    bool colon = false;
        
    /* counter variables */
    int count, count2, i; // iterators 
    int linenum = 0; // makefile line number
    int num_commands = 0; // number of command lines
    char *name;
    int numTargets = 0;
        
    /* get lines in makefile */
    while ((read = getline(&line, &len, makefile)) != -1) {
        firstCh = line[0]; // get the first character of the line
        char *longLine = malloc(sizeof(char) * MAX_LINE);
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
               longLine[i] = string[i];
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
        } else if (((firstCh != '>') && ((isalpha(firstCh))) || isdigit(firstCh))) {
            /* dependency declarations */
            count = 0;
            char* depend = malloc(sizeof(char) * read);
            d = malloc(sizeof(char) * read);
            
            for (int a = 0; a < read; a++) {
                if(string[a] == ':')
                    colon = true;
            }
            
            if (colon == false) {
                fprintf(stderr, "%d%s%s\n", linenum, ": Invalid line format : ", string);
                exit(1);
            } else {
                // find target name
                name = strtok(string,":");
            }
            
            /* if there is no target name */
            if (name == NULL) {
                // error
                fprintf(stderr, "%d%s%s\n", linenum,": No valid target name : ", string);
            }

            strcpy(depend, name);
            
            /* if target is valid */
            while(depend != NULL) {
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
                if (count!=0) d[count-1] = depend;
                count++;
            }
        } else if (firstCh == '>') {
            /* command declarations */
            count2 = 0;
            num_commands++;
            char *command = malloc(sizeof(char) * read);
            c = malloc(sizeof(char) * read);
            string_without_tab = malloc(sizeof(char) * read);
            
            /* get the first 4 characters of the line */
            for (int j = 0; j < 4; j++) {
                tab[j] = string[j];
            }

            /* if tab isn't equal to the correct tab characters */
            if (strcmp(tab, tab_chars) == 0) {    
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
            Target *t = create(name, d, count-1, c, num_commands);
    	    target_list[numTargets] = t;
	        numTargets++;
            *num_targets= numTargets;
	     
            // reset number of command lines
            num_commands = 0;
        }
    }
    fclose(makefile);
}
