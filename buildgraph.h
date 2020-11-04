/*
Cecelia Peterson: cpeterson36@wisc.edu, 9073157274
Kelsey Hickok: khickok@wisc.edu, 9076435016
*/
#ifndef BUILD_GRAPH_H
#define BUILD_GRAPH_H_
#include<time.h>
#include "buildrep.h"

int buildGraph(Target **target_list, int num_targets);
void push(char stack[], int *stackTop, int stackSize, Target *target);
void pop(char stack[], int *stackTop, int stackSize);
int traverseGraph(Target *t, Target **target_list, int num_targets);
Target *findTarget(char *name, Target **target_list, int *num_targets);

#endif // BUILD_GRAPH_H
