/*	
Program		: body_huffman.cpp
Deskripsi	: Header untuk ADT Huffman Code pada kompresi gambar
Dibuat oleh :
            - Farhan Muhammad Lutfhi 	(221524039) 
            - Faris Abulkhoir 		    (221524040) 
            - Mahardika Pratama 		(221524044)
Kelompok	: A1
Kelas		: 1B
Jurusan     : Teknik Komputer dan Informatika
Prodi       : D4 Teknik Informatika
Angkatan    : 2022/2023
Tanggal		: 15 Mei 2023
===============================================*/

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

void Encode(char filename[]);
/*
Description : Procedure for compressing ppm image files and storing the compressed results in a txt format file containing information on pixel values in bits, tree information, and header information.
I.S. : ppm image files are uncompressed.
F.S. : ppm image file has been successfully compressed and the compressed results are in the form of pixel value information in bits, tree information, and header information stored in a txt format file.
*/

HuffmanTreeNode* buildHuffmanTree(unsigned char (*data)[3], int freq[], int size);
/*
Description : This function builds a Huffman tree based on the provided data and frequency information.
I.S. : The data and frequency arrays are populated with pixel values and their frequencies.
F.S. : The Huffman tree is constructed using the provided data and frequency information.
Reference : https://www.geeksforgeeks.org/huffman-coding-using-priority-queue/
*/

HuffmanTreeNode* generateTree(priority_queue<HuffmanTreeNode*, vector<HuffmanTreeNode*>, Compare> pq);
/*
Description : This function generates a Huffman tree based on the priority queue of Huffman tree nodes.
I.S. : The priority queue contains Huffman tree nodes.
F.S. : The Huffman tree is generated using the priority queue of Huffman tree nodes.
Reference : https://www.geeksforgeeks.org/huffman-coding-using-priority-queue/
*/

void writeCodetoFile(HuffmanTreeNode* root, int arr[], int top);
/*
Description : This Procedure writes the Huffman codes of the unique pixels to a file.
I.S. : The Huffman tree and binary representation arrays are populated.
F.S. : The Huffman codes of the pixels are written to a file.
Reference : https://www.geeksforgeeks.org/huffman-coding-using-priority-queue/
*/

void encodeHuffman(HuffmanTreeNode* root, unsigned char header[], unsigned char *image, int size, char filename[]);
/*
Description : This Procedure encodes the image using Huffman coding and stores the compressed results in a file. 
			  It includes pixel value information in bits, tree information, and header information.
I.S. : The image is provided as uncompressed data. The Huffman tree is constructed. The header array is initialized.
F.S. : The image is encoded using Huffman coding. The compressed results, 
	   including pixel value information in bits, tree information, and header information, are stored in a file.
*/

void encodeTree(HuffmanTreeNode* root, FILE* file);
/*
Description : This Procedure encodes the Huffman tree and writes it to a file.
I.S. : The Huffman tree is constructed. The file is opened for writing.
F.S. : The Huffman tree is encoded and written to the file.
*/

void writeEncoded(unsigned char* image, int size, char filename[]);
/*
Description : This Procedure writes the encoded image data to a file.
I.S. : The encoded image data is available.
F.S. : The encoded image data is written to a file.
*/

void Decode(char filename1[]);
/*
Description : This Procedure decodes the compressed image file and restores it to its original ppm format.
I.S. : The compressed file is available
F.S. : The compressed file is decoded, and the original ppm image is reconstructed.
*/

void decodeHuffman(unsigned char *image, unsigned char header[], int size, char filename[]);
/*
Description : This procedure decodes the encoded image data using the Huffman tree and stores the decoded image in an array.
I.S. : The encoded image data, Huffman tree, header information, and file for output are available.
F.S. : The encoded image data is decoded using the Huffman tree, and the decoded image is stored in an array.
*/

HuffmanTreeNode *rebuildTree(FILE *read);
/*
Description : This Procedure rebuilds the Huffman tree from the encoded file.
I.S. : The encoded file is available.
F.S. : The Huffman tree is reconstructed from the encoded file.
*/

void readHeaderFromFile(FILE *read, unsigned char header[]);
/*
Description : This Procedure reads the header information from the encoded file.
I.S. : The encoded file is available, and the header array is initialized.
F.S. : The header information is read from the file and stored in the header array.
*/

void ConvertCodetoData(HuffmanTreeNode* root, unsigned char *image, int size, char filename[]);
/*
Description : This Procedure converts the encoded data back to the original 
			pixel values using the Huffman tree and stores the results in an array image.
I.S. : The encoded data, Huffman tree, and file for output are available.
F.S. : The encoded data is converted back to the original pixel values using the Huffman tree, and the results are stored in an array.
*/

void TraverseTree(HuffmanTreeNode** root, char c, unsigned char info[3]);
/*
Description : This Procedure traverses the Huffman tree to find the pixel value corresponding to a specific code.
I.S. : The Huffman tree, character code, and information array are available.
F.S. : The Huffman tree is traversed to find the corresponding pixel value, and store them in the info array.
*/
#endif
