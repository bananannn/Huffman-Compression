#include "HCTree.h"
#include "HCNode.h"

#include <iostream>
#include <queue>
#include <vector>
#include <fstream>
   
/*
 * Name: Bananannn
 */

/*
 * Function name: operator<
 * Description: this function is used in the priority queue
 * in order to identify the priority of each node
 * Input: const HCNode& other: the node used to compare
 * Return value: true if the one call the function has
 * lower priority
 */
bool HCNode::operator<(const HCNode& other){
    // If the count is the same, return true
    // if the symbol is larger
    if( count  == other.count ){
        if( symbol < other.symbol ){
            return true;
        }
        return false;
    }
    // return true if the count is smaller
    // since nodes with smaller counts will have
    // higher priority
    else{
        // if the node has smaller counts, return false
        if( count < other.count ){
            return false;
        }
        return true;
    }
}


/*
std::priority_queue<HCNode*, std::vector<HCNode*>, compare> priQueue;

bool compare::operator()( HCNode* n1, HCNode* n2 ){
    return (*n1).operator<(*n2);
}*/
