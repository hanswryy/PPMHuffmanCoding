/*	Program		: body_PPMReader.cpp
	Deskripsi	: Body prototype ADT PPMReader
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

#include "PPMReader.h"


void readPPMHeader(FILE *file, unsigned char *header)
/*
Description : Procedure to read the header from the input PPM image file.
I.S. : “header” has not saved the header data from the PPM image file.
F.S. : “header” successfully saves the header data from the PPM image file.
Reference : https://www.delftstack.com/howto/cpp/read-ppm-file-cpp/
*/
{
    /*Algorithm*/

    //reads 15 bytes of data from the file pointed to by file and stores it in the memory location pointed to by header.
    fread(header, 15, 1, file);
}

void readPPMImage(FILE *file, unsigned char *image, int size)
/*
Description : Procedure to read pixel information from input PPM image file.
I.S. : “image” has not saved the pixel information from the PPM image file
F.S. : “image” successfully saves the pixel information from the PPM image file.
Reference : https://www.delftstack.com/howto/cpp/read-ppm-file-cpp/
*/
{
    /*Algorithm*/

    //reads size bytes of data from the file pointed to by file and stores it in the memory location pointed to by image.
    fread(image, size, 1, file);
}

int getDimension(unsigned char *header, int &pos)
/*
Description : Function to get the dimensions of a PPM image file.
I.S. : The dimensions of the PPM image file have not been obtained.
F.S. : The dimensions of the PPM image file have been obtained.
Reference : https://www.delftstack.com/howto/cpp/read-ppm-file-cpp/
*/
{
    /*Data Dictionary*/
    int dim;
    /*Algorithm*/
    dim=0;
    // Read through the characters, each char is being read as ASCII. 
	// Therefore we need to subtract it with the ASCII of '0' in order to get its integer value.
	// Cast each digit with this formula (x=0;x=x*10+num) to get the whole integer value of the dimension.
	// This process is repeated to get height.
    // (omg I can't believe I can speak English! by: Farhan)
    for ( ;header[pos]!='\n' && header[pos]!=' ';pos++)
        dim = dim * 10 + (header[pos] - '0');
    return dim;
}


void writePPM(FILE *file, unsigned char *header, unsigned char *image, int size)
/*
Description : Procedure for writing header and image data into a file with PPM format.
I.S. : Header and image data have not been written to a PPM format file.
F.S. : Header and image data successfully written into a file with PPM format.
Reference : https://www.delftstack.com/howto/cpp/read-ppm-file-cpp/
*/
{
    /*Algorithm*/

    //writing 15 bytes of data from the header array to the file.
    fwrite(header, 15, 1, file);

    //writing size bytes of data from the image array to the file.
    fwrite(image, size, 1, file);
}

//procedure to read rgb value of the PPM file
void readImage(unsigned char header[], unsigned char* &image, char filename[])
/*
Description : Procedure to read images in PPM (Portable Pixmap) format and store header data and pixel intensity information into a dynamic array.
I.S. : Array headers and image pointers are not initialized.
F.S. : The header array contains image header information, and the image pointer points to a dynamically allocated memory block that stores image pixel data.
Reference : https://www.delftstack.com/howto/cpp/read-ppm-file-cpp/
*/
{
    /*Data Dictionary*/
    FILE *read;
  	int width, height, pos;
    /*Algorithm*/

	//opens the file specified by filename in binary mode for reading.
	read = fopen(filename, "rb");
	
    //readPPMHeader function is called to read the PPM header from the file and store it in the header array.
    readPPMHeader(read, header);

    //The if condition checks if the PPM format is valid by verifying the first two characters of the header.
    if (header[0]!='P' || header[1]!='6'){
        //If the format is invalid, the program prints an error message and returns.
        printf("Invalid PPM format.\n");
        return;
    }	
    // get dimenstion
    //The pos variable is updated to the position of the width value in the header.
    pos = 3;

    //The width and height values are obtained by calling the getDimension function on the header array.
    width = getDimension(header, pos);
    pos++;
    height = getDimension(header, pos);

    //The image pointer is allocated with memory to store the pixel data based on the calculated width, height, and color channels (3 bytes per pixel).
    image = new unsigned char [width * height * 3];

    //The readPPMImage function is called to read the pixel data from the file and store it in the image array.
    readPPMImage(read, image, width*height*3);
    
    //the file is closed using fclose function.
    fclose(read);
}


void countPixelFrequency(unsigned char* image, int width, int height, int* freq, unsigned char (*data)[3])
/*
Description : Procedure for calculating the frequency of each pixel value in an image.
I.S. : The frequency of each image is not yet known.
F.S. : The frequency of each image is known.
Reference : https://www.geeksforgeeks.org/counting-frequencies-of-array-elements/
*/
{
    /*Data Dictionary*/
    int size, count, j, index;
    bool* visited = new bool[size];
    /*Algorithm*/

    //size stores the total number of pixels in the image (width * height * 3).
    size = width * height * 3;

    //All elements in the visited array are set to false.
	for (int i = 0; i < size; i++) {
		visited[i] = false;
	}
	index = 0;

    //The loop iterates through each pixel in the image.
	for (int i = 0 ; i < size; i+=3){
        //If a pixel has already been visited, the loop skips it and continues to the next pixel.
		if(visited[i] == true){
			continue;
		}
        //If a pixel has not been visited, it starts counting the frequency by comparing it with subsequent pixels.
		count = 1;
		for (j = i + 3; j < size; j += 3) {
            //If a subsequent pixel has the same RGB values, it is marked as visited and the count is incremented.
            if (image[i] == image[j] && image[i + 1] == image[j + 1] && image[i + 2] == image[j + 2]) {
                visited[j] = true;
                count++;
            }
        }
        //After counting the frequency, the count value is stored in the freq array at the corresponding index.
        //The RGB values of the pixel are stored in the data array at the corresponding index.
		freq[index] = count;
        data[index][0] = image[i];
        data[index][1] = image[i+1];
        data[index][2] = image[i+2];
		index++;
	}
    //the visited array is deallocated using delete[].
	delete[] visited;
}