#include "PPMReader.h"


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

void readImage(unsigned char header[], unsigned char* &image) // perubahan pada bagian parameter
{
	FILE *read, *write1;
  	int i, j;
	read = fopen("first.ppm", "rb"); /* b - binary mode */
	
    readPPMHeader(read, header);
    if (header[0]!='P' || header[1]!='6'){
        printf("Wrong hahah");
        return;
    }	
    // get dimenstion
    int width, height, clrs, pos = 3;
    width = getDimension(header, pos);
    pos++;
    
    height = getDimension(header, pos);
    image = new unsigned char [width * height * 3];
    readPPMImage(read, image, width*height*3);
    // Validate the pixel intensities (rgb) of the first pixel. (255 29 29)
    
    fclose(read);
}

void countPixelFrequency(unsigned char* image, int width, int height, int* freq, unsigned char (*data)[3]){

    int size = width * height * 3;
    bool* visited = new bool[size] {false};
    printf("\nsize : %d\n", size);
	int count;
	int j,k;
	int index = 0;
	for (int i = 0 ; i < size; i+=3){
		bool found = false;
		if(visited[i] == true){
			continue;
		}
		count = 1;
		
		for (j = i + 3; j < size; j += 3) {
            if (image[i] == image[j] && image[i + 1] == image[j + 1] && image[i + 2] == image[j + 2]) {
                visited[j] = true;
                count++;
            }
        }
        
		freq[index] = count;
        data[index][0] = image[i];
        data[index][1] = image[i+1];
        data[index][2] = image[i+2];
		printf("(%d, %d, %d) : %d\n", data[index][0], data[index][1],data[index][2], freq[i]);
		index++;
	}
	delete[] visited;
}

// function to print pixel frequency table
void printPixelFrequency(int* freq,unsigned char (*data)[3]){
    printf("\nPixel Frequency Table:\n");
	for(int i=0; i<99; i++){
		if (freq[i] > 0){
			printf("(%d, %d, %d) : %d\n", data[i][0], data[i][1],data[i][2], freq[i]);		
		}
    }
}

