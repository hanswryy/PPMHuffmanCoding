#include <stdio.h>
#include "header.h"

int main() {
    unsigned char header[15], *image;
	readImage(header, image); 
	
	int width, height, pos = 3;
	width = getDimension(header, pos);
	pos++;
	height = getDimension(header, pos);
	printf("\nWidth : %d, Height : %d\n", width, height);

	int *freq = new int[width*height];
    unsigned char (*data)[3] = (unsigned char (*)[3])calloc(width*height, sizeof(unsigned char[3]));

    if (freq == NULL || data == NULL) {
        printf("Failed to allocate memory\n");
        return 1;
    }
	countPixelFrequency(image, width, height, freq, data);

//	printPixelFrequency(freq, data, width*height);
	TreeNode *root;
	root = buildHuffmanCodes(data, freq, width*height);
	int arr[10000], top = 0;
	printCodes(root, arr, top);
	free(image);
    free(freq);
    free(data);
    return 0;
}
