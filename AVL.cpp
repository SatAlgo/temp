#include <bits/stdc++.h>
using namespace std;

struct Node {
    int key, height;
    Node *left, *right;
    Node(int k) : key(k), height(1), left(nullptr), right(nullptr) {}
};

int height(Node *n) { return n ? n->height : 0; }
int getBalance(Node *n) { return n ? height(n->left) - height(n->right) : 0; }

Node *rightRotate(Node *y) {
    Node *x = y->left, *T2 = x->right;
    x->right = y; y->left = T2;
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
}

Node *leftRotate(Node *x) {
    Node *y = x->right, *T2 = y->left;
    y->left = x; x->right = T2;
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
}

Node* insert(Node* node, int key) {
    if (!node) return new Node(key);
    if (key < node->key) node->left = insert(node->left, key);
    else if (key > node->key) node->right = insert(node->right, key);
    else return node;

    node->height = 1 + max(height(node->left), height(node->right));
    int balance = getBalance(node);

    if (balance > 1 && key < node->left->key) return rightRotate(node);
    if (balance < -1 && key > node->right->key) return leftRotate(node);
    if (balance > 1 && key > node->left->key) { node->left = leftRotate(node->left); return rightRotate(node); }
    if (balance < -1 && key < node->right->key) { node->right = rightRotate(node->right); return leftRotate(node); }
    return node;
}

void inOrder(Node *root) {
    if (!root) return;
    inOrder(root->left);
    cout << root->key << " ";
    inOrder(root->right);
}

void preOrder(Node *root) {
    if (!root) return;
    cout << root->key << " ";
    preOrder(root->left);
    preOrder(root->right);
}

void postOrder(Node *root) {
    if (!root) return;
    postOrder(root->left);
    postOrder(root->right);
    cout << root->key << " ";
}

void nonRecursiveInOrder(Node *root) {
    stack<Node*> st;
    Node *curr = root;
    while (curr || !st.empty()) {
        while (curr) {
            st.push(curr);
            curr = curr->left;
        }
        curr = st.top(); st.pop();
        cout << curr->key << " ";
        curr = curr->right;
    }
}

void nonRecursivePreOrder(Node *root) {
    if (!root) return;
    stack<Node*> st;
    st.push(root);
    while (!st.empty()) {
        Node *curr = st.top(); st.pop();
        cout << curr->key << " ";
        if (curr->right) st.push(curr->right);
        if (curr->left) st.push(curr->left);
    }
}

void nonRecursivePostOrder(Node *root) {
    if (!root) return;
    stack<Node*> st1, st2;
    st1.push(root);
    while (!st1.empty()) {
        Node *curr = st1.top(); st1.pop();
        st2.push(curr);
        if (curr->left) st1.push(curr->left);
        if (curr->right) st1.push(curr->right);
    }
    while (!st2.empty()) {
        cout << st2.top()->key << " ";
        st2.pop();
    }
}

bool search(Node *root, int key) {
    while (root) {
        if (key == root->key) return true;
        root = key < root->key ? root->left : root->right;
    }
    return false;
}

void displayMenu() {
    cout << "\n================= AVL Tree Menu =================\n";
    cout << "1. Insert a Node\n";
    cout << "2. Recursive In-order Traversal\n";
    cout << "3. Recursive Pre-order Traversal\n";
    cout << "4. Recursive Post-order Traversal\n";
    cout << "5. Non-Recursive In-order Traversal\n";
    cout << "6. Non-Recursive Pre-order Traversal\n";
    cout << "7. Non-Recursive Post-order Traversal\n";
    cout << "8. Search for a Node\n";
    cout << "9. Exit\n";
    cout << "================================================\n";
    cout << "Enter your choice: ";
}

void displayTraversal(const string& type, void (*traversal)(Node *), Node *root) {
    cout << "\n" << type << " Traversal: ";
    traversal(root);
    cout << "\n------------------------------------------------\n";
}

int main() {
    Node *root = nullptr;
    int choice, num;

    do {
        displayMenu();
        cin >> choice;
        cout << "\n";

        switch (choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> num;
                root = insert(root, num);
                cout << num << " inserted successfully!\n";
                break;
            case 2:
                displayTraversal("Recursive In-order", inOrder, root);
                break;
            case 3:
                displayTraversal("Recursive Pre-order", preOrder, root);
                break;
            case 4:
                displayTraversal("Recursive Post-order", postOrder, root);
                break;
            case 5:
                displayTraversal("Non-Recursive In-order", nonRecursiveInOrder, root);
                break;
            case 6:
                displayTraversal("Non-Recursive Pre-order", nonRecursivePreOrder, root);
                break;
            case 7:
                displayTraversal("Non-Recursive Post-order", nonRecursivePostOrder, root);
                break;
            case 8:
                cout << "Enter value to search: ";
                cin >> num;
                cout << (search(root, num) ? "Node found!" : "Node not found!") << "\n";
                break;
            case 9:
                cout << "Exiting program. Thank you!\n";
                break;
            default:
                cout << "Invalid choice! Please enter a number between 1-9.\n";
        }
    } while (choice != 9);

    return 0;
}
