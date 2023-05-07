#include "header.h"

// Returns a new tree node 
struct TreeNode *newTreeNode(int freq, unsigned char item[3])
{
	struct TreeNode *node = (struct TreeNode *) malloc(sizeof(struct TreeNode));
	if (node == NULL)
	{
		printf("\n Memory overflow , When creating a new TreeNode");
	}
	else
	{
		for (int i = 0; i < 3; i++) {
            node->item[i] = item[i];
        }
		node->freq = freq;
		node->left = NULL;
		node->right = NULL;
	}
	return node;
}

// Get a front element of queue
struct TreeNode *peek(struct PriorityQueue *q)
{
	if (isEmpty(q) == 1)
	{
		// When stack is empty
		return NULL;
	}
	else
	{
		return q->front->n;
	}
}

// Construct Huffman Code Tree
struct TreeNode *buildHuffmanCodes(unsigned char (*value)[3], int frequency[], int n)
{
	struct PriorityQueue *q = newPriorityQueue();
	struct TreeNode *root = NULL;
	struct TreeNode *n1 = NULL;
	struct TreeNode *n2 = NULL;
	// First add all elements into priority queue
	for (int i = 0; i < n; ++i)
	{
		root = newTreeNode(frequency[i], value[i]);
		enQueue(q, root);
	}
//	printQdata(q);
	// Execute loop until the priority queue contains more than 1 node
	while (isSize(q) > 1)
	{
		// Get first smallest node  
		n1 = peek(q);
		//Remove a front element
		deQueue(q);
		// Get second smallest node
		n2 = peek(q);
		// Remove a front element
		deQueue(q);
		// Make new node using two smallest node
		unsigned char empty[3] = {'-', '-', '-'};
		root = newTreeNode(n1->freq + n2->freq, empty);
		// Add new node into priority queue 
		enQueue(q, root);
		// Set left and right child
		root->left = n1;
		root->right = n2;
	}
	return root;
}

void printCodes(struct TreeNode* root,
				int arr[], int top)
{
	// Assign 0 to the left node
	// and recur
	if (root->left) {
		arr[top] = 0;
		printCodes(root->left,
				arr, top + 1);
	}

	// Assign 1 to the right
	// node and recur
	if (root->right) { 
		arr[top] = 1;
		printCodes(root->right, arr, top + 1);
	}

	// If this is a leaf node,
	// then we print root->data

	// We also print the code
	// for this character from arr
	if (!root->left && !root->right) {
        printf("(%hhu, %hhu, %hhu) \n\t", root->item[0], root->item[1],root->item[2]);		
		for (int i = 0; i < top; i++) {
			cout << arr[i];
		}
		cout << endl;
	}
}

//void PrintTree(struct TreeNode* root, char tab[]){
//	char temp[10];
//	strcpy(temp,tab);
//	strcat(temp,"-");
//	if(root == NULL) return;
//	if(root != NULL){
//		if(root->item == '\n'){
//			printf("%s[%i]\n",temp,root->freq);	
//		}
//		else{
//			printf("%s%c[%i]\n",temp,root->item,root->freq);
//		}
//		PrintTree(root->left,temp);
//		PrintTree(root->right,temp);
//	}
//}
