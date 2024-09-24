#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int value) : data(value), left(NULL), right(NULL) {}
};

class BinarySearchTree {
public:
    Node* insert(Node* root, int value) {
        if (!root) return new Node(value);
        if (value < root->data)
            root->left = insert(root->left, value);
        else if (value > root->data) // Avoid duplicates
            root->right = insert(root->right, value);
        return root;
    }

    void inOrder(Node* root) {
        if (!root) return;
        inOrder(root->left);
        cout << root->data << " ";
        inOrder(root->right);
    }

    Node* generateRandomTree(int n, int valueRange) {
        Node* root = NULL;
        while (n > 0) {
            int randomValue = rand() % valueRange + 1;
            if (!search(root, randomValue)) { // Check for duplicates
                root = insert(root, randomValue);
                n--;
            }
        }
        return root;
    }

    bool search(Node* root, int value) {
        if (!root) return false;
        if (root->data == value) return true;
        if (value < root->data)
            return search(root->left, value);
        else
            return search(root->right, value);
    }

    int height(Node* root) {
        if (!root) return 0;
        return 1 + max(height(root->left), height(root->right));
    }

    // Destructor to free memory
    void deleteTree(Node* root) {
        if (root) {
            deleteTree(root->left);
            deleteTree(root->right);
            delete root;
        }
    }
};

int main() {
    srand(time(0)); // Seed random number generator

    BinarySearchTree bst;
    Node* root = NULL;

    int numNodes, valueRange;
    cout << "Enter the number of nodes for the random tree: ";
    cin >> numNodes;
    while(numNodes <= 0) {
        cout << "Please enter a positive number for nodes: ";
        cin >> numNodes;
    }

    cout << "Enter the range of node values (1 to valueRange): ";
    cin >> valueRange;
    while(valueRange <= 0) {
        cout << "Please enter a positive number for value range: ";
        cin >> valueRange;
    }

    root = bst.generateRandomTree(numNodes, valueRange);

    cout << "In-order Traversal of Random Tree: ";
    bst.inOrder(root);
    cout << endl;

    cout << "Height of the Random Tree: " << bst.height(root) << endl;

    bst.deleteTree(root); // Free allocated memory
    return 0;
}
