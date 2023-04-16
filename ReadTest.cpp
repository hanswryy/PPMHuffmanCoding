#include <stdlib.h>
#include <stdio.h>

void readPPMHeader(FILE *file, unsigned char *header){
    fread(header, 15, 1, file);
}
void readPPMImage(FILE *file, unsigned char *image, int size){
    fread(image, size, 1, file);
}

int getDimension(unsigned char *header, int &pos){
    int dim=0;
    // Read through the characters, each char is being read as ASCII. 
	// Therefore we need to subtract it with the ASCII of '0' in order to get its integer value.
	// Cast each digit with this formula (x=0;x=x*10+num) to get the whole integer value of the dimension.
	// This process is repeated to get height.
    // (omg I can't believe I can speak English! by: Farhan)
    for ( ;header[pos]!='\n' && header[pos]!=' ';pos++)
        dim = dim * 10 + (header[pos] - '0');
    return dim;
}

void writePPM(FILE *file, unsigned char *header, unsigned char *image, int size){
    fwrite(header, 15, 1, file);
    fwrite(image, size, 1, file);
}

int main(void)
{
	FILE *read, *write1;
	unsigned char header[15], *image;
  	int i, j;
	read = fopen("first.ppm", "rb"); /* b - binary mode */
    readPPMHeader(read, header);
    if (header[0]!='P' || header[1]!='6'){
        printf("Wrong hahah");
        return 0;
    }
    // get dimenstion
    int width, height, clrs, pos = 3;
    width = getDimension(header, pos);
    pos++;
    height = getDimension(header, pos);
    printf("Width : %d, Height : %d", width, height);
    image = new unsigned char [width * height * 3];
    readPPMImage(read, image, width*height*3);
    // Validate the pixel intensities (rgb) of the first pixel. (255 29 29)
    printf("\n");
    for (i=0;i<3;i++){
    	printf("%d", *image);
    	*image++;
    }
	writePPM(write1, header, image, width * height * 3);
    fclose(read);
    return 0;
}
