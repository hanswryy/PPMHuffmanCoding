#include "PPMReader.h"
#include <stdio.h>

int main() {
    unsigned char header[15], *image;
	readImage(header, image);
	
	int width, height, pos = 3;
  	width = getDimension(header, pos);
  	pos++;
  	height = getDimension(header, pos);
	int numChannels = 3;  // tiga channel warna (RGB)
	int imageSize = width * height * numChannels;
  	int numPixels = imageSize / 3;
    unsigned char infoImage[numPixels][3];
    
	int count = 0;
    for (int i = 0; i < numPixels; i++) {
        for (int j = 0; j < 3; j++) {
            infoImage[i][j] = image[count];
            count++;
        }
    }
    Huffman root;
    hitungFreq(infoImage, &root, imageSize);
    
    return 0;
}

