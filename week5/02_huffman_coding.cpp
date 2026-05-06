/*
 * ============================================================================
 *  HUFFMAN CODING (Greedy Algorithm)
 * ============================================================================
 *  PROBLEM:
 *  - Given a set of characters and their frequencies, find an optimal prefix 
 *    code for data compression.
 *  - Prefix Code: No codeword is a prefix of another codeword. This avoids 
 *    ambiguity during decoding.
 *
 *  GREEDY APPROACH:
 *  - Build a binary tree from the bottom up.
 *  - Greedy Choice: Always merge the two nodes with the LOWEST frequencies.
 *  - Doing this ensures that the least frequent characters end up deepest in 
 *    the tree (getting longer codes), and the most frequent characters stay 
 *    near the root (getting shorter codes).
 *
 *  IMPLEMENTATION:
 *  - We use a Min-Priority Queue to efficiently extract the two smallest 
 *    frequencies.
 *  - Time Complexity: O(N log N) where N is the number of unique characters.
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <deque>
#include <limits>
#include <climits>
#include <cstring>
#include <numeric>

using namespace std;

// ─────────────────────────────────────────────────────────────────────────────
//  HUFFMAN CODING IMPLEMENTATION
// ─────────────────────────────────────────────────────────────────────────────
// Tree Node
struct MinHeapNode {
    char data;
    unsigned freq;
    MinHeapNode *left, *right;

    MinHeapNode(char data, unsigned freq) {
        this->left = this->right = nullptr;
        this->data = data;
        this->freq = freq;
    }
};

// Comparator for the priority queue
struct compare {
    bool operator()(MinHeapNode* l, MinHeapNode* r) {
        return (l->freq > r->freq);
    }
};

// Recursively print the generated Huffman codes from the tree
void printCodes(struct MinHeapNode* root, string str) {
    if (!root) return;

    // If this is a leaf node, print the character and its code
    if (root->data != '$') {
        cout << root->data << ": " << str << "\n";
    }

    // Traverse left (append '0')
    printCodes(root->left, str + "0");
    
    // Traverse right (append '1')
    printCodes(root->right, str + "1");
}

// Build the Huffman Tree and print codes
void HuffmanCodes(vector<char>& data, vector<int>& freq) {
    MinHeapNode *left, *right, *top;

    // Create a min heap & inserts all characters of data[]
    priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> minHeap;

    for (int i = 0; i < data.size(); ++i) {
        minHeap.push(new MinHeapNode(data[i], freq[i]));
    }

    // Iterate while size of heap doesn't become 1
    while (minHeap.size() != 1) {
        // Extract the two minimum freq items from min heap
        left = minHeap.top();
        minHeap.pop();

        right = minHeap.top();
        minHeap.pop();

        // Create a new internal node with frequency equal to the sum of the 
        // two nodes frequencies. Make the two extracted node as left and right 
        // children of this new node. '$' is a special value for internal nodes.
        top = new MinHeapNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;

        minHeap.push(top);
    }

    // Print Huffman codes using the Huffman tree built above
    cout << "Huffman Codes:\n";
    printCodes(minHeap.top(), "");
}

// ─────────────────────────────────────────────────────────────────────────────
//  DRIVER
// ─────────────────────────────────────────────────────────────────────────────
int main() {
    cout << "=== HUFFMAN CODING ===\n";
    vector<char> arr = {'a', 'b', 'c', 'd', 'e', 'f'};
    vector<int> freq = {5, 9, 12, 13, 16, 45};

    cout << "Characters and Frequencies:\n";
    for(int i = 0; i < arr.size(); i++){
        cout << arr[i] << " : " << freq[i] << "\n";
    }
    cout << "\n";

    HuffmanCodes(arr, freq);

    return 0;
}
