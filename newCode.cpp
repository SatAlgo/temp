#include <iostream>
#include <stack>
#include <queue>
using namespace std;

struct node {
    int val;
    node* left;
    node* right;
};

node* newNode(int val) {
    node* temp = new node();
    temp->val = val;
    temp->left = temp->right = NULL;
    return temp;
}

node* insert(node* root, int val) {
    if (!root) return newNode(val);
    if (val <= root->val) root->left = insert(root->left, val);
    else root->right = insert(root->right, val);
    return root;
}

node* findMin(node* root) {
    while (root->left) root = root->left;
    return root;
}

node* remove(node* root, int val) {
    if (!root) return root;
    if (val < root->val) root->left = remove(root->left, val);
    else if (val > root->val) root->right = remove(root->right, val);
    else {
        
        if (!root->left) {
            node* temp = root->right;
            delete root;
            return temp;

        // If Node has No Right Child
        } else if (!root->right) {
            node* temp = root->left;
            delete root;
            return temp;
        }
        
        node* temp = findMin(root->right);
        root->val = temp->val;
        root->right = remove(root->right, temp->val);
    }
    return root;
}


//Left Root Right
void inOrderRecursive(node* root) {
    if (!root) return;
    inOrderRecursive(root->left);
    cout << root->val << " ";
    inOrderRecursive(root->right);
}

void inOrderNonRecursive(node* root) {
    stack<node*> s;
    node* curr = root;
    while (curr || !s.empty()) {
        while (curr) {
            s.push(curr);
            curr = curr->left;
        }
        curr = s.top();
        s.pop();
        cout << curr->val << " ";
        curr = curr->right;
    }
}

// Root, Left, Right
void preOrderRecursive(node* root) {
    if (!root) return;
    cout << root->val << " ";
    preOrderRecursive(root->left);
    preOrderRecursive(root->right);
}

// Root, Left, Right
void preOrderNonRecursive(node* root) {
    if (!root) return;
    stack<node*> s;
    s.push(root);
    while (!s.empty()) {
        node* curr = s.top();
        s.pop();
        cout << curr->val << " ";
        if (curr->right) s.push(curr->right);
        if (curr->left) s.push(curr->left);
    }
}

// Left, Right, Root
void postOrderRecursive(node* root) {
    if (!root) return;
    postOrderRecursive(root->left);
    postOrderRecursive(root->right);
    cout << root->val << " ";
}

void postOrderNonRecursive(node* root) {
    if (!root) return;
    stack<node*> s1, s2;
    s1.push(root);
    while (!s1.empty()) {
        node* curr = s1.top();
        s1.pop();
        s2.push(curr);
        if (curr->left) s1.push(curr->left);
        if (curr->right) s1.push(curr->right);
    }
    while (!s2.empty()) {
        cout << s2.top()->val << " ";
        s2.pop();
    }
}

void levelOrderTraversal(node* root) {
    if (!root) return;
    queue<node*> q;
    q.push(root);
    while (!q.empty()) {
        int levelSize = q.size();
        for (int i = 0; i < levelSize; i++) {
            node* curr = q.front();
            q.pop();
            cout << curr->val << " ";
            if (curr->left) q.push(curr->left);
            if (curr->right) q.push(curr->right);
        }
        cout << endl;
    }
}

int main() {
    node* root = NULL;
    int op, val;
    while (true) {
        cout << "\n1:Insert  2:Delete  3:In-order(Recursive)  4:In-order(Non-recursive)\n";
        cout << "5:Pre-order(Recursive)  6:Pre-order(Non-recursive)  7:Post-order(Recursive)\n";
        cout << "8:Post-order(Non-recursive)  9:Level-wise Printing  10:Exit\n";
        cout << "\nEnter your choice:";
        cin >> op;
        switch (op) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> val;
                root = insert(root, val);
                break;
            case 2:
                cout << "Enter value to delete: ";
                cin >> val;
                root = remove(root, val);
                break;
            case 3:
                cout << "In-order (Recursive): ";
                inOrderRecursive(root);
                cout << endl;
                break;
            case 4:
                cout << "In-order (Non-recursive): ";
                inOrderNonRecursive(root);
                cout << endl;
                break;
            case 5:
                cout << "Pre-order (Recursive): ";
                preOrderRecursive(root);
                cout << endl;
                break;
            case 6:
                cout << "Pre-order (Non-recursive): ";
                preOrderNonRecursive(root);
                cout << endl;
                break;
            case 7:
                cout << "Post-order (Recursive): ";
                postOrderRecursive(root);
                cout << endl;
                break;
            case 8:
                cout << "Post-order (Non-recursive): ";
                postOrderNonRecursive(root);
                cout << endl;
                break;
            case 9:
                cout << "Level-wise Printing:\n";
                levelOrderTraversal(root);
                break;
            case 10:
                return 0;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    }
    return 0;
}