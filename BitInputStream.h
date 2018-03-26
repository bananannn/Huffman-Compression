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
class BitInputStream{
    private:
        unsigned char buffer; //One byte used to store the bits
        int bit;              // number of bits read
        istream& in;          // the input stream
    public:
        int length;           // the length of a file
        
        /*
         * Description: the constructor used to assign the initial
         * value of the buffer, bit and input file.
         */
        BitInputStream(istream & inf): in(inf), buffer(0), bit(8) {}
        
        /*
         * Function name: fill()
         * Description: filling the buffer by updating the bits and
         * reading from the input file
         */
        void fill();

        /*
         * Function name: readBit()
         * Description: read the input file bit by bit.
         */ 
        unsigned int readBit();

        /*
         * get the length of the file
         */
        int getLength();
};

