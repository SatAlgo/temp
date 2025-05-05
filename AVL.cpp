#include <iostream>
#include <stack>
using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;
    int height;

    Node(int value) {
        data = value;
        left = right = nullptr;
        height = 1;
    }
};

// Get height of node
int height(Node* node) {
    return node ? node->height : 0;
}

// Get balance factor of node
int balanceFactor(Node* node) {
    return node ? height(node->left) - height(node->right) : 0;
}

// Right rotation
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

// Left rotation
Node* leftRotate(Node* y) {
    Node* x = y->right;
    Node* T2 = x->left;

    x->left = y;
    y->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return x;
}

// Insert into AVL tree
Node* insert(Node* node, int value) {
    if (!node) return new Node(value);

    if (value < node->data)
        node->left = insert(node->left, value);
    else if (value > node->data)
        node->right = insert(node->right, value);
    else {
        cout << "Duplicate value ignored: " << value << endl;
        return node;
    }

    node->height = 1 + max(height(node->left), height(node->right));
    int balance = balanceFactor(node);

    // Left Left Case
    if (balance > 1 && value < node->left->data)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && value > node->right->data)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && value > node->left->data) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && value < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Recursive Traversals
void inorderRecursive(Node* root) {
    if (root) {
        inorderRecursive(root->left);
        cout << root->data << " ";
        inorderRecursive(root->right);
    }
}

void preorderRecursive(Node* root) {
    if (root) {
        cout << root->data << " ";
        preorderRecursive(root->left);
        preorderRecursive(root->right);
    }
}

void postorderRecursive(Node* root) {
    if (root) {
        postorderRecursive(root->left);
        postorderRecursive(root->right);
        cout << root->data << " ";
    }
}

// Non-Recursive Traversals
void inorderNonRecursive(Node* root) {
    stack<Node*> s;
    Node* current = root;
    while (current || !s.empty()) {
        while (current) {
            s.push(current);
            current = current->left;
        }
        current = s.top(); s.pop();
        cout << current->data << " ";
        current = current->right;
    }
}

void preorderNonRecursive(Node* root) {
    if (!root) return;
    stack<Node*> s;
    s.push(root);
    while (!s.empty()) {
        Node* node = s.top(); s.pop();
        cout << node->data << " ";
        if (node->right) s.push(node->right);
        if (node->left) s.push(node->left);
    }
}

void postorderNonRecursive(Node* root) {
    if (!root) return;
    stack<Node*> s1, s2;
    s1.push(root);
    while (!s1.empty()) {
        Node* node = s1.top(); s1.pop();
        s2.push(node);
        if (node->left) s1.push(node->left);
        if (node->right) s1.push(node->right);
    }
    while (!s2.empty()) {
        cout << s2.top()->data << " ";
        s2.pop();
    }
}

// Main function
int main() {
    Node* root = nullptr;
    int n, value;

    cout << "Enter number of nodes to insert: ";
    cin >> n;
    cout << "Enter " << n << " values:\n";
    for (int i = 0; i < n; ++i) {
        cin >> value;
        root = insert(root, value);
    }

    cout << "\nInorder Recursive: ";
    inorderRecursive(root);
    cout << "\nPreorder Recursive: ";
    preorderRecursive(root);
    cout << "\nPostorder Recursive: ";
    postorderRecursive(root);

    cout << "\nInorder Non-Recursive: ";
    inorderNonRecursive(root);
    cout << "\nPreorder Non-Recursive: ";
    preorderNonRecursive(root);
    cout << "\nPostorder Non-Recursive: ";
    postorderNonRecursive(root);

    return 0;
}
