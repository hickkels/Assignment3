/* parse  lines in the makefile
* splits line into an array of strings
* check whether a line begins with tab or regular char
* filters out blank line
*/

#include <stdio.h>
#include "textparser.h"

// 15
static int MAX_LINE = 4096;

void parse_makefile() {
    char *string = NULL; // initial string set to NULL
    size_t len = 0; // initial size of string
    char ch, firstCh; // character to be iterated and read in from stdin
    char * token = strtok(string, " ");
    
    FILE *makefile;
    char *make = argv[1];

    makefile = fopen(input, "r");
    
    if (input_file == 0) {
        fprintf(stderr, "Canot open makefile\n");
        exit(-1);
    }

    ch = (char) fgetc(makefile);
    while (EOF != ch) {
        // 10
        // if line doesn't start with a target name or tab (getline/readline) -> error
        // if it does then continue
        while (ch != '\n') {
            if (ch == '\t') {
                // if first character is a tab    
                            
            } else if (ch == '#') {
                // 8

            } else if (ch == '\0') {
                // 9
                // print error and exit
            } else {
                // if first character is not a tab
                // add character to line string    
                string[len++] = ch;
                ch = (char) fgetc(makefile);
            }
        }
        if (string == NULL) {
            // 7
            // line is empty disregard it
        }
        i++;
    }
    // while character iterated is not the end of line character
        while ((ch != '\n') && (characters<MAX_BUFF)) {
            string[len++] = ch; // read in characters and set equal to corresponding position
            characters++; // increment character count of string
            ch = (char) fgetc(stdin);
        }
        // if input line exceeds buffer size
        if ((characters==MAX_BUFF) && (ch != '\n')) {
            fprintf(stderr, "Input line has exceeded buffer length.\n"); // print error
            // flush to end of live any remaining characters on that line
            while ('\n' != ch) ch = (char) fgetc(stdin);
        } else {
            if (string != NULL)
                EnqueueString(reader_to_munch1, string); // pass line to queue
        }
        ch = (char) fgetc(stdin);
        len = 0;
    characters = 0;
        string = NULL;
    }

}
