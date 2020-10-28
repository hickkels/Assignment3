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

// 15
static int MAX_LINE = 4096;

int main(void)
{
    char ** output;
    int k = 0;
    while (k <= 5) {
        output = parse_makefile();
        printf("%s", *output);
    }
    return 0;
}

// TODO:
// pass in size of array
char** parse_makefile() {
    char *line = NULL;
    char *longLine;
    char **array[MAX_LINE];
    // char *newString[] = NULL;
    char **section = NULL;
    size_t len = 0; // initial size of string
    char firstCh; // character to be iterated and read in from stdin
    ssize_t read;
    int count, count2, i;
    int linenum = 0;
    int iterator = 0;
    FILE *makefile;
    struct stat buffer;
        
    makefile = fopen("/u/h/i/hickok/private/OS/Assignment3/makefile", "r"); // open makefile
    
    // check if makefile is a valid file
    if (makefile == NULL) {
        fprintf(stderr, "Cannot open makefile, invalid file.");
        exit(1);
    }

    // get lines in makefile
    while ((read = getline(&line, &len, makefile)) != -1) {
        firstCh = line[0];
        linenum++;
        *array = malloc(sizeof(char) * read);
        
        printf("%s", line);    
        // if line is too long
        if (read > MAX_LINE) {
            fprintf(stderr, "%d%s", linenum, ": Line count too long: ");
            i = 0;
            while (i < MAX_LINE) {
               longLine[i] = fgetc(makefile);
            }
            printf("%s\n", longLine);
            exit(1);
            i++;
        }
    
        // 9        
        // search for null character and semicolon to get target
        for (int i=0; i<read; ++i) {
            if (line[i] == '\0') {
                fprintf(stderr, "%d%s%s", linenum, ": Null character found: ", line);
                exit(1);
            }            
        }    
   
        // 8
        // if comment line 
        if (firstCh == '#') {
            // ignore rest of line
            continue;
        } else if ((firstCh != ' ') && ((isalpha(firstCh)) || isdigit(firstCh))) {
            // 3
            // if target is valid
            count = 0;
            char** depend = malloc(sizeof(char) * read);
            *depend = strtok(line,":"); // find target name
            if (*depend == NULL) {
                fprintf(stderr, "%d%s%s\n", linenum,": No target name, invalid line: ", line);
                exit(1);
            }
            while(*depend != NULL) {
                *depend = strtok(NULL, " ");
                /* get each string and check to see if valid dependency
                // disregard right now
                if (stat (*depend, &buffer) != 0) {
                    fprintf(stderr, "%d%s%s\n", linenum,": Dependency not valid: ", line);
                    exit(1);
                }
                */
                //array[count] = *depend;
                printf("%s%s\n", "Dependency: ", *depend);
                count++;
            }
            // return **array[count];

        } else if (firstCh == ' ') {
            // command line stuff
            count2 = 0;
            char **command = malloc(sizeof(char) * read);
            // TODO:
            // edit space/tab character
            // fix NULL in strtok
            *command = strtok(line, " ");
            while(*command != NULL) {
                *command = strtok(NULL, " ");
                //**array[count2] = *command;
                printf("%s%s\n", "Command: ", *command);
                count2++;
            }
            // return **array[count2];
        } else if (firstCh == '\n') {
            // 7
            // if blank line disregard it
            continue;
        } else {
            // 10
            // if line doesn't start with a target name or tab 
            fprintf(stderr, "%d%s%s\n", linenum, ": Invalid line format: ", line);
            exit(1);
        }
    }
    fclose(makefile);
    return 0;
}
