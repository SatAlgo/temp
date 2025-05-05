#include <iostream>
#include <stack>
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

// Non-recursive Inorder traversal
void InorderTraversal(Node* root) {
    stack<Node*> s;
    Node* current = root;
    
    while (current != NULL || !s.empty()) {
        while (current != NULL) {
            s.push(current);
            current = current->left;
        }
        current = s.top();
        s.pop();
        cout << current->data << " ";
        current = current->right;
    }
}

// Non-recursive Preorder traversal
void PreorderTraversal(Node* root) {
    if (root == NULL) return;
    stack<Node*> s;
    s.push(root);
    
    while (!s.empty()) {
        Node* current = s.top();
        s.pop();
        cout << current->data << " ";
        
        if (current->right != NULL) {
            s.push(current->right);
        }
        if (current->left != NULL) {
            s.push(current->left);
        }
    }
}

// Non-recursive Postorder traversal
void PostorderTraversal(Node* root) {
    if (root == NULL) return;
    stack<Node*> s1, s2;
    s1.push(root);
    
    while (!s1.empty()) {
        Node* current = s1.top();
        s1.pop();
        s2.push(current);
        
        if (current->left != NULL) {
            s1.push(current->left);
        }
        if (current->right != NULL) {
            s1.push(current->right);
        }
    }
    
    while (!s2.empty()) {
        Node* current = s2.top();
        s2.pop();
        cout << current->data << " ";
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
   
    // Print the preorder traversal of the tree
    cout << "Preorder Traversal of the Binary Search Tree: ";
    PreorderTraversal(root);
    cout << endl;
   
    // Print the postorder traversal of the tree
    cout << "Postorder Traversal of the Binary Search Tree: ";
    PostorderTraversal(root);
    cout << endl;

    return 0;
}
