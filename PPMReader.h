#ifndef PPMReader_h
#define PPMReader_h

#include <stdlib.h>
#include <stdio.h>

typedef struct tHuffmanNode *HuffmanNode;
typedef struct tHuffmanNode {
    unsigned char info[3];
    int freq;
    HuffmanNode left;
    HuffmanNode right;
} Huffman;

void readPPMHeader(FILE *file, unsigned char *header);

void readPPMImage(FILE *file, unsigned char *image, int size);

int getDimension(unsigned char *header, int &pos);

void writePPM(FILE *file, unsigned char *header, unsigned char *image, int size);

void readImage(unsigned char header[], unsigned char * &image, char filename[]);

void countPixelFrequency(unsigned char* image, int width, int height, int* freq,unsigned char (*data)[3]);

void printPixelFrequency(int* freq,unsigned char (*data)[3], int size);

#endif

