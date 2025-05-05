#include<iostream>
#include<string>
#include<stack>
#include<queue>
using namespace std;

class node {
public:
    int data;
    node *left;
    node *right;

    node(int data) {
        this->data = data;
        this->left = NULL;
        this->right = NULL;
    }
};

node* insert(node *root, int data) {
    node *newnode = new node(data);
    if (root == NULL) {
        root = newnode;
    }
    else if (data <= root->data) {
        root->left = insert(root->left, data);
    }
    else {
        root->right = insert(root->right, data);
    }
    return root;
}

bool search(node* root, int data) {
    if (root == NULL) {
        return false;
    } else if (root->data == data) {
        return true;
    } else if (data < root->data) {
        return search(root->left, data);
    } else {
        return search(root->right, data);
    }
}

void inorder(node* root) {
    if (root == NULL) {
        return;
    }
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
} 

void preorder(node* root) {
    if (root == NULL) {
        return;
    }
    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

void postorder(node* root) {
    if (root == NULL) {
        return;
    }
    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
}


void stk_inorder(node* root){
	if(root==NULL){
		cout<<"the tree is empty.";
		return;
	}
	stack<node*>s;
	node *curr=root;
	while(curr !=NULL || s.empty()==false){
		while(curr != NULL){
			s.push(curr);
			curr=curr->left;
		}
		curr=s.top();
		s.pop();
		cout<<curr->data<<" ";
		curr=curr->right;
	}
}

void stk_preorder(node* root) {
    if (root == NULL) {
        cout << "The tree is empty." << endl;
        return;
    }

    stack<node*> s;
    s.push(root);

    while (!s.empty()) {
        node* current = s.top();
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

void stk_postorder(node* root) {
    if (root == NULL) {
        cout << "The tree is empty." << endl;
        return;
    }

    stack<node*> s1, s2;
    s1.push(root);

    while (!s1.empty()) {
        node* current = s1.top();
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
        cout << s2.top()->data << " ";
        s2.pop();
    }
}


void levelorder(node *root){
	if (root==NULL) return;
	queue <node *> Q;
	Q.push(root);
	while(!Q.empty()){
		node * current =Q.front();
		cout<<current->data<< " ";
		if(current->left != NULL) Q.push(current->left);
		if(current->right != NULL) Q.push(current->right);
		Q.pop();
	}
}

node* minvaluenode(node* root) {
    node* current = root;
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}

node* deletenode(node* root, int key) {
    if (root == NULL) {
        cout << "Tree is empty." << endl;
        return root;
    }

    if (key < root->data) {
        root->left = deletenode(root->left, key);
    } else if (key > root->data) {
        root->right = deletenode(root->right, key);
    } else {
        if (root->left == NULL && root->right == NULL) {
            delete root;
            return NULL;
        }
        else if (root->left == NULL) {
            node* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == NULL) {
            node* temp = root->left;
            delete root;
            return temp;
        }

        node* temp = minvaluenode(root->right);
        root->data = temp->data;
        root->right = deletenode(root->right, temp->data);
    }
    return root;
}




int main() {
    node *root = NULL;
    int choice, number;

    do {
        cout << "\nBinary Search Tree Menu\n";
        cout << "1. Insert Node\n";
        cout << "2. Search Node\n";
        cout << "3. Recursive Inorder Traversal\n";
        cout << "4. Recursive Preorder Traversal\n";
        cout << "5. Recursive Postorder Traversal\n";
        cout << "6. Non-recursive Inorder Traversal\n";
        cout << "7. Non-Recursive Preorder Traversal\n";
        cout << "8. Non-Recursive Postorder Traversal\n";
        cout << "9. Level wise printing\n";
        cout << "10. Deletion of node\n";
        cout << "11. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter the number to be inserted: ";
                cin >> number;
                root = insert(root, number);
                cout << "Node inserted successfully!" << endl;
                break;
           
            case 2:
                cout << "Enter the number to be searched: ";
                cin >> number;
                if (search(root, number)) {
                    cout << "Found" << endl;
                } else {
                    cout << "Not found" << endl;
                }
                break;
               
            case 3:
                cout << "Inorder Traversal: ";
                inorder(root);
                cout << endl;
                break;
               
            case 4:
                cout << "Preorder Traversal: ";
                preorder(root);
                cout << endl;
                break;
               
            case 5:
                cout << "Postorder Traversal: ";
                postorder(root);
                cout << endl;
                break;
            
            case 6:
                cout << "stk_inorder Traversal: ";
                stk_inorder(root);
                cout << endl;
                break;
                
            case 7:
                cout << "stk_inorder Traversal: ";
                stk_preorder(root);
                cout << endl;
                break;
                
            case 8:
                cout << "stk_inorder Traversal: ";
                stk_postorder(root);
                cout << endl;
                break;
                
            case 9:
                levelorder(root);
                break;
               
            case 10:
                cout << "Enter the number to be deleted: ";
                cin >> number;
                root = deletenode(root, number);
                cout << "Node deleted (if exists)!" << endl;
                break;
               
            case 11:
                cout << "Exiting program..." << endl;
                break;
               
            default:
                cout << "Invalid choice, please try again." << endl;
        }
    } while (choice != 11);

    return 0;
}