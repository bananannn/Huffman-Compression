#include "HCTree.h"
#include "HCNode.h"
#include<bits/stdc++.h>
#include <iostream>
#include <queue>
#include <vector>
#include <fstream>
   
/*
 * Name: Bananannn
 */

/*
 * Function name: fill()
 * Description: filling the buffer by updating the bits and
 * reading from the input file
 */
void BitInputStream::fill(){
    buffer = in.get();
    bit = 0;
}

/*
 * Function name: readBit()
 * Description: read the input file bit by bit.
 */ 
unsigned int BitInputStream::readBit(){
    if(bit == 8){
        fill();
    }
    // update the bit and write in the buffer
    unsigned int next = (buffer & (1 << (7-bit))) >> (7-bit);
    bit++;
    return next;
}

/*
 * get the length of the file
 */
int BitInputStream::getLength(){
    return length;
}

