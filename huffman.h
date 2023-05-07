#ifndef huffman_h
#define huffman_h

// C++ Program for Huffman Coding
// using Priority Queue
#include <iostream>
#include <queue>
#include "HuffmanTreeNode.h"
#include "Compare.h"

using namespace std;

// Maximum Height of Huffman Tree.
#define MAX_SIZE 10000

// Function to generate Huffman
// Encoding Tree
HuffmanTreeNode* generateTree(priority_queue<HuffmanTreeNode*,
							vector<HuffmanTreeNode*>,
											Compare> pq);

// Function to print the
// huffman code for each
// character.

// It uses arr to store the codes
void printCodes(HuffmanTreeNode* root,
				int arr[], int top);

void HuffmanCodes(unsigned char (*data)[3],
				int freq[], int size);


#endif