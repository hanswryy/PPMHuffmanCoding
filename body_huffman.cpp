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

// It uses arr to store the codes
void printCodes(HuffmanTreeNode *root,
				int arr[], int top)
{
	// Assign 0 to the left node
	// and recur
	if (root->left)
	{
		arr[top] = 0;
		printCodes(root->left,
				   arr, top + 1);
	}

	// Assign 1 to the right
	// node and recur
	if (root->right)
	{
		arr[top] = 1;
		printCodes(root->right, arr, top + 1);
	}

	// If this is a leaf node,
	// then we print root->data

	// We also print the code
	// for this character from arr
	if (!root->left && !root->right)
	{

		printf("(%hhu, %hhu, %hhu)", root->data[0], root->data[1], root->data[2]);
		for (int i = 0; i < top; i++)
		{
			cout << arr[i];
		}
		cout << endl;
	}
}

void HuffmanCodes(unsigned char (*data)[3],
				  int freq[], int size)
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

	// Generate Huffman Encoding
	// Tree and get the root node
	HuffmanTreeNode *root = generateTree(pq);

	// Print Huffman Codes
	int arr[MAX_SIZE], top = 0;
	printCodes(root, arr, top);
}

HuffmanTreeNode *giveTree(unsigned char (*data)[3],
						  int freq[], int size)
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

	// Generate Huffman Encoding
	// Tree and get the root node
	return generateTree(pq);
}

void encodeHuffman(HuffmanTreeNode *root, unsigned char header[], unsigned char *image, int size)
{
	FILE *write;
	int i = 0, j = 0, k = 0;
	write = fopen("Test1.txt", "w");
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

	/*testing write bits to the file*/
	int arr[MAX_SIZE], top = 0;
	rgbtoCodes(root, arr, top, size, image);
	printf("hi");
	bitset<8> writebit;
	unsigned long n;
	ofstream output("Test1.txt", ios::app);
	// n = writebit.to_ulong();
	// output.write(reinterpret_cast<const char *>(&n), sizeof(n));
	for (int j = 0; j < 20; j++)
	{
		if (j % 2 == 0)
		{
			writebit.set(k, 0);
		}
		else
		{
			writebit.set(k, 1);
		}
		k++;
		if (k == 8)
		{
			n = writebit.to_ulong();
			output.write(reinterpret_cast<const char *>(&n), sizeof(n));
			k = 0;
			writebit.reset();
		}
	}
	n = writebit.to_ulong();
	output.write(reinterpret_cast<const char *>(&n), sizeof(n));
	output.close();
}

// travers the tree but not working
void rgbtoCodes(HuffmanTreeNode *root,
				int arr[], int top, int size, unsigned char *image)
{
	HuffmanDictPtr dict;
    dict = (HuffmanDictPtr)malloc(sizeof(HuffmanDict));
    dictionary(root, arr, top, dict, 1);
    printf("(%hhu, %hhu, %hhu)", dict->data[0], dict->data[1], dict->data[2]);
    printf("hi");
}

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

void decodeHuffman()
{
	unsigned char header[15];
	FILE *read = fopen("Test1.txt", "r");
	if (read == NULL)
	{
		printf("File tidak ditemukan\n");
	}
	HuffmanTreeNode *root = treeisBack(read);
	int arr[MAX_SIZE], top = 0;

	printCodes(root, arr, top);
	readHeader(read, header);
}

// read the tree from the file
HuffmanTreeNode *treeisBack(FILE *read)
{
	char c;
	unsigned char data[3];
	while (c != '\n')
	{
		c = fgetc(read);
		if (c == '1')
		{
			fscanf(read, "%hhu %hhu %hhu", &data[0], &data[1], &data[2]);
			printf("(%hhu, %hhu, %hhu)\n", data[0], data[1], data[2]);
			return new HuffmanTreeNode(data, 0);
		}
		else
		{
			HuffmanTreeNode *left = treeisBack(read);
			HuffmanTreeNode *right = treeisBack(read);
			HuffmanTreeNode *root = new HuffmanTreeNode(0, 0);
			root->left = left;
			root->right = right;
			return root;
		}
	}
	return 0;
}

// just read the header from txt
void readHeader(FILE *read, unsigned char *header)
{
	int i = 0, j = 0;
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

//make the list of leaf node with the way of traversing the tree
void dictionary(HuffmanTreeNode *root,
				int arr[], int top, HuffmanDictPtr dict, int i)
{
	if (i != 1) {
        dict->next = (HuffmanDictPtr)malloc(sizeof(HuffmanDict));
        dict = dict->next;
    }
    i++;
    if (root->left) {
        arr[top] = 0;
        dictionary(root->left, arr, top + 1, dict, i);
    }
    if (root->right) {
        arr[top] = 1;
        dictionary(root->right, arr, top + 1, dict, i);
    }
    if (!root->left && !root->right) {
        dict->data[0] = root->data[0];
        dict->data[1] = root->data[1];
        dict->data[2] = root->data[2];
        for (int j = 0; j < top; j++) {
            dict->code[j] = arr[j];
        }
        dict->code[top] = -1;
    }
}