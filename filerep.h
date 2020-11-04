/*
Cecelia Peterson: cpeterson36@wisc.edu, 9073157274
Kelsey Hickok: khickok@wisc.edu, 9076435016
*/
#ifndef FILE_REP_H_
#define FILE_REP_H_
#include<time.h>
#include "buildrep.h"

typedef struct File
{
    char *name;
    int visited;
} File;

File *create_file(char *name);
int file_visited(char *name, File **file_list, int num_files);
int count_files(Target **target_list, int num_targets);
int createFileStructs(File **file_list, int file_count, Target **target_list, int *num_targets);
int fileExists(File **file_list, int file_count, char *name);

#endif // FILE_REP_H
