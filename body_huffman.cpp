/*	Program		: body_huffman.cpp
	Deskripsi	: Body prototype ADT Huffman Code pada kompresi gambar
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

// C++ Program for Huffman Coding
// using Priority Queue
#include "huffman.h"
#include "PPMReader.h"


void Encode(char filename[])
/*
Description : Procedure for compressing ppm image files and storing the compressed results in a txt format file containing information on pixel values in bits, tree information, and header information.
I.S. : ppm image files are uncompressed.
F.S. : ppm image file has been successfully compressed and the compressed results are in the form of pixel value information in bits, tree information, and header information stored in a txt format file.
*/
{
	/*Data Dictionary*/
    // File pointer to open and read the image file
	FILE *f;
	// Array to store the header and pixel data of the image
	unsigned char header[15], *image;
	// Pointer to the root of the Huffman tree
	HuffmanTreeNode *root = NULL;
	// Variables for image width, height, position, array, and length of the filename
	int width, height, pos, arr[MAX_SIZE], top, lenFilename;
	//variable for image size
	long fsize1, fsize2;
	// Allocate memory for the resulting compressed image
	unsigned char *resultImage = (unsigned char *)malloc(sizeof(unsigned char) * width * height * 3);
	// Dynamically allocate memory for the frequency of each pixel value
	int *freq = new int[width * height];
	// Allocate memory for pixel data in 2D array format
	unsigned char(*data)[3] = (unsigned char(*)[3])calloc(width * height, sizeof(unsigned char[3]));
    

	/*Algorithm*/
	// Open the image file in read mode
	f = fopen(filename, "r");
	// Move the file pointer to the end of the file
	fseek(f, 0, SEEK_END);
	// Get the file size of the original image
	fsize1 = ftell(f);
	printf("\t\t\tNama file original : %s\n", filename);
	printf("\t\t\tUkuran file original : %ld bytes\n", fsize1);
	// Close the file
	fclose(f);

	// Read the image header and pixel data
	readImage(header, image, filename);
	pos = 3;
	// Get the width of the image from the header
	width = getDimension(header, pos);
	pos++;
	// Get the height of the image from the header
	height = getDimension(header, pos);
	
	// Initialize the frequency array with zeros
	memset(freq, 0, sizeof(*freq) * width * height);
	
	if (freq == NULL || data == NULL)
	{
		printf("Failed to allocate memory\n");
	}
	else
	{
		// Calculate the frequency of each pixel value
		countPixelFrequency(image, width, height, freq, data);
		// Build the Huffman tree using the pixel data and frequencies
		root = buildHuffmanTree(data, freq, width * height);
		top = 0;
		// Write the Huffman codes to a file
		writeCodetoFile(root, arr, top);
		//count length of filename
		lenFilename = strlen(filename);
		filename[lenFilename - 3] = 't';
		filename[lenFilename - 2] = 'x';
		filename[lenFilename - 1] = 't'; 
		// Encode the image using Huffman coding
		encodeHuffman(root, header, image, width * height * 3, filename);
		// Open the compressed image file in read mode
		f = fopen(filename, "r");
		// Move the file pointer to the end of the file
		fseek(f, 0, SEEK_END);
		// Get the file size of the compressed image
		fsize2 = ftell(f);
		printf("\t\t\tNama file kompresi : %s\n", filename);
		printf("\t\t\tUkuran file kompresi : %ld bytes\n", fsize2);
		// Close the file
		fclose(f);
		printf("\t\t\tPersentase pengurangan size : %f persen\n", ((float)fsize2 / fsize1) * 100);
	}
}


HuffmanTreeNode *buildHuffmanTree(unsigned char (*data)[3], int freq[], int size)
/*
Description : This function builds a Huffman tree based on the provided data and frequency information.
I.S. : The data and frequency arrays are populated with pixel values and their frequencies.
F.S. : The Huffman tree is constructed using the provided data and frequency information.
Reference : https://www.geeksforgeeks.org/huffman-coding-using-priority-queue/
*/
{

	// Declaring priority queue using custom comparator
	priority_queue<HuffmanTreeNode *, vector<HuffmanTreeNode *>, Compare> pq;

	// Populating the priority queue
	for (int i = 0; i < size; i++)
	{
		if (freq[i] == 0)
		{
			continue;
		}
		HuffmanTreeNode *newNode = new HuffmanTreeNode(data[i], freq[i]);
		pq.push(newNode);
	}
	// Generate Huffman Encoding Tree and get the root node
	return generateTree(pq);
}



HuffmanTreeNode *generateTree(priority_queue<HuffmanTreeNode *, vector<HuffmanTreeNode *>, Compare> pq)
/*
Description : This function generates a Huffman tree based on the priority queue of Huffman tree nodes.
I.S. : The priority queue contains Huffman tree nodes.
F.S. : The Huffman tree is generated using the priority queue of Huffman tree nodes.
Reference : https://www.geeksforgeeks.org/huffman-coding-using-priority-queue/
*/
{

	// We keep on looping till
	// only one node remains in
	// the Priority Queue
	while (pq.size() != 1)
	{

		// Node which has least
		// frequency
		HuffmanTreeNode *left = pq.top();

		// Remove node from
		// Priority Queue
		pq.pop();

		// Node which has least
		// frequency
		HuffmanTreeNode *right = pq.top();

		// Remove node from
		// Priority Queue
		pq.pop();

		// A new node is formed
		// with frequency left->freq
		// + right->freq

		// We take data as '$'
		// because we are only
		// concerned with the
		// frequency
		unsigned char empty[3] = {0, 0, 0};
		HuffmanTreeNode *node = new HuffmanTreeNode(empty, left->freq + right->freq);
		node->left = left;
		node->right = right;

		// Push back node
		// created to the
		// Priority Queue
		pq.push(node);
	}

	return pq.top();
}



void writeCodetoFile(HuffmanTreeNode *root, int arr[], int top)
/*
Description : This Procedure writes the Huffman codes of the unique pixels to a file.
I.S. : The Huffman tree and binary representation arrays are populated.
F.S. : The Huffman codes of the pixels are written to a file.
Reference : https://www.geeksforgeeks.org/huffman-coding-using-priority-queue/
*/
{
	// Assign 0 to the left node
	// and recur
	if (root->left)
	{
		arr[top] = 0;
		writeCodetoFile(root->left, arr, top + 1);
	}

	// Assign 1 to the right
	// node and recur
	if (root->right)
	{
		arr[top] = 1;
		writeCodetoFile(root->right, arr, top + 1);
	}

	if (!root->left && !root->right)
	{
		// Open the file in "a" (append) mode to write the codes
		FILE *file = fopen("code.txt", "a");
		// Write the pixel values to the file
		fprintf(file, "%hhu %hhu %hhu ", root->data[0], root->data[1], root->data[2]);
		for (int i = 0; i < top; i++)
		{
			// Write the Huffman code (0 or 1) to the file
			fprintf(file, "%d", arr[i]);
		}
		// Write a new line character to separate the codes
		fprintf(file, "\n");
		// Close the file
		fclose(file);
	}
}


void encodeHuffman(HuffmanTreeNode *root, unsigned char header[], unsigned char *image, int size, char filename[])
/*
Description : This Procedure encodes the image using Huffman coding and stores the compressed results in a file. 
			  It includes pixel value information in bits, tree information, and header information.
I.S. : The image is provided as uncompressed data. The Huffman tree is constructed. The header array is initialized.
F.S. : The image is encoded using Huffman coding. The compressed results, 
	   including pixel value information in bits, tree information, and header information, are stored in a file.
*/
{
	/*Data Dictionary*/
    FILE *write;
	int i, j, k;
    /*Algorithm*/
	i = 0, j = 0, k = 0;
	// Encode the RGB values to binary values and write to a file
	writeEncoded(image, size, filename);
	// Open the file in "ab" (append and binary) mode
	write = fopen(filename, "ab");
	// Write the Huffman tree to the file
	encodeTree(root, write);
	// Write a new line character to separate the tree from the header
	fprintf(write, "\n");

	// Write the header to the file
	for (; j < 15; j++)
	{
		fprintf(write, "%c", header[j]);
		if (header[j] == '\n')
		{
			i++;
		}
		if (i == 3)
		{
			break;
		}
	}
	// Close the file
	fclose(write);
}


void encodeTree(HuffmanTreeNode *node, FILE *file)
/*
Description : This Procedure encodes the Huffman tree and writes it to a file.
I.S. : The Huffman tree is constructed. The file is opened for writing.
F.S. : The Huffman tree is encoded and written to the file.
*/
{
	// If the current node is a leaf node (no left or right child),
	// write "1" to indicate a leaf and write the RGB values to the file
	if (!node->left && !node->right)
	{
		// Write "1" as a leaf node indicator
		fwrite("1", 1, 1, file);
		// Write the RGB values to the file
		fprintf(file, " %hhu %hhu %hhu ", node->data[0], node->data[1], node->data[2]);
	}
	else
	{
		// Write "0" to indicate an internal node
		fwrite("0", 1, 1, file);
		// Recursively encode the left subtree
		encodeTree(node->left, file);
		// Recursively encode the right subtree
		encodeTree(node->right, file);
	}
}

void writeEncoded(unsigned char *image, int size, char filename[])
/*
Description : This Procedure writes the encoded image data to a file.
I.S. : The encoded image data is available.
F.S. : The encoded image data is written to a file.
*/
{
	/*Data Dictionary*/
    int i, j, k;
	bitset<8> writebit;
	unsigned long n;
	unsigned char data[3];
	char code[100];
	FILE *file;
    /*Algorithm*/
	k = 7;
	// Open the output file in binary mode for writing encoded data
	ofstream output(filename, ios::binary);
	// Open the code.txt file containing the Huffman codes
	file = fopen("code.txt", "r");
	// Loop through the elements of the image array
	for (i = 0; i < size; i += 3)
	{
		// Loop through the elements of the image array
		while (!feof(file))
		{
			// Read the RGB values and corresponding code
			fscanf(file, "%hhu %hhu %hhu ", &data[0], &data[1], &data[2]);
			fscanf(file, "%s", code);
			if (data[0] == image[i] && data[1] == image[i + 1] && data[2] == image[i + 2])
			{
				// Loop through the characters of the code
				for (j = 0; j < strlen(code); j++)
				{
					if (code[j] == '0')
					{
						// Set the bit at index k to 0
						writebit.set(k, 0);
					}
					else if (code[j] == '1')
					{
						// Set the bit at index k to 1
						writebit.set(k, 1);
					}
					k--;
					// If the bitset is full (k reaches -1), write the bitset to the output file
					if (k == -1)
					{
						// Convert the bitset to an unsigned long
						n = writebit.to_ulong();
						// Write the unsigned long to the file
						output.write(reinterpret_cast<const char *>(&n), sizeof(n));
						// Reset k to 7
						k = 7;
						// Reset the bitset
						writebit.reset();
					}
				}
				break;
			}
		}
		// Reset the file pointer to the start of the code.txt file for the next iteration
		fseek(file, 0, SEEK_SET);
	}
	// Write the last bitset to the output file if it is not full
	n = writebit.to_ulong();
	output.write(reinterpret_cast<const char *>(&n), sizeof(n));
	// Close the output file
	output.close();
	// Close the code.txt file
	fclose(file);
	// Delete the code.txt file for security reasons
	remove("code.txt");
}


void Decode(char filename1[])
/*
Description : This Procedure decodes the compressed image file and restores it to its original ppm format.
I.S. : The compressed file is available
F.S. : The compressed file is decoded, and the original ppm image is reconstructed.
*/
{
	/*Data Dictionary*/
    FILE *f, *read, *write;
	long fsize1, fsize2;
	unsigned char resultHeader[15];
	int width, height, pos;
    unsigned char *resultImage = (unsigned char *)malloc(sizeof(unsigned char) * width * height * 3);
	/*Algorithm*/

	// Open the input file in read mode
	f = fopen(filename1, "r");
	// Move the file pointer to the end of the file
	fseek(f, 0, SEEK_END);
	// Get the file size
	fsize1 = ftell(f);
	printf("\t\t\tNama file original : %s\n", filename1);
	printf("\t\t\tUkuran file original : %ld bytes\n", fsize1);
	// Close the input file
	fclose(f);
	
	// Open the input file again to read the header
	read = fopen(filename1, "r");
	// Read the header from the file
	readHeaderFromFile(read, resultHeader);
	
	pos = 3;
	// Get the width dimension from the header
	width = getDimension(resultHeader, pos);
	pos++;
	// Get the height dimension from the header
	height = getDimension(resultHeader, pos);
	// Close the file after reading the header
	fclose(read);
	
	// Decode the Huffman-encoded image
	decodeHuffman(resultImage, resultHeader, width * height * 3, filename1);
	// Open a new file to write the decoded image
	write = fopen("finishresult.ppm", "wb");
	// Write the header and image data to the file in PPM format
	writePPM(write, resultHeader, resultImage, width * height * 3);
	// Close the output file
	fclose(write);
	// Open the decoded file to get its size
	f = fopen("finishresult.ppm", "r");
	// Move the file pointer to the end of the file
	fseek(f, 0, SEEK_END);
	// Get the file size
	fsize2 = ftell(f);
	printf("\t\t\tNama file dekompresi : finishresult.ppm\n");
	printf("\t\t\tUkuran file dekompresi : %ld bytes\n", fsize2);
	// Close the decoded file
	fclose(f);
	printf("\t\t\tPersentase penambahan size : %f persen\n", ((float)fsize2 / fsize1) * 100);
}


void decodeHuffman(unsigned char *image, unsigned char header[], int size, char filename[])
/*
Description : This procedure decodes the encoded image data using the Huffman tree and stores the decoded image in an array.
I.S. : The encoded image data, Huffman tree, header information, and file for output are available.
F.S. : The encoded image data is decoded using the Huffman tree, and the decoded image is stored in an array.
*/
{
	/*Data Dictionary*/
    FILE *read;
	HuffmanTreeNode *root;
	int width, height, pos;
    /*Algorithm*/
	// Open the input file in read mode
	read = fopen(filename, "r");
	if (read == NULL)
	{
		printf("File tidak ditemukan\n");
	}
	// Rebuild the Huffman tree from the file
	root = rebuildTree(read); // get the tree from the file txt
	// Read the header from the file
	readHeaderFromFile(read, header);		   // read the header from the file txt
	pos = 3;
	// Get the width dimension from the header
	width = getDimension(header, pos);
	pos++;
	// Get the height dimension from the header
	height = getDimension(header, pos);
	// Convert the Huffman codes in the file to image data
	ConvertCodetoData(root, image, size, filename); // decode the file txt to the image.ppm
	// Close the input file
	fclose(read);
}


HuffmanTreeNode *rebuildTree(FILE *read)
/*
Description : This Procedure rebuilds the Huffman tree from the encoded file.
I.S. : The encoded file is available.
F.S. : The Huffman tree is reconstructed from the encoded file.
*/
{
	/*Data Dictionary*/
    char c;
	unsigned char data[3];
	HuffmanTreeNode *left, *right, *root;
	unsigned char empty[3] = {0, 0, 0};
    /*Algorithm*/
	
	// Stop when it reads a newline character
	while ((c = fgetc(read)) != '\n')
	{
		if (c == '1')
		{
			// Read the data values from the file
			fscanf(read, "%hhu %hhu %hhu", &data[0], &data[1], &data[2]);
			// Create a new leaf node with the data values
			return new HuffmanTreeNode(data, 0);
		}
		else if (c == '0')
		{
			// Recursively rebuild the left and right subtrees
			left = rebuildTree(read);
			right = rebuildTree(read);
			// Create a new internal node with empty data values
			root = new HuffmanTreeNode(empty, 0);
			// Assign the left and right subtrees to the internal node
			root->left = left;
			root->right = right;
			return root;
		}
	}
	return 0;
}



void readHeaderFromFile(FILE *read, unsigned char header[])
/*
Description : This Procedure reads the header information from the encoded file.
I.S. : The encoded file is available, and the header array is initialized.
F.S. : The header information is read from the file and stored in the header array.
*/
{
	/*Data Dictionary*/
    int i, j;
	char c;
    /*Algorithm*/
	// Skip characters until 'P' is found
	while (fgetc(read) != 'P'){}
	// Set the first character of the header to 'P'
	header[0] = 'P';
	i = 1; // Initialize the index for the header array
	j = 0; // Initialize the counter for newline characters
	// Read characters and populate the header array
	while (j < 3)
	{
		c = fgetc(read);
		header[i] = c;
		i++;
		if (c == '\n')
		{
			j++;
		}
	}
}


void ConvertCodetoData(HuffmanTreeNode *root, unsigned char *image, int size, char filename[])
/*
Description : This Procedure converts the encoded data back to the original 
			pixel values using the Huffman tree and stores the results in an array image.
I.S. : The encoded data, Huffman tree, and file for output are available.
F.S. : The encoded data is converted back to the original pixel values using the Huffman tree, and the results are stored in an array.
*/
{
	/*Data Dictionary*/
    bitset<8> readbit;
	unsigned long byte;
	int i, j, k;
	unsigned char info[3];
	HuffmanTreeNode *temp;
    /*Algorithm*/
	// Initialize the index for the image array
	j = 0;
	// Open the input file in binary mode for reading
	ifstream input(filename, ios::binary);
	// Set the current node to the root of the Huffman tree
	temp = root;
	// Read bytes from the input file and process each bit
	while (input.read(reinterpret_cast<char *>(&byte), sizeof(byte)))
	{
		readbit = byte; // Convert the byte to a bitset
		// Process each bit in the bitset
		for (k = 0; k < 8; k++)
		{
			// Traverse the Huffman tree based on the current bit
			TraverseTree(&temp, readbit.to_string()[k], info);
			// Check if the current node is a leaf node
			if (temp->left != NULL && temp->right != NULL)
			{
				continue; // If not a leaf node, continue to the next bit
			}
			else
			{
				// If it is a leaf node, store the RGB values in the image array
				for (i = 0; i < 3; i++)
				{
					if (j < size)
					{
						image[j] = info[i];
						j++;
					}
				}
				// Reset the current node to the root for the next bit
				temp = root;
			}
		}
	}
	// Close the input file
	input.close();
}


void TraverseTree(HuffmanTreeNode **root, char c, unsigned char info[3])
/*
Description : This Procedure traverses the Huffman tree to find the pixel value corresponding to a specific code.
I.S. : The Huffman tree, character code, and information array are available.
F.S. : The Huffman tree is traversed to find the corresponding pixel value, and store them in the info array.
*/
{
	// Update the current node based on the input bit
	if (c == '0')
	{
		*root = (*root)->left;
	}
	else if (c == '1')
	{
		*root = (*root)->right;
	}
	// Check if the current node is a leaf node
	if (!(*root)->left && !(*root)->right)
	{
		// If it is a leaf node, retrieve the RGB values from the node's data and store them in the info array
		info[0] = (*root)->data[0];
		info[1] = (*root)->data[1];
		info[2] = (*root)->data[2];
	}
}

