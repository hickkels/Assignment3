/* represents dependencies between build specifications
* traverses the graph in bottom-up order
*/

#include "buildrep.h"
#include<stdio.h>

/*
* build the graph that represents dependencies between build specifications
* 
* ERROR IF THERE IS A CYCLE
*/
void buildGraph(Target *target_list) {

    int stackSize = 4096;  // CHANGE THIS...to num of targets?
    char stack[stackSize];
    int stackTop = -1;  // negative index means empty

}

void push(char stack[], int *stackTop, int stackSize, Target *target){
    if (*stackTop==0) {
        printf("stack is full, change stack implementation to total num targets\n");
    } else if(*stackTop==-1){
	stack[stackSize - 1] = element;
    	*top = stackSize - 1;
    } else{
        stack[(*top) - 1] = element;
	(*top)--;
    }
}

void pop(char stack[], int *stackTop, int stackSize){
    if(*stackTop==-1){
	printf("Tried to pop, empty stack.\n");
    } else{
  	printf("Popped: %c \n", stack[(*top)]);
    	// if we popped last element, move size around to -1
	if((*top)==stackSize - 1){
    	    (*top) = -1;
    	} else{
    	    (*top)++;
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
bool traverseGraph(Target *t) {

    // BASE CASE: node has no dependencies
    if (t->dependencies==NULL) {
	t->visited=0; // set visited equal to zero
	return false;
    }

    // RECURSIVE CASE: call traverse on each of a nodes dependencies
    // visit current node (root)
    t->visited=1;
    for (int i=0; i<t->num_dependencies; i++) {
	Target *curr = getTarget(t->dependencies[i]; 
        // check if child is already visited and return true if yes
        if (curr->visited==1) return true;
	traverseGraph(curr);
    }
}

Target *getTarget(char *name) {

    // iterate through each target checking for the name
    

}
