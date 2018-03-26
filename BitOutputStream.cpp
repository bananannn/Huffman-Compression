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
 * Write the buffer to the output stream and then clear the buffer
 */
void BitOutputStream::flush(){
    out.put(buffer);
    // clear the buffer
    out.flush();
    buffer = 0;
    bit = 0;
    
}

/*
 * Write each individual bit onto the buffer
 */
void BitOutputStream::writeBit(unsigned int obit){
    if(bit == 8){
        flush();
    }
    // set the 1 to the corresponding location in the buffer
    if( obit == 1 ){
        buffer = (buffer | (buffer|(obit<<(7-bit))));
    }
    // set the 0 to the corresponding location in the buffer
    else{
        buffer = (buffer & (~(obit << bit )));
    }
        
    bit++;
}

/*
 * Write one byte to the output stream
 */
void BitOutputStream::writeByte(char input){
    out.put(input);
}
    
