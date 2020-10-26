/* parse lines in the makefile
* splits line into an array of strings
* check whether a line begins with tab or regular char
* filters out blank line
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>   // stat
#include "textparser.h"

// 15
static int MAX_LINE = 4096;

char** parse_makefile() {
    char *line = NULL;
    char *longLine = NULL;
    char *command = NULL;
    char *dependency = NULL;
    char **section = NULL;
    size_t len = 0; // initial size of string
    char firstCh; // character to be iterated and read in from stdin
    ssize_t read;
    int count, count2, i;
    int linenum = 0;
    int iterator = 0;
    FILE *makefile;
    struct stat buffer;
        
    makefile = fopen("/etc/motd", "r"); // open makefile
    
    // check if makefile is a valid file
    if (makefile == NULL) {
        fprintf(stderr, "Cannot open makefile, invalid file.");
        exit(1);
    }

    // get lines in makefile
    while ((read = getline(&line, &len, makefile)) != -1) {
        firstCh = line[0];
        char * target;
        linenum++;
        
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
            } else if (line[i] == ':') {
                // 1
                // get target name
                target = strtok(line, ":");
            }            
        }    
   
        // 8
        // if comment line 
        if (firstCh == '#') {
            // ignore rest of line
            continue;
        } else if ((firstCh != '\t') && (stat (target, &buffer) == 0)) {
            // 3
            // if target is valid
            count = 0;
            while(count <= read) {
                dependency = strtok(line, " ");
                // get each string and check to see if valid dependency
                if (stat (dependency, &buffer) != 0) {
                    fprintf(stderr, "%d%s%s", linenum,": Dependency not valid: ", line);
                    exit(1);
                }
                section[count] = dependency;
                count2++;
            }
        } else if (firstCh == '\t') {
            // command line stuff
            count2 = 0;
            iterator = count + 1;
            while(count2 <= read) {
                command = strtok(line, " ");
                section[iterator] = command;
                count2++;
                iterator++;
            }
        } else {
            // 10
            // if line doesn't start with a target name or tab
            fprintf(stderr, "%d%s%s\n", linenum, ": Invalid line format: ", line);
            exit(1);
        }
        
        // 7
        // if blank line
        // disregard it but pass parsed strings to graph
        if (line == NULL) {
            return section;   
        
        } 
    }
    return 0;
}
