/*	
Program		: body_PPMReader.cpp
Deskripsi	: Header untuk ADT PPMReader
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

#ifndef PPMReader_h
#define PPMReader_h

#include <stdlib.h>
#include <stdio.h>


void readPPMHeader(FILE *file, unsigned char *header);
/*
Description : Procedure to read the header from the input PPM image file.
I.S. : “header” has not saved the header data from the PPM image file.
F.S. : “header” successfully saves the header data from the PPM image file.
Referensi : https://www.delftstack.com/howto/cpp/read-ppm-file-cpp/
*/

void readPPMImage(FILE *file, unsigned char *image, int size);
/*
Description : Procedure to read pixel information from input PPM image file.
I.S. : “image” has not saved the pixel information from the PPM image file
F.S. : “image” successfully saves the pixel information from the PPM image file.
Reference : https://www.delftstack.com/howto/cpp/read-ppm-file-cpp/
*/

int getDimension(unsigned char *header, int &pos);
/*
Description : Function to get the dimensions of a PPM image file.
I.S. : The dimensions of the PPM image file have not been obtained.
F.S. : The dimensions of the PPM image file have been obtained.
Reference : https://www.delftstack.com/howto/cpp/read-ppm-file-cpp/
*/

void writePPM(FILE *file, unsigned char *header, unsigned char *image, int size);
/*
Description : Procedure for writing header and image data into a file with PPM format.
I.S. : Header and image data have not been written to a PPM format file.
F.S. : Header and image data successfully written into a file with PPM format.
Reference : https://www.delftstack.com/howto/cpp/read-ppm-file-cpp/
*/

void readImage(unsigned char header[], unsigned char * &image, char filename[]);
/*
Description : Procedure to read images in PPM (Portable Pixmap) format and store header data and pixel intensity information into a dynamic array.
I.S. : Array headers and image pointers are not initialized.
F.S. : The header array contains image header information, and the image pointer points to a dynamically allocated memory block that stores image pixel data.
Reference : https://www.delftstack.com/howto/cpp/read-ppm-file-cpp/
*/

void countPixelFrequency(unsigned char* image, int width, int height, int* freq,unsigned char (*data)[3]);
/*
Description : Procedure for calculating the frequency of each pixel value in an image.
I.S. : The frequency of each image is not yet known.
F.S. : The frequency of each image is known.
Reference : https://www.geeksforgeeks.org/counting-frequencies-of-array-elements/
*/

#endif

