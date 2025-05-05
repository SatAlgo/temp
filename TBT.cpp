#include <iostream>
using namespace std;

class TBTree {
public:
    int data;
    TBTree *left, *right;
    bool lthread, rthread;
    TBTree(int val) {
        data = val;
        left = right = NULL;
        lthread = rthread = true;
    }
};

class ThreadedBinaryTree {
private:
    TBTree *root;
public:
    ThreadedBinaryTree() { root = NULL; }
    TBTree *insert(TBTree *node, int key);
    void insert(int key) { root = insert(root, key); }
    void inorder_recursive(TBTree *node);
    void preorder_recursive(TBTree *node);
    void postorder_recursive(TBTree *node);
    TBTree *leftMost(TBTree *node);
    void inorder_nonrecursive();
    void preorder_nonrecursive();
    TBTree *search(int key);
    TBTree *deleteNode(TBTree *node, int key);
    void deleteKey(int key) { root = deleteNode(root, key); }
    void menu();
};

TBTree *ThreadedBinaryTree::insert(TBTree *node, int key) {
    TBTree *ptr = node, *par = NULL;
    while (ptr != NULL) {
        if (key == ptr->data) {
            cout << "Duplicate key!\n";
            return node;
        }
        par = ptr;
        if (key < ptr->data) {
            if (!ptr->lthread)
                ptr = ptr->left;
            else
                break;
        } else {
            if (!ptr->rthread)
                ptr = ptr->right;
            else
                break;
        }
    }
    TBTree *temp = new TBTree(key);
    if (par == NULL) {
        node = temp;
    } else if (key < par->data) {
        temp->left = par->left;
        temp->right = par;
        par->lthread = false;
        par->left = temp;
    } else {
        temp->right = par->right;
        temp->left = par;
        par->rthread = false;
        par->right = temp;
    }
    return node;
}

void ThreadedBinaryTree::inorder_recursive(TBTree *node) {
    if (node == NULL)
        return;
    if (!node->lthread)
        inorder_recursive(node->left);
    cout << node->data << " ";
    if (!node->rthread)
        inorder_recursive(node->right);
}

void ThreadedBinaryTree::preorder_recursive(TBTree *node) {
    if (node == NULL)
        return;
    cout << node->data << " ";
    if (!node->lthread)
        preorder_recursive(node->left);
    if (!node->rthread)
        preorder_recursive(node->right);
}

void ThreadedBinaryTree::postorder_recursive(TBTree *node) {
    if (node == NULL)
        return;
    if (!node->lthread)
        postorder_recursive(node->left);
    if (!node->rthread)
        postorder_recursive(node->right);
    cout << node->data << " ";
}

TBTree *ThreadedBinaryTree::leftMost(TBTree *node) {
    while (node != NULL && !node->lthread)
        node = node->left;
    return node;
}

void ThreadedBinaryTree::inorder_nonrecursive() {
    TBTree *curr = leftMost(root);
    while (curr != NULL) {
        cout << curr->data << " ";
        if (curr->rthread)
            curr = curr->right;
        else {
            curr = curr->right;
            curr = leftMost(curr);
        }
    }
}

void ThreadedBinaryTree::preorder_nonrecursive() {
    TBTree *curr = root;
    while (curr != NULL) {
        cout << curr->data << " ";
        if (!curr->lthread)
            curr = curr->left;
        else {
            while (curr->rthread && curr->right != NULL)
                curr = curr->right;
            curr = curr->right;
        }
    }
}

TBTree *ThreadedBinaryTree::search(int key) {
    TBTree *ptr = root;
    while (ptr != NULL) {
        if (key == ptr->data)
            return ptr;
        else if (key < ptr->data) {
            if (!ptr->lthread)
                ptr = ptr->left;
            else
                break;
        } else {
            if (!ptr->rthread)
                ptr = ptr->right;
            else
                break;
        }
    }
    return NULL;
}

TBTree* ThreadedBinaryTree::deleteNode(TBTree* root, int key) {
    TBTree* parent = NULL;
    TBTree* curr = root;
    while (curr != NULL) {
        if (key == curr->data)
            break;
        parent = curr;
        if (key < curr->data) {
            if (!curr->lthread)
                curr = curr->left;
            else
                return root;
        } else {
            if (!curr->rthread)
                curr = curr->right;
            else
                return root;
        }
    }
    if (curr == NULL) {
        cout << "Node not found.\n";
        return root;
    }
    if (curr->lthread && curr->rthread) {
        if (parent == NULL)
            return NULL;
        if (parent->left == curr) {
            parent->lthread = true;
            parent->left = curr->left;
        } else {
            parent->rthread = true;
            parent->right = curr->right;
        }
        delete curr;
    }
    else if (!curr->lthread || !curr->rthread) {
        TBTree* child = (!curr->lthread) ? curr->left : curr->right;
        if (parent == NULL)
            return child;
        if (parent->left == curr)
            parent->left = child;
        else
            parent->right = child;
        TBTree* pred = leftMost(child);
        pred->left = curr->left;
        delete curr;
    }
    else {
        TBTree* successor = leftMost(curr->right);
        int val = successor->data;
        root = deleteNode(root, successor->data);
        curr->data = val;
    }
    return root;
}

void ThreadedBinaryTree::menu() {
    int choice, val;
    do {
        cout << "\n--- Menu ---\n";
        cout << "1. Insert Node\n";
        cout << "2. Recursive Inorder\n";
        cout << "3. Recursive Preorder\n";
        cout << "4. Recursive Postorder\n";
        cout << "5. Non-Recursive Inorder\n";
        cout << "6. Non-Recursive Preorder\n";
        cout << "7. Search Node\n";
        cout << "8. Delete Node\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> val;
                insert(val);
                break;
            case 2:
                inorder_recursive(root);
                cout << endl;
                break;
            case 3:
                preorder_recursive(root);
                cout << endl;
                break;
            case 4:
                postorder_recursive(root);
                cout << endl;
                break;
            case 5:
                inorder_nonrecursive();
                cout << endl;
                break;
            case 6:
                preorder_nonrecursive();
                cout << endl;
                break;
            case 7:
                cout << "Enter value to search: ";
                cin >> val;
                cout << (search(val) ? "Node found!\n" : "Node not found.\n");
                break;
            case 8:
                cout << "Enter value to delete: ";
                cin >> val;
                deleteKey(val);
                break;
            case 9:
                return;
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 9);
}

int main() {
    ThreadedBinaryTree tbt;
    tbt.menu();
    return 0;
}