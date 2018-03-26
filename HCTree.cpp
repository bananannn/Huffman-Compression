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
/**
 * ICONDITION: freqs is a vector of ints, such that freqs[i] is 
 * the frequency of occurrence of byte i in the message.
 * POSTCONDITION:  root points to the root of the trie,
 * and leaves[i] points to the leaf node containing byte i.
 */
void HCTree::build(const vector<int>& freqs){
    /*// If the input argument is null,
    if( freqs == nullptr ){
        return;
    }*/
    // create a priority queue which can sort all the data
    // and arrange them from the low frenquency to high frenquency node
    std::priority_queue<HCNode*,std::vector<HCNode*>,HCNodePtrComp>
    priQueue;
    HCNode* newRoot;
    int sign = 0;
    for( int i = 0; i<256; i++ ){
        //HCNode* current = new HCNode(freqs[i], i, 0, 0, 0);
        //leaves[i] = current; 
        // Only push the strings which frequency is not 0
        if( freqs[i] != 0 ){
            HCNode* current = new HCNode(freqs[i], i, 0, 0, 0);
            priQueue.push(current);
            leaves[i] = current;
        }
    }
    // The while loop will get each of the element in the priority queue
    while( 1<priQueue.size() ){
        HCNode* curr = priQueue.top();
        priQueue.pop();
        HCNode* nextCurr = priQueue.top();
	priQueue.pop();
        // The root of the new big tree
        byte sym = 0;
        if( curr->symbol > nextCurr-> symbol ){
            sym = curr->symbol;
        }
        else{
            sym = nextCurr->symbol;
        }
        int sum = nextCurr->count + curr->count;
        // Use the collected info to create the new node
        newRoot = new HCNode(sum, sym, 0, 0, 0);
        newRoot->c1 = curr;
        curr->p = newRoot;
        newRoot->c0 = nextCurr;
        nextCurr->p = newRoot;
        // Adding the new node onto the priority queue
        priQueue.push(newRoot);
        sign = 1;
    }
    // If the tree only has one child, then update the root
    if( priQueue.size() == 1 && sign != 1){
        HCNode* topone = priQueue.top();
        root = new HCNode(topone->count, 0, topone, 0, 0);
        topone->p = root;
    }
    else{
        // update the root in the end
        if( priQueue.size() != 0 ){ 
            root = priQueue.top();
            priQueue.pop();
        }
    }
}

/*
 * Function: rebuild
 * Function prototype: void rebuild(vector<char>& header, int max);
 * Description: This function uses the header to rebuild the tree
 * It basically reverse the result of a tree's preorder traversal.
 * input: the header and the header's size
 * output: void
 */
void HCTree::rebuild( vector<char>& header, int max){
    int index = 1;
    root = new HCNode(0, 0, 0, 0, 0);
    HCNode* curr = root;
    // Stop when there is no more unread characters in the header
    while( index < max ){
        //std::cout<<"index: "<<index<<std::endl;
        // if the header indicate 1, it means the node connect
        // to the parent is a dummy node which does not have
        // useful information
        if( header[index] == '1' ){
            //HCNode* newnode = new HCNode(0,0,0,0,curr);
            if( curr->c1 == nullptr ){
                HCNode* newnode = new HCNode(0,0,0,0,curr);
                // update the left node accordingly
                curr->c1 = newnode;
                curr = newnode;
                index+=1;
            }
            else if( curr->c0 == nullptr ){
                HCNode* newnode = new HCNode(0,0,0,0,curr);
                // update the right node accordingly
                curr->c0 = newnode;
                curr = newnode;
                index+=1;
            }
            // if the parent node already has two child 
            else if( curr->c1 != nullptr && curr->c0 != nullptr ){
                if(curr->p != nullptr){
                    curr = curr->p;
                }
            }
        }
        // If the header has 0, it means the connected node is a
        // "useful" node
        else if( header[index] == '0' ){
            //HCNode* newnode = new HCNode(0,header[index+1],0,0,curr);
            // Update the left and right child accordingly
            if( curr->c1 == nullptr ){
                HCNode* newnode = new HCNode(0,header[index+1],0,0,curr);
                curr->c1 = newnode;
                index += 2;
            }
            else if( curr->c0 == nullptr ){
                HCNode* newnode = new HCNode(0,header[index+1],0,0,curr);
                curr->c0 = newnode;
                index += 2;
            }
            // if the parent node already has two child 
            else if( curr->c1 != nullptr && curr->c0 != nullptr ){
                if( curr->p != nullptr ){
                    curr = curr->p;
                }
            }
        }
    }
}

/**
 * the sequence of bits coding the given symbol.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 */
/*void HCTree::encode(byte symbol, ofstream& out) const{
    HCNode* current = leaves[symbol];
    int i = 0;
    std::string str;
    while( current->p != nullptr ){
        HCNode* currPar = current->p;
        if( currPar->c0 == current ){
            str += "0";
        }
        else{
            str += "1";
        }
        current = current->p;
    }
    reverse(str.begin(), str.end());
    long int size = str.size();
    char* buffer = new char[size];
    for(long int i =0; i<size; i++){
        buffer[i] = str.at(i);
    }
   
    
    out.write(buffer, size);
}*/

/**
 * the sequence of bits coding the given symbol.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 */
void HCTree::encode(byte symbol, BitOutputStream& out) const{
    HCNode* current = leaves[symbol];
    int i = 0;
    std::string str;
    // traverse up to the root
    while( current->p != nullptr ){
        HCNode* currPar = current->p;
        // Update the 0 and 1 accordingly
        if( currPar->c0 == current ){
            str += "0";
        }
        else{
            str += "1";
        }
        current = current->p;
    }
    // Reverse the sequence
    reverse(str.begin(), str.end());
    long int size = str.size();
    // write the encoded info to the output file
    for(long int i =0; i<size; i++){
        int input = str.at(i) - '0';
        out.writeBit(input);
    }
}

/**
 *  Return symbol coded in the next sequence of bits from the stream.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector. 
 */
/*int HCTree::decode(ifstream& in) const{
    char curr;
    int i = 0;
    HCNode* current = root;
    if( root == nullptr ){
         return -1;
    }
    while( 1 ){
        in >> curr;
        if( current->c1 == nullptr && current->c0 == nullptr ){
            return current->symbol;
        }   
        if( curr != '0' && curr != '1' ){
            return -1;
        }
        if( curr == '0' ){
            current = current->c0;
            i++;
        }
        else{
            current = current->c1;
            i++;
        }
	
    }
}*/

/**
 *  Return symbol coded in the next sequence of bits from the stream.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector. 
 */
byte HCTree::decode( BitInputStream& in) const{
    unsigned int curr = 0;
    int i = 0;
    HCNode* current = root;
    while( 1 ){
        // get the character in the header
        curr = in.readBit();
        if( curr == EOF ){
            break;
        }
        // if the character is not 0 or 1
        if( curr != 0 && curr != 1 ){
            return -1;
        }
        // if 0, go to the right child
        if( curr == 0 ){
            current = current->c0;
            i++;
        }
        // if 1, go to the left child
        else{
            current = current->c1;
            i++;
        }
        // if it is a leaf, return the symbol 
        // the symbol is the decoded info
        if( current->c1 == nullptr && current->c0 == nullptr ){
            return current->symbol;
        }   
	
    }

}
/*
 * Function: getLeaves
 * Description: used to get the leaves vector 
 * It is used in the compress file.
 */
vector<HCNode*> HCTree::getLeaves(){
    /*std::cout<<"00"<<root->c0->c0->symbol<<std::endl;
    std::cout<<"01"<<root->c0->c1->symbol<<std::endl;
    std::cout<<"10"<<root->c1->c0->symbol<<std::endl;
    std::cout<<"11"<<root->c1->c1->symbol<<std::endl;*/
    return leaves;
}

/*
 * Helper function used in the compress used to draw the 
 * header tree
 */
void HCTree::preorder(HCNode* n, vector<char>& drawTree){
    if( n == nullptr ){
        return;
    }
    // if it is one leaf, record the node as 0
    // and also record the character
    if( n->c1 == nullptr && n->c0 == nullptr ){
        drawTree.push_back('0');
        drawTree.push_back((char) n->symbol);
    }
    else{
        drawTree.push_back('1');
    }
    // traverse to the left
    preorder(n->c1, drawTree);
    // traverse to the right
    preorder(n->c0, drawTree);
} 

/*
 * Function: getRoot
 * Description: used to find the root
 */
HCNode* HCTree::getRoot(){
    return root;
}

// Memory destructor
HCTree::~HCTree(){
    //if( root != nullptr){
    //delete root->c1;
    //delete root->c0;
    //}
    deleteAll(root); 
        
}

// Helper function of the destructor
void HCTree::deleteAll(HCNode* node){
  if( node == nullptr ){
      return;
  }
  // delete the left branches first
  if( node->c1 != nullptr ){
      deleteAll(node->c1);
  }
  // then delete the right banches 
  if( node->c0 != nullptr ){
      deleteAll(node->c0);
  }
  delete(node);
}


