#include "PPMReader.h"
#include <stdio.h>

int main() {
    unsigned char *header, *image;
    readImage(&(*header), &(*image));
    printf("\n");
    
    for (int i=0;i<3;i++){
    	printf("%d", *image);
    	image++;
    }
    return 0;
}