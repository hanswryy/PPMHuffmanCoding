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
		FILE  *file = fopen("code.txt","a");
		//printf("(%hhu, %hhu, %hhu)", root->data[0], root->data[1], root->data[2]);
		fprintf(file, "%hhu %hhu %hhu ", root->data[0], root->data[1], root->data[2]);
		for (int i = 0; i < top; i++)
		{
			//cout << arr[i];
			fprintf(file, "%d", arr[i]);
		}
		//cout << endl;
		fprintf(file, "\n");
		fclose(file);
	}
}

void printTree(HuffmanTreeNode *root,
				int arr[], int top)
{
	// Assign 0 to the left node
	// and recur
	if (root->left)
	{
		arr[top] = 0;
		printTree(root->left,
				   arr, top + 1);
	}

	// Assign 1 to the right
	// node and recur
	if (root->right)
	{
		arr[top] = 1;
		printTree(root->right, arr, top + 1);
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

void fixEncode(unsigned char *image, int size)
{
	printf("%hhu %hhu %hhu\n", image[0], image[1], image[2]);
	int k = 7;
	bitset<8> writebit;
	unsigned long n;
	ofstream output("Test1.txt", ios::binary);
	unsigned char data[3];
	char code[100];
	FILE * file = fopen("code.txt", "r");
	for(int i = 0; i < size; i+=3){
		while(!feof(file)){
			fscanf(file, "%hhu %hhu %hhu ", &data[0], &data[1], &data[2]);
			fscanf(file, "%s", code);
			if (data[0] == image[i] && data[1] == image[i+1] && data[2] == image[i+2])
			{
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
		fseek(file, 0, SEEK_SET);
	}
	n = writebit.to_ulong();
	output.write(reinterpret_cast<const char *>(&n), sizeof(n));
	output.close();
	fclose(file);
	remove("code.txt");
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
	//printCodes(root, arr, top);
}

HuffmanTreeNode *giveTree(unsigned char (*data)[3],
						  int freq[], int size, int* arrsize)
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

void encodeHuffman(HuffmanTreeNode *root, unsigned char header[], unsigned char *image, int size)
{
	//ofstream write("Test1.txt", ios::ate);
	fixEncode(image, size);
	FILE *write;
	int i = 0, j = 0, k = 0;
	write = fopen("Test1.txt", "ab");
	//fprintf(write, "\n");
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
	//write.close();
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

void decodeHuffman(unsigned char *image, unsigned char header[], int size)
{
	FILE *read = fopen("Test1.txt", "r");
	//ifstream read("Test1.txt", ios::in);
	if (read == NULL)
	{
		printf("File tidak ditemukan\n");
	}
	HuffmanTreeNode *root = treeisBack(read);
	int arr[MAX_SIZE], top = 0;
	printTree(root, arr, top);
	ConvertHuffman(root, image, size);
	readHeader(read, header);
	printf("header : %c%c", header[0], header[1]);
	fclose(read);
	//read.close();
//	ifstream input("Test1.txt", ios::binary);
//	
//	bitset<8> readbit;
//	unsigned long byte;
//	cout << endl;
//	for(int i = 0; i < 100; i++){
//		input.read(reinterpret_cast<char *>(&byte), sizeof(byte));
//		// print the byte
//		readbit = byte;
//		cout << readbit << endl;
//	}
//	input.close();

}

// read the tree from the file
HuffmanTreeNode *treeisBack(FILE *read)
{
	char c;
	unsigned char data[3];
	// stop when it reads newline
	while ((c = fgetc(read)) != '\n')
	{
//		printf("%c", c);
		if(c == '1'){
			fscanf(read, "%hhu %hhu %hhu", &data[0], &data[1], &data[2]);
			printf("(%hhu, %hhu, %hhu)\n", data[0], data[1], data[2]);
			return new HuffmanTreeNode(data, 0);
		}
		else if (c == '0') {
			HuffmanTreeNode *left = treeisBack(read);
			HuffmanTreeNode *right = treeisBack(read);
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
void readHeader(FILE *read, unsigned char header[])
{
	while(fgetc(read)!='P'){
		
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

void ConvertHuffman(HuffmanTreeNode* root, unsigned char *image, int size){
    ifstream input("Test1.txt", ios::binary);
	bitset<8> readbit;
	unsigned long byte;
    int j = 0;
    unsigned char info[3];
    HuffmanTreeNode* temp;
    temp = root;
    while (input.read(reinterpret_cast<char*>(&byte), sizeof(byte))) {
    	readbit = byte;
    	for (int k=0; k<8; k++){
    		Traverse(&temp, readbit.to_string()[k], info);
			if(info[0]!=0 && info[1]!=0 && info[2]!=0){
				for (int i=0; i<3; i++){
	            	if (j<size){
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
	


void Traverse(HuffmanTreeNode** root, char c, unsigned char info[3]){ 
    if (c == '0'){
        *root = (*root)->left;
        info[0] = 0;
        info[1] = 0;
        info[2] = 0;
    }
    else if (c == '1'){
        *root = (*root)->right;
        info[0] = 0;
        info[1] = 0;
        info[2] = 0;
    }
    
    if(!(*root)->left && !(*root)->right){ 
        info[0] = (*root)->data[0];
        info[1] = (*root)->data[1];
        info[2] = (*root)->data[2];
    }
}
