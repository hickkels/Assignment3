
#ifndef TEXT_PARSER_H_   /* Include guard */
#define TEXT_PARSER_H_

#include <stdio.h>
#include "buildrep.h"

char** parse_makefile(FILE* makefile, int *num_targets, Target **target_list);

#endif // TEXT_PARSER_H
