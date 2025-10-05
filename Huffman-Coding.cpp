#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct TreeNode {
    char letter;
    int frequency;
    TreeNode* leftChild;
    TreeNode* rightChild;
};

TreeNode* createNode(char letter, int frequency) {
    TreeNode* temp = new TreeNode();
    temp->letter = letter;
    temp->frequency = frequency;
    temp->leftChild = NULL;
    temp->rightChild = NULL;
    return temp;
}

struct myComparator {
    bool operator()(TreeNode* node1, TreeNode* node2) {
        return node1->frequency > node2->frequency;
    }
};

void printPreorder(TreeNode* currentNode, string currentCode) {
    if (currentNode == NULL)
        return;

    if (currentNode->leftChild == NULL && currentNode->rightChild == NULL) {
        cout << currentCode << " ";
    }

    printPreorder(currentNode->leftChild, currentCode + "0");   
    printPreorder(currentNode->rightChild, currentCode + "1");  
}

int main() {
    string characters = "abcdef";
    int frequencies[] = {5, 9, 12, 13, 16, 45};
    int totalCharacters = characters.size();

    priority_queue<TreeNode*, vector<TreeNode*>, myComparator> minHeap;

    for (int i = 0; i < totalCharacters; i++) {
        minHeap.push(createNode(characters[i], frequencies[i]));
    }

    while (minHeap.size() > 1) {
        TreeNode* small1 = minHeap.top(); 
        minHeap.pop();
        
        TreeNode* small2 = minHeap.top(); 
        minHeap.pop();

        TreeNode* parentNode = createNode('*', small1->frequency + small2->frequency);
        parentNode->leftChild = small1;
        parentNode->rightChild = small2;

        minHeap.push(parentNode);
    }

    TreeNode* treeRoot = minHeap.top();
    printPreorder(treeRoot, "");

    return 0;
}
/*
Output:
   0   100   101   1100   1101   111
*/
