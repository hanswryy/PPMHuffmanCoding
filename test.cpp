// C++ Program for Huffman Coding
// using Priority Queue
#include <iostream>
#include <queue>
using namespace std;

// Maximum Height of Huffman Tree.
#define MAX_SIZE 100

class HuffmanTreeNode {
public:
	// Stores character
	unsigned char data[3];

	// Stores frequency of
	// the character
	int freq;

	// Left child of the
	// current node
	HuffmanTreeNode* left;

	// Right child of the
	// current node
	HuffmanTreeNode* right;

	// Initializing the
	// current node
	HuffmanTreeNode(unsigned char character[3],
					int frequency)
	{
		data[0] = character[0];
		data[1] = character[1];
		data[2] = character[2];
		freq = frequency;
		left = right = NULL;
	}
};

// Custom comparator class
class Compare {
public:
	bool operator()(HuffmanTreeNode* a,
					HuffmanTreeNode* b)
	{
		// Defining priority on
		// the basis of frequency
		return a->freq > b->freq;
	}
};

// Function to generate Huffman
// Encoding Tree
HuffmanTreeNode* generateTree(priority_queue<HuffmanTreeNode*,
							vector<HuffmanTreeNode*>,
											Compare> pq)
{

	// We keep on looping till
	// only one node remains in
	// the Priority Queue
	while (pq.size() != 1) {

		// Node which has least
		// frequency
		HuffmanTreeNode* left = pq.top();

		// Remove node from
		// Priority Queue
		pq.pop();

		// Node which has least
		// frequency
		HuffmanTreeNode* right = pq.top();

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
		unsigned char temp[3] = {'$','$','$'};
		HuffmanTreeNode* node = new HuffmanTreeNode(temp,
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
void printCodes(HuffmanTreeNode* root, int arr[], int top)
{
    // Assign 0 to the left node and recur
    if (root->left) {
        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }

    // Assign 1 to the right node and recur
    if (root->right) {
        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }

    // If this is a leaf node, print the character and its Huffman code
    if (!root->left && !root->right) {
	    if (root->data[0] != 0 && root->data[1] != 0 && root->data[2] != 0){
			printf("Info : %d, %d, %d\t", root->data[0], root->data[1], root->data[2]);
	        for (int i = 0; i < top; i++) {
	            printf("%d", arr[i]);
	        }
	        printf("\n");
	    }
    }
}


void HuffmanCodes(unsigned char (*data)[3],
				int freq[], int size)
{

	// Declaring priority queue
	// using custom comparator
	priority_queue<HuffmanTreeNode*,
				vector<HuffmanTreeNode*>,
				Compare>
		pq;

	// Populating the priority
	// queue
	for (int i = 0; i < size; i++) {
		HuffmanTreeNode* newNode;
		if (freq[i] > 0){
			newNode	= new HuffmanTreeNode(data[i], freq[i]);
			pq.push(newNode);
		}
	}

	// Generate Huffman Encoding
	// Tree and get the root node
	HuffmanTreeNode* root = generateTree(pq);

	// Print Huffman Codes
	int arr[MAX_SIZE], top = 0;
	printCodes(root, arr, top);
}

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
//    printf("\nsize : %d\n", size);
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
//		printf("(%d, %d, %d) : %d\n", data[index][0], data[index][1],data[index][2], freq[i]);
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

// Driver Code
int main()
{

	unsigned char header[15], *image;
	readImage(header, image); 
	
	int width, height, pos = 3;
	width = getDimension(header, pos);
	pos++;
	height = getDimension(header, pos);
	printf("\nWidth : %d, Height : %d\n", width, height);

	int *freq = new int[width*height];
    unsigned char (data)[3] = (unsigned char ()[3])calloc(width*height, sizeof(unsigned char[3]));

    if (freq == NULL || data == NULL) {
        printf("Failed to allocate memory\n");
        return 1;
    }
	countPixelFrequency(image, width, height, freq, data);
	printPixelFrequency(freq, data);
	HuffmanCodes(data, freq, width*height);
	free(image);
    free(freq);
    free(data);
	return 0;
}
