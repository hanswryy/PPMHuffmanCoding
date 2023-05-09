#ifndef huffman_h
#define huffman_h

// C++ Program for Huffman Coding
// using Priority Queue
#include <iostream>
#include <queue>
#include <stdio.h>
#include "HuffmanTreeNode.h"
#include "Compare.h"
#include <bitset>
#include <fstream>
#include <string.h>
#include "PPMReader.h"

using namespace std;

// Maximum Height of Huffman Tree.
#define MAX_SIZE 100


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


HuffmanTreeNode* giveTree(unsigned char (*data)[3],
				int freq[], int size, int * arrsize);

void encodeHuffman(HuffmanTreeNode* root, unsigned char header[], unsigned char *image, int size, char filename[]);

void encodeTree(HuffmanTreeNode* root, FILE* file);

HuffmanTreeNode *treeisBack(FILE *read);

void decodeHuffman(unsigned char *image, unsigned char header[], int size, char filename[]);

void readHeader(FILE *read, unsigned char header[]);

void fixEncode(unsigned char* image, int size);

void ConvertHuffman(HuffmanTreeNode* root, unsigned char *image, int size, char filename[]);

void Traverse(HuffmanTreeNode** root, char c, unsigned char info[3]);

void Encode(char filename[]);

void Decode(char filename1[]);

#endif