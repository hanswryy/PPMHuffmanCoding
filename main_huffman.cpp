#include "PPMReader.h"
#include <stdio.h>

int main() {
    unsigned char header[15], *image;
	readImage(header, image); 
	
	int width, height, pos = 3;
	width = getDimension(header, pos);
	pos++;
	height = getDimension(header, pos);
	printf("\nWidth : %d, Height : %d\n", width, height);
	HuffmanNode root = (HuffmanNode)malloc(sizeof(Huffman));
	countPixelFrequency(image, width, height, &root);
	free(image);
	printPixelFrequency(root);
    
    return 0;
}

