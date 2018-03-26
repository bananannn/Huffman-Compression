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
 * All the templates of the classes are credicted to the stepik book
 * The website is: https://stepik.org/lesson/31729/step/6?unit=11913
 */
class BitOutputStream{
    private:
        unsigned char buffer;    // one byte used to store the bit
        int bit;                 // number of byte which has been written
        ostream & out;           // the output file
    public:
        /*
         * The constructor used to initialize the buffer, bit and
         * output stream
         */ 
        BitOutputStream(ostream & osf): out(osf), buffer(0), bit(0){}

        /*
         * Write the buffer to the output stream and then clear the buffer
         */
        void flush();

        /*
         * Write each individual bit onto the buffer
         */
        void writeBit(unsigned int obit);
        
        /*
         * Write one byte to the output stream
         */
        void writeByte(char input);
};
