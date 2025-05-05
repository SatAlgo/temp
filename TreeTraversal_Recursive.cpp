#include<iostream>
using namespace std;

struct Node {
    int data;        // Data element of the node
    Node* left;      // Pointer to the left child node
    Node* right;     // Pointer to the right child node
};

// Function to create a new node with given data
Node* GetNewNode(int data) {
    Node* newNode = new Node();
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to insert a new node in the Binary Search Tree
Node* Insert(Node* root, int data) {
    if (root == NULL) {
        // If root is NULL, create a new node and return it
        root = GetNewNode(data);
    } else if (data < root->data) {
        // If data is smaller than current node, insert it in the left subtree
        root->left = Insert(root->left, data);
    } else {
        // If data is larger than current node, insert it in the right subtree
        root->right = Insert(root->right, data);
    }
    return root;
}

// Function to do inorder traversal of the tree
void InorderTraversal(Node* root) {
    if (root != NULL) {
        InorderTraversal(root->left);    // Traverse left subtree
        cout << root->data << " ";       // Print node data
        InorderTraversal(root->right);   // Traverse right subtree
    }
}

// Preorder Traversal (Root, Left, Right)
void PreorderTraversal(Node* root) {
    if (root != NULL) {
        cout << root->data << " ";       // Print node data (Root)
        PreorderTraversal(root->left);    // Traverse left subtree
        PreorderTraversal(root->right);   // Traverse right subtree
    }
}

// Postorder Traversal (Left, Right, Root)
void PostorderTraversal(Node* root) {
    if (root != NULL) {
        PostorderTraversal(root->left);    // Traverse left subtree
        PostorderTraversal(root->right);   // Traverse right subtree
        cout << root->data << " ";         // Print node data (Root)
    }
}


int main() {
    int n;
    cout << "Enter the number of nodes you want to insert: " << endl;
    cin >> n;
   
    int data;
    Node* root = NULL;  // Initialize root as NULL, we'll set it later.
   
    cout << "Enter root data: " << endl;
    cin >> data;
   
    root = GetNewNode(data);  // Create root node

    cout << "Enter other nodes:" << endl;
    for (int i = 0; i < n - 1; i++) {
        cout << "Enter node data: ";
        cin >> data;
        root = Insert(root, data);  // Insert data into the tree
    }

    // Print the inorder traversal of the tree
    cout << "Inorder Traversal of the Binary Search Tree: ";
    InorderTraversal(root);
    cout << endl;
   
    cout << "Preorder Traversal of the Binary Search Tree: ";
    PreorderTraversal(root);
    cout << endl;
   
    cout << "Postorder Traversal of the Binary Search Tree: ";
    PostorderTraversal(root);
    cout << endl;

    return 0;
}