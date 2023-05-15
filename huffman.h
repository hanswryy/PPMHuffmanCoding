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
void writeCodetoFile(HuffmanTreeNode* root,
				int arr[], int top);


HuffmanTreeNode* buildHuffmanTree(unsigned char (*data)[3],
				int freq[], int size, int * arrsize);

void encodeHuffman(HuffmanTreeNode* root, unsigned char header[], unsigned char *image, int size, char filename[]);

void encodeTree(HuffmanTreeNode* root, FILE* file);

HuffmanTreeNode *rebuildTree(FILE *read);

void decodeHuffman(unsigned char *image, unsigned char header[], int size, char filename[]);

void readHeaderFromFile(FILE *read, unsigned char header[]);

void writeEncoded(unsigned char* image, int size, char filename[]);

void ConvertCodetoData(HuffmanTreeNode* root, unsigned char *image, int size, char filename[]);

void TraverseTree(HuffmanTreeNode** root, char c, unsigned char info[3]);

void printTree(HuffmanTreeNode* root, int arr[], int top);

void Encode(char filename[]);

void Decode(char filename1[]);

#endif