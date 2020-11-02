/*
Cecelia Peterson: cpeterson36@wisc.edu, 9073157274
Kelsey Hickok: khickok@wisc.edu, 9076435016
*/
#ifndef BUILD_REP_H_
#define BUILD_REP_H_

typedef struct Target
{
    char *name;
    char *dependencies;
    int num_dependencies;
    char **command_lines;
    int num_command_lines;
    int visited;
    time_t modTime;
} Target;

Target create(char** dependencies, char** commands, int num_commands);
void update(); // from writeup, don't do anything yet
void access(); // from writeup, don't do anything yet

#endif // BUILD_REP_H
