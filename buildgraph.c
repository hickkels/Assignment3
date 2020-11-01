/* represents dependencies between build specifications
* traverses the graph in bottom-up order
*/

#include "buildrep.h"

/*
* build the graph that represents dependencies between build specifications
* 
* ERROR IF THERE IS A CYCLE
*/
void buildGraph(Target *target_list) {

    

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
	t->visited=0;
	return false;
    }

    // RECURSIVE CASE: call traverse on each of a nodes dependencies
    for (int i=0; i<t->num_dependencies; i++) {
        // visit current node (root)
	Target *curr = 
            // set visited to 1
    }

}

Target *getTarget(char *name) {

    // iterate through each target checking for the name

}
