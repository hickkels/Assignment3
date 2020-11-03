/*
Cecelia Peterson: cpeterson36@wisc.edu, 9073157274
Kelsey Hickok: khickok@wisc.edu, 9076435016
*/
#ifndef FILE_REP_H_
#define FILE_REP_H_
#include<time.h>

typedef struct File
{
    char *name;
    int visited;
} File;

File *create_file(char *name);
int file_visited(File *f, File **file_list, int num_files);

#endif // FILE_REP_H
