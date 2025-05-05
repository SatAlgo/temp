#include <iostream>
#include <stack>
#include <queue>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
};

Node* GetNewNode(int data) {
    Node* newNode = new Node();
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

Node* Insert(Node* root, int data) {
    if (root == NULL) {
        root = GetNewNode(data);
    } else if (data < root->data) {
        root->left = Insert(root->left, data);
    } else {
        root->right = Insert(root->right, data);
    }
    return root;
}

Node* DeleteNode(Node* root, int data) {
    if (root == NULL) return root;
    
    if (data < root->data) {
        root->left = DeleteNode(root->left, data);
    } else if (data > root->data) {
        root->right = DeleteNode(root->right, data);
    } else {
        if (root->left == NULL) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        
        Node* temp = root->right;
        while (temp && temp->left != NULL) {
            temp = temp->left;
        }
        root->data = temp->data;
        root->right = DeleteNode(root->right, temp->data);
    }
    return root;
}

void InorderTraversal(Node* root) {
    if (root != NULL) {
        InorderTraversal(root->left);
        cout << root->data << " ";
        InorderTraversal(root->right);
    }
}

void PreorderTraversal(Node* root) {
    if (root != NULL) {
        cout << root->data << " ";
        PreorderTraversal(root->left);
        PreorderTraversal(root->right);
    }
}

void PostorderTraversal(Node* root) {
    if (root != NULL) {
        PostorderTraversal(root->left);
        PostorderTraversal(root->right);
        cout << root->data << " ";
    }
}

void LevelOrderTraversal(Node* root) {
    if (root == NULL) return;
    
    queue<Node*> q;
    q.push(root);
    
    while (!q.empty()) {
        Node* temp = q.front();
        q.pop();
        cout << temp->data << " ";
        
        if (temp->left) q.push(temp->left);
        if (temp->right) q.push(temp->right);
    }
}

int main() {
    int n, data;
    Node* root = NULL;
    
    cout << "Enter the number of nodes you want to insert: " << endl;
    cin >> n;
    
    cout << "Enter root data: " << endl;
    cin >> data;
    root = GetNewNode(data);
    
    cout << "Enter other nodes:" << endl;
    for (int i = 0; i < n - 1; i++) {
        cout << "Enter node data: ";
        cin >> data;
        root = Insert(root, data);
    }
    
    cout << "Inorder Traversal: ";
    InorderTraversal(root);
    cout << endl;
    
    cout << "Preorder Traversal: ";
    PreorderTraversal(root);
    cout << endl;
    
    cout << "Postorder Traversal: ";
    PostorderTraversal(root);
    cout << endl;
    
    cout << "Level Order Traversal: ";
    LevelOrderTraversal(root);
    cout << endl;
    
    int deleteData;
    cout << "Enter node to delete: ";
    cin >> deleteData;
    root = DeleteNode(root, deleteData);
    
    cout << "After Deletion (Inorder Traversal): ";
    InorderTraversal(root);
    cout << endl;
    
    cout << "Enter new node to insert after deletion: ";
    cin >> data;
    root = Insert(root, data);
    
    cout << "After Insertion (Inorder Traversal): ";
    InorderTraversal(root);
    cout << endl;
    
    return 0;
}
