#include "buildrep.h"

#ifndef PROC_CREATE_H_   /* Include guard */
#define PROC_CREATE_H_

void run_command(Target *target, Target *target_array, int *num_targets);
int create_process(char *argv[]);

#endif // PROC_CREATE_H
