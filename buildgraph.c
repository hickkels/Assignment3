/* represents dependencies between build specifications
* traverses the graph in bottom-up order
*/

#include "buildgraph.h"
#include "buildrep.h"
#include <stdio.h>
#include <stdbool.h>

/*
* build the graph that represents dependencies between build specifications
* 
* ERROR IF THERE IS A CYCLE
*/
int buildGraph(Target **target_list, int num_targets) {

    int total = 0;
    int stackSize = num_targets;  // CHANGE THIS...to num of targets?
    Target *stack[stackSize];
    int stackTop = -1;  // negative index means empty
    for (int i=0; i<num_targets; i++) {
	Target *toCheck = target_list[i];
	total = total + traverseGraph(toCheck, target_list, num_targets);
    }
    return total;
}

void push(char stack[], int *stackTop, int stackSize, Target *target){
    if (*stackTop==0) {
        printf("stack is full, change stack implementation to total num targets\n");
    } else if(*stackTop==-1){
	stack[stackSize - 1] = target;
    	*stackTop = stackSize - 1;
    } else{
        stack[(*stackTop) - 1] = target;
	(*stackTop)--;
    }
}

void pop(char stack[], int *stackTop, int stackSize){
    if(*stackTop==-1){
	printf("Tried to pop, empty stack.\n");
    } else{
  	printf("Popped: %c \n", stack[(*stackTop)]);
    	// if we popped last element, move size around to -1
	if((*stackTop)==stackSize - 1){
    	    (*stackTop) = -1;
    	} else{
    	    (*stackTop)++;
    	}
    }
}

/*
* traverse the graph in a bottom-up order to evaluate the specificiations
* using a post-order traversal (recursion)
*
* -going to call on each target
* -call recursively on each node in array of dependencies
* -return true if dependency, otherwise false
*/
int traverseGraph(Target *t, Target **target_list, int num_targets) {

    // BASE CASE: node has no dependencies
    if (t->num_dependencies==0) {
	t->visited=0; // set visited equal to zero
	return false;
    }

    // RECURSIVE CASE: call traverse on each of a nodes dependencies
    // visit current node (root)
    t->visited=1;
    for (int i=0; i<t->num_dependencies; i++) {
	Target *curr = findTarget(t->dependencies[i], target_list, num_targets); 
        // check if child is already visited and return true if yes
        if (curr->visited==1) return true;
	traverseGraph(curr, target_list, num_targets);
    }
}

Target *findTarget(char *name, Target **target_list, int *num_targets) {

    for (int i=0; i<num_targets; i++) {
        Target *curr = target_list[i];
        if (strcmp(target_list[i]->name, name)==0) return curr;
    }       

}
