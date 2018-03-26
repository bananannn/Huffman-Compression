#include "HCTree.h"
#include "HCNode.h"

#include <iostream>
#include <queue>
#include <vector>
#include <fstream>
#include <string>
/*
 * Name: Bananannn
 */
/*
 * Function name: main
 * Function prototype: int main( int argc, char** argv );
 * Description: This function will uncompress the characters
 * in the input file by decoding the characters based on the
 * header on the top and then write them to the output file.
 */
int main( int argc, char** argv ){
    // check whether the program has enough input arguments
    if( argc !=  3){
        std::cout<<"Not enough input arguments" << std::endl;
    }
    // Read the input arguments
    std::string infile = argv[1];
    std::string outfile = argv[2];
    HCTree tree;
    std::ifstream stream;
    stream.open(infile, ios::binary);
    //std::vector<int> freqs;
    // get the size of the characters
    stream.seekg(0, stream.end);
    int length = stream.tellg();
    stream.seekg(0,stream.beg);
    int count = 0;
    
    // Rebuild the coding tree based on the header
    std::ofstream outstream;
    outstream.open(outfile, ios::binary);
    
    // bitwisely read all the characters
    BitInputStream inStream = BitInputStream(stream);
    BitOutputStream outStream = BitOutputStream(outstream);
    
    int total;
    // get the number of leaves and the total number
    // of characters from the header
    stream.read((char*)&total, sizeof(total)); 
    int headersize;
    stream.read((char*)&headersize, sizeof(headersize));
    //std::cout<<"Found "<<numLeaves<<"unique symbols in inputfile"<<std::endl;
    
    // Read the header from the input file
    int read = 0;
    char curr; 
    vector<char> header;
    //while( numLeaves != read ){
    while(read<headersize){
        curr = stream.get();
        header.push_back(curr);
        read+=1;
    }
    
    // Rebuild the tree according to the header
    tree.HCTree::rebuild(header, header.size());
    std::cout<<"Building Huffman code tree. Done"<<std::endl;
    HCNode* root = tree.getRoot();
   
    // Read the remaining data and decode
    std::cout<<"Writing to output file... "<<std::endl;
    while( total != 0 ){
        // if reaches the end of the input file
        if(stream.eof()){
            break;
        } 
        // decode the file
        if( tree.getRoot() == nullptr ){
            std::cout<<"Please check: the tree is empty" << std::endl;
            return 0;
        }
        byte symbol = tree.HCTree::decode(inStream);
        // if the decode cannot work properly
        if( symbol == -1 ){
            std::cout<<"Exit decoding"<<std::endl;
            break;
        }
        // Write the decoded message to the output file
        outStream.writeByte(symbol); 
        total -= 1;
    }
    std::cout<<"done."<<std::endl;
    stream.close();
    outstream.close();
    return 0;
}
