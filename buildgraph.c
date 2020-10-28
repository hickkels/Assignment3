/* represents dependencies between build specifications
* traverses the graph in bottom-up order
*/

#include "buildrep.h"

/*
* build the graph that represents dependencies between build specifications
* 
* ERROR IF THERE IS A CYCLE
*/
void buildGraph() {



}

/*
* traverse the graph in a bottom-up order to evaluate the specificiations
* using a post-order traversal (recursion)
*
* -going to call on each target
* -call recursively on each node in array of dependencies
* 
*/
void traverseGraph() {

    // BASE CASE: node has no dependencies
	// set visited to 0

    // RECURSIVE CASE: call traverse on each of a nodes dependencies

    // visit current node (root)
	// set visited to 1

}
