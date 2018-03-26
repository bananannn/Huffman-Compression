#include "HCTree.h"
#include "HCNode.h"
#include <iostream>
#include <queue>
#include <vector>
#include <fstream>
#include <string>
/*
 * Function name: main
 * Function prototype: int main( int argc, char** argv );
 * Description: This function will compress all the characters
 * in the input file and then write them to the output file.
 */
int main( int argc, char** argv ){
    if( argc != 3 ){
        std::cout<<"not enough arguments"<<std::endl;
    }
    std::string infile = argv[1];
    std::string outfile = argv[2];
    HCTree tree;
    int total = 0;
    std::vector<int> freqs;
    std::ifstream stream;
    //BitInputStream(stream);
    stream.open(infile, ios::binary);
    /* The algrithm of getting lengthes is learned by browsing the 
     * http://www.cplusplus.com/reference/istream/istream/read/
     */
    stream.seekg(0, stream.end);
    int length = stream.tellg();
    stream.seekg(0, stream.beg);
    for( int i=0; i<256; i++){
        freqs.push_back(0);
    }
       
    // Read all the data in the input file
    char next;
    // Read characters from the input file
    // to create the freqs vector used in building the coding tree
    while( stream.get(next) != false ){
        byte sym = 0;
        sym = (byte)next;
        freqs[sym] += 1;
    }
    // calculate the number of bytes that should be decoded
    for( int i = 0; i<freqs.size(); i++){
        total += freqs[i];
    }
    // Count the number of leaves
    int numLeaves = 0;
    for( unsigned int i =0; i<freqs.size(); i++){
        if( freqs[i] != 0 ){
            numLeaves++;
        }
    }
    std::cout<<"Uncompressed file will have "<<numLeaves<<
    " unique symbols"<<std::endl;
    stream.close();

    // Build the coding tree
    tree.HCTree::build(freqs);
    std::cout<<"Building Huffman code tree... done."<<std::endl;
    
    // Prepare for adding information to the output file
    std::ofstream outstream;
    outstream.open(outfile);

    // Building the header
    HCNode* root = tree.getRoot();
    vector<char> header;
    tree.HCTree::preorder(root, header);
    
    // Encode all the characters in the file
    stream.open(infile, ios::binary);
    stream.seekg(0, stream.beg);
    BitOutputStream outStream = BitOutputStream(outstream);
    int headersize = header.size();
    // Record the total characters in the input file
    // And the number of leaves in the coding tree
    outstream.write((char*)&total, sizeof(total)); 
    outstream.write((char*)&headersize, sizeof(headersize));
    
    // Start writing
    std::cout<<"Writing to file... done."<<std::endl;
    // put the header above the encoded information
    for(unsigned int i = 0; i<header.size(); i++){
        outStream.writeByte(header.at(i));
    }
     
    while( length != 0 ){
        if(stream.eof()){
            break;
        }
        //byte sym = 0;
        //stream >> sym;
        unsigned char ch;
        ch = stream.get();
        tree.HCTree::encode(ch, outStream);
        length -= 1;
    }
    outStream.flush();
    stream.close();
    outstream.close();
    return 0;
}
