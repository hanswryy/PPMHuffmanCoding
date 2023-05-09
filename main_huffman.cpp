#include "PPMReader.h"
#include "huffman.h"
#include <stdio.h>

int main() {
    unsigned char header[15], resultHeader[15], *image;
    int sumrgb;
    HuffmanTreeNode* root = NULL;
	readImage(header, image); 
    
	
	int width, height, pos = 3;
	width = getDimension(header, pos);
	pos++;
	height = getDimension(header, pos);
	printf("\nWidth : %d, Height : %d\n", width, height);
	unsigned char *resultImage = (unsigned char*) malloc(sizeof(unsigned char) * width*height*3);
	int *freq = new int[width*height]{0};
	
    unsigned char (*data)[3] = (unsigned char (*)[3])calloc(width*height, sizeof(unsigned char[3]));

    if (freq == NULL || data == NULL) {
        printf("Failed to allocate memory\n");
        return 1;
    }

	countPixelFrequency(image, width, height, freq, data);

	printPixelFrequency(freq, data, width*height);

    HuffmanCodes(data, freq, width*height);

    root = giveTree(data, freq, width*height, &sumrgb);
    int arr[MAX_SIZE], top = 0;
    printCodes(root, arr, top);
    printTree(root, arr, top);

    printf("Printing codes from tree\n");
    //printf("%i %i %i", image[0], image[1], image[2]);

    encodeHuffman(root, header, image, width*height*3);
    decodeHuffman(resultImage, resultHeader, width*height*3);
    
    for (int i = width*height*3-9; i<width*height*3; i++){
    	printf("image : %d\n", image[i]);
    	printf("result : %d\n", resultImage[i]);
//    	printf("header : %c\n", resultHeader[i]);
	}
    
    FILE *write = fopen("result.ppm", "wb");
    writePPM(write, resultHeader, resultImage, width*height*3);
    
	free(resultImage);
	free(image);
    free(freq);
    free(data);

    remove("code.txt");
    return 0;
}

