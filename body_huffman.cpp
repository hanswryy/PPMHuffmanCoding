// C++ Program for Huffman Coding
// using Priority Queue
#include "huffman.h"

// Function to generate Huffman
// Encoding Tree
HuffmanTreeNode *generateTree(priority_queue<HuffmanTreeNode *,
											 vector<HuffmanTreeNode *>,
											 Compare>
								  pq)
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
		HuffmanTreeNode *node = new HuffmanTreeNode(empty,
													left->freq + right->freq);
		node->left = left;
		node->right = right;

		// Push back node
		// created to the
		// Priority Queue
		pq.push(node);
	}

	return pq.top();
}

// Function to print the
// huffman code for each
// character.

// It uses file to store the codes
void writeCodetoFile(HuffmanTreeNode *root,
				int arr[], int top)
{
	// Assign 0 to the left node
	// and recur
	if (root->left)
	{
		arr[top] = 0;
		writeCodetoFile(root->left,
				   arr, top + 1);
	}

	// Assign 1 to the right
	// node and recur
	if (root->right)
	{
		arr[top] = 1;
		writeCodetoFile(root->right, arr, top + 1);
	}

	// If this is a leaf node,
	// then we print root->data

	// We also print the code
	// for this character from arr
	if (!root->left && !root->right)
	{
		FILE *file = fopen("code.txt", "a");
		fprintf(file, "%hhu %hhu %hhu ", root->data[0], root->data[1], root->data[2]);
		for (int i = 0; i < top; i++)
		{
			fprintf(file, "%d", arr[i]);
		}
		fprintf(file, "\n");
		fclose(file);
	}
}

//this procedure is used to replace the rgb value with binary value from the tree
void writeEncoded(unsigned char *image, int size)
{
	int k = 7;
	bitset<8> writebit;
	unsigned long n;
	ofstream output("Test1.txt", ios::binary);
	unsigned char data[3];
	char code[100];
	FILE *file = fopen("code.txt", "r");
	//this looping through the elemen of rgb array
	for (int i = 0; i < size; i += 3)
	{
		//this looping is used to find the binary value of the rgb value
		while (!feof(file))
		{
			fscanf(file, "%hhu %hhu %hhu ", &data[0], &data[1], &data[2]);
			fscanf(file, "%s", code);
			if (data[0] == image[i] && data[1] == image[i + 1] && data[2] == image[i + 2])
			{
				//this looping is used to write the binary value to the file
				for (int j = 0; j < strlen(code); j++)
				{
					if (code[j] == '0')
					{
						writebit.set(k, 0);
					}
					else if (code[j] == '1')
					{
						writebit.set(k, 1);
					}
					k--;
					//if the bitset is full then it will write the bitset to the file
					if (k == -1)
					{
						n = writebit.to_ulong();
						output.write(reinterpret_cast<const char *>(&n), sizeof(n));
						k = 7;
						writebit.reset();
					}
				}
				break;
			}
		}
		//this is used to reset the file pointer to the start of the file
		fseek(file, 0, SEEK_SET);
	}
	//this is used to write the last bitset to the file when the bitset is not full
	n = writebit.to_ulong();
	output.write(reinterpret_cast<const char *>(&n), sizeof(n));
	output.close();
	fclose(file);
	//this is used to delete the code.txt file so no one can see the code
	remove("code.txt");
}

//this function is used to get the huffman tree from the rgb value
HuffmanTreeNode *buildHuffmanTree(unsigned char (*data)[3],
						  int freq[], int size, int *arrsize)
{

	// Declaring priority queue
	// using custom comparator
	priority_queue<HuffmanTreeNode *,
				   vector<HuffmanTreeNode *>,
				   Compare>
		pq;

	// Populating the priority
	// queue
	for (int i = 0; i < size; i++)
	{
		if (freq[i] == 0)
		{
			continue;
		}
		HuffmanTreeNode *newNode = new HuffmanTreeNode(data[i], freq[i]);
		pq.push(newNode);
	}
	*arrsize = pq.size();
	// Generate Huffman Encoding
	// Tree and get the root node
	return generateTree(pq);
}

//this procedure is used to encode the image.ppm to the file txt
void encodeHuffman(HuffmanTreeNode *root, unsigned char header[], unsigned char *image, int size, char filename[])
{
	//change the filename to .txt
	int lenFilename = strlen(filename);
	filename[lenFilename-3] = 't';
	filename[lenFilename-2] = 'x';
	filename[lenFilename-1] = 't';

	//this is used to encode the rgb value to binary value
	writeEncoded(image, size);

	FILE *write;
	int i = 0, j = 0, k = 0;
	write = fopen(filename, "ab");
	encodeTree(root, write); // write the tree to the file
	fprintf(write, "\n");

	/*write the header to the file*/
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
	fclose(write);
}

//this procedure is used to write the tree to the file
//if the node is leaf then it will write 1 and the rgb value
//if the node is not leaf then it will write 0 and go to the left and right node
void encodeTree(HuffmanTreeNode *node, FILE *file)
{
	if (!node->left && !node->right)
	{
		fwrite("1", 1, 1, file);
		fprintf(file, " %hhu %hhu %hhu ", node->data[0], node->data[1], node->data[2]);
	}
	else
	{
		fwrite("0", 1, 1, file);
		encodeTree(node->left, file);
		encodeTree(node->right, file);
	}
}

//this procedure is used to decode the file txt to the image.ppm
void decodeHuffman(unsigned char *image, unsigned char header[], int size, char filename[])
{
	FILE *read = fopen(filename, "r");
	if (read == NULL)
	{
		printf("File tidak ditemukan\n");
	}
	HuffmanTreeNode *root = rebuildTree(read);//get the tree from the file txt
	int arr[MAX_SIZE], top = 0;
	readHeaderFromFile(read, header);//read the header from the file txt
	int width, height, pos = 3;
	width = getDimension(header, pos);
	pos++;
	height = getDimension(header, pos);
	ConvertCodetoData(root, image, size, filename);//decode the file txt to the image.ppm
	fclose(read);
}

// read the tree from the file
HuffmanTreeNode *rebuildTree(FILE *read)
{
	char c;
	unsigned char data[3];
	// stop when it reads newline
	while ((c = fgetc(read)) != '\n')
	{
		if (c == '1')
		{
			fscanf(read, "%hhu %hhu %hhu", &data[0], &data[1], &data[2]);
			return new HuffmanTreeNode(data, 0);
		}
		else if (c == '0')
		{
			HuffmanTreeNode *left = rebuildTree(read);
			HuffmanTreeNode *right = rebuildTree(read);
			unsigned char empty[3] = {0, 0, 0};
			HuffmanTreeNode *root = new HuffmanTreeNode(empty, 0);
			root->left = left;
			root->right = right;
			return root;
		}
	}
	return 0;
}

// just read the header from txt
void readHeaderFromFile(FILE *read, unsigned char header[])
{
	while (fgetc(read) != 'P')
	{
	}
	header[0] = 'P';
	int i = 1, j = 0;
	char c;
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

//convert the binary value from txt file to rgb value
void ConvertCodetoData(HuffmanTreeNode *root, unsigned char *image, int size, char filename[])
{
	ifstream input(filename, ios::binary);
	bitset<8> readbit;
	unsigned long byte;
	int j = 0;
	unsigned char info[3];
	HuffmanTreeNode *temp;
	temp = root;
	while (input.read(reinterpret_cast<char *>(&byte), sizeof(byte)))
	{
		readbit = byte;
		for (int k = 0; k < 8; k++)
		{
			TraverseTree(&temp, readbit.to_string()[k], info);
			if (info[0] != 0 && info[1] != 0 && info[2] != 0)
			{
				for (int i = 0; i < 3; i++)
				{
					if (j < size)
					{
						image[j] = info[i];
						j++;
					}
				}
				temp = root;
			}
		}
	}

	input.close();
}

//this procedure is used to traverse the tree to get the rgb value
void TraverseTree(HuffmanTreeNode **root, char c, unsigned char info[3])
{
	if (c == '0')
	{
		*root = (*root)->left;
		info[0] = 0;
		info[1] = 0;
		info[2] = 0;
	}
	else if (c == '1')
	{
		*root = (*root)->right;
		info[0] = 0;
		info[1] = 0;
		info[2] = 0;
	}

	if (!(*root)->left && !(*root)->right)
	{
		info[0] = (*root)->data[0];
		info[1] = (*root)->data[1];
		info[2] = (*root)->data[2];
	}
}

//this procedure is used to encode the image.ppm to the file txt
//this procedure is all of flow oh the huffman encoding
void Encode(char filename[])
{
	unsigned char header[15], resultHeader[15], *image;
	int sumrgb;
	HuffmanTreeNode *root = NULL;
	readImage(header, image, filename);
	int width, height, pos = 3;
	width = getDimension(header, pos);
	pos++;
	height = getDimension(header, pos);
	unsigned char *resultImage = (unsigned char *)malloc(sizeof(unsigned char) * width * height * 3);
	int *freq = new int[width * height]{0};
	unsigned char(*data)[3] = (unsigned char(*)[3])calloc(width * height, sizeof(unsigned char[3]));
	if (freq == NULL || data == NULL)
	{
		printf("Failed to allocate memory\n");
	}
	else
	{
		countPixelFrequency(image, width, height, freq, data);
		root = buildHuffmanTree(data, freq, width * height, &sumrgb);
		int arr[MAX_SIZE], top = 0;
		writeCodetoFile(root, arr, top);
		encodeHuffman(root, header, image, width * height * 3, filename);
	}
}

//this procedure is used to decode the file txt to the image.ppm
//this procedure is all of flow of the decoding process
void Decode(char filename1[])
{
	FILE *read = fopen(filename1, "r");
	unsigned char resultHeader[15];
	readHeaderFromFile(read, resultHeader);
	int width, height, pos = 3;
	width = getDimension(resultHeader, pos);
	pos++;
	height = getDimension(resultHeader, pos);
	fclose(read);
	unsigned char *resultImage = (unsigned char *)malloc(sizeof(unsigned char) * width * height * 3);
	decodeHuffman(resultImage, resultHeader, width * height * 3, filename1);
	FILE *write = fopen("finishresult.ppm", "wb");
	writePPM(write, resultHeader, resultImage, width * height * 3);
}