#include <iostream>
#include <stack>
#include <queue>
using namespace std;

struct Node {
    int value;
    Node* left;
    Node* right;
};

Node* createNode(int value) {
    Node* newNode = new Node();
    newNode->value = value;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

Node* addNode(Node* root, int value) {
    if (root == nullptr) {
        root = createNode(value);
    } else {
        if (value <= root->value) {
            root->left = addNode(root->left, value);
        } else {
            root->right = addNode(root->right, value);
        }
    }
    return root;
}

void inOrder(Node* root) {
    if (root == nullptr) return;
    inOrder(root->left);
    cout << root->value << " ";
    inOrder(root->right);
}

void preOrder(Node* root) {
    if (root == nullptr) return;
    cout << root->value << " ";
    preOrder(root->left);
    preOrder(root->right);
}

void postOrder(Node* root) {
    if (root == nullptr) return;
    postOrder(root->left);
    postOrder(root->right);
    cout << root->value << " ";
}

void inOrderIter(Node* root) {
    stack<Node*> s;
    Node* curr = root;
    while (curr != nullptr || !s.empty()) {
        while (curr != nullptr) {
            s.push(curr);
            curr = curr->left;
        }
        curr = s.top();
        s.pop();
        cout << curr->value << " ";
        curr = curr->right;
    }
}

void preOrderIter(Node* root) {
    if (root == nullptr) return;
    stack<Node*> s;
    s.push(root);
    while (!s.empty()) {
        Node* curr = s.top();
        s.pop();
        cout << curr->value << " ";
        if (curr->right) s.push(curr->right);
        if (curr->left) s.push(curr->left);
    }
}

void postOrderIter(Node* root) {
    if (root == nullptr) return;
    stack<Node*> s1, s2;
    s1.push(root);
    while (!s1.empty()) {
        Node* curr = s1.top();
        s1.pop();
        s2.push(curr);
        if (curr->left) s1.push(curr->left);
        if (curr->right) s1.push(curr->right);
    }
    while (!s2.empty()) {
        cout << s2.top()->value << " ";
        s2.pop();
    }
}

void levelOrder(Node* root) {
    if (root == nullptr) return;
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* curr = q.front();
        q.pop();
        cout << curr->value << " ";
        if (curr->left) q.push(curr->left);
        if (curr->right) q.push(curr->right);
    }
}

bool searchIter(Node* root, int value) {
    while (root != nullptr) {
        if (root->value == value) return true;
        else if (root->value > value) root = root->left;
        else root = root->right;
    }
    return false;
}

bool searchRec(Node* root, int value) {
    if (root == nullptr) return false;
    if (root->value == value) return true;
    else if (root->value > value) return searchRec(root->left, value);
    else return searchRec(root->right, value);
}

Node* findMin(Node* root) {
    while (root->left != nullptr) {
        root = root->left;
    }
    return root;
}

Node* findMax(Node* root) {
    while (root->right != nullptr) {
        root = root->right;
    }
    return root;
}

Node* deleteNode(Node* root, int value) {
    if (root == nullptr) return root;
    if (value < root->value) root->left = deleteNode(root->left, value);
    else if (value > root->value) root->right = deleteNode(root->right, value);
    else {
        if (root->left == nullptr && root->right == nullptr) {
            delete root;
            root = nullptr;
        } else if (root->left == nullptr) {
            Node* temp = root;
            root = root->right;
            delete temp;
        } else if (root->right == nullptr) {
            Node* temp = root;
            root = root->left;
            delete temp;
        } else {
            Node* temp = findMin(root->right);
            root->value = temp->value;
            root->right = deleteNode(root->right, temp->value);
        }
    }
    return root;
}

int main() {
    Node* root = nullptr;
    char cont = 'y';

    while (cont == 'y' || cont == 'Y') {
        cout << "\n1. Create Tree";
        cout << "\n2. Display Tree";
        cout << "\n3. Search";
        cout << "\n4. Insert";
        cout << "\n5. Delete";
        cout << "\n6. Exit
";
        int choice;
        cin >> choice;

        if (choice == 1) {
            int num, value;
            cout << "Enter number of nodes: ";
            cin >> num;
            while (num-- > 0) {
                cout << "Enter value: ";
                cin >> value;
                root = addNode(root, value);
            }
        } else if (choice == 2) {
            int order, type;
            cout << "1. In-order
2. Pre-order
3. Post-order
4. Level-order
";
            cin >> order;

            if (order == 4) {
                cout << "Level Order: ";
                levelOrder(root);
            } else {
                cout << "1. Recursive
2. Iterative
";
                cin >> type;

                if (order == 1) {
                    if (type == 1) {
                        cout << "Recursive In-order: ";
                        inOrder(root);
                    } else {
                        cout << "Iterative In-order: ";
                        inOrderIter(root);
                    }
                } else if (order == 2) {
                    if (type == 1) {
                        cout << "Recursive Pre-order: ";
                        preOrder(root);
                    } else {
                        cout << "Iterative Pre-order: ";
                        preOrderIter(root);
                    }
                } else if (order == 3) {
                    if (type == 1) {
                        cout << "Recursive Post-order: ";
                        postOrder(root);
                    } else {
                        cout << "Iterative Post-order: ";
                        postOrderIter(root);
                    }
                } else {
                    cout << "Invalid choice
";
                }
            }
        } else if (choice == 3) {
            int value, method;
            cout << "Enter value to search: ";
            cin >> value;
            cout << "1. Recursive
2. Iterative
";
            cin >> method;

            if (method == 1) {
                if (searchRec(root, value)) {
                    cout << value << " found.\n";
                } else {
                    cout << value << " not found.\n";
                }
            } else {
                if (searchIter(root, value)) {
                    cout << value << " found.\n";
                } else {
                    cout << value << " not found.\n";
                }
            }
        } else if (choice == 4) {
            int value;
            cout << "Enter value to insert: ";
            cin >> value;
            root = addNode(root, value);
            cout << "Tree after insertion: ";
            inOrder(root);
            cout << endl;
        } else if (choice == 5) {
            int value;
            cout << "Enter value to delete: ";
            cin >> value;
            root = deleteNode(root, value);
            cout << "Tree after deletion: ";
            inOrder(root);
            cout << endl;
        } else if (choice == 6) {
            cont = 'n';
        } else {
            cout << "Invalid choice
";
        }
    }

    return 0;
}