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
    HuffmanTreeNode(unsigned char character[],
                    int frequency)
    {
        for (int i = 0; i < 3; i++) {
            data[i] = character[i];
        }
        freq = frequency;
        left = right = NULL;
    }
};