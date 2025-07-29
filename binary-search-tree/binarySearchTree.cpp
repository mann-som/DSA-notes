#include <iostream>
#include <queue>
using namespace std;

class Node{

    public:
        int data;
        Node* left;
        Node* right;
    
    Node(int value){
        this->left = nullptr;
        this->data = value;
        this->right = nullptr;
    }
};


void levelOrderTraversal(Node* root){
    queue<Node*> q;
    q.push(root);
    q.push(NULL);
    while(!q.empty()){
        Node* temp = q.front();
        q.pop();
        if(!temp){
            cout<<endl;
            if(!q.empty()){
                q.push(nullptr);
            }
        }
        else{
            cout<<temp->data<<" ";
            if(temp->left){
                q.push(temp->left);
            }
            if(temp->right){
                q.push(temp->right);
            }
        }
    }

    cout<<endl;

}

void preOrder(Node* root){
    // NLR
    if(!root){
        return;
    }

    cout<<root->data<<" ";
    preOrder(root->left);
    preOrder(root->right);
}

void inOrder(Node* root){
    // LNR
    if(!root){
        return;
    }

    inOrder(root->left);
    cout<<root->data<<" ";
    inOrder(root->right);
}

void postOrder(Node* root){
    // LRN
    if(!root) return;
    
    postOrder(root->left);
    postOrder(root->right);
    cout<<root->data<<" ";
}

Node* minVal(Node* root){
    if(!root) return nullptr;

    while(root->left){
        root = root->left;
    }

    return root;
}

Node* maxVal(Node* root){
    if(!root) return nullptr;
    
    while(root->right){
        root = root->right;
    }

    return root;
}

Node* deleteNode(Node* &root, int target){
    if(!root){
        return nullptr;
    }
    
    if(root->data == target){
        
        if(!root->left && !root->right){
            delete root;
            return nullptr;
        }
        else if(!root->left && root->right){
            Node* rightSubTree = root->right;
            delete root;
            return rightSubTree;
        }
        else if(root->left && !root->right){
            Node* leftSubTree =root->left;
            delete root;
            return leftSubTree;
        }
        else{
            // left subtree max
            Node* maxi = maxVal(root->left);
            root->data = maxi->data;
            root->left = deleteNode(root->left, maxi->data);
            return root;
        }

        return root; 
    }
    else if(root->data > target){
        root->left =  deleteNode(root->left, target);
    }
    else{
        root->right =  deleteNode(root->right, target);
    }

    return root;
}

// convert binary search tree to a doubly linked list
void convertBSTtoDLL(Node* root, Node* &head){
    if(!root) return;
    
    // reverse inorder : RNL
    convertBSTtoDLL(root->right, head);
    root->right = head;
    if(head){
        head->left = root;
    }
    head = root;

    convertBSTtoDLL(root->left, head);
}

// convert sorted DLL to BST
// void convertDLLtoBST

Node* BSTFromInOrder(int inOrder[], int s, int e){
    // base case
    if(s > e){
        return nullptr;
    }

    int mid = (e-s)/2 + s;
    Node* root = new Node(inOrder[mid]);
    root->left = BSTFromInOrder(inOrder, s, mid-1);
    root->right = BSTFromInOrder(inOrder, mid+1, e);

    return root;
}

Node* insertIntoBST(Node* root, int data){
    if(!root){
        root = new Node(data);
        return root;
    }

    if(data > root->data){
        root->right = insertIntoBST(root->right, data);
    }
    else{
        root->left = insertIntoBST(root->left, data);
    }

    return root;
}

Node* createBST(Node* &root){
    // cout<<"Enter data: ";
    // int data;
    // cin>>data;
    // cout<<endl;

    vector<int> data = {50, 30, 20, 25, 40, 60, 70, 80, 55, -1};
    int i = 0;
    while(data[i] != -1){
        root = insertIntoBST(root, data[i]);
        i++;
    }

    return root;
}

int main(){

    // Node* root = nullptr;
    // createBST(root);

    // levelOrderTraversal(root);

    // cout<<"Inorder: ";
    // inOrder(root);
    // cout<<endl;

    // cout<<"preOrder: ";
    // preOrder(root);
    // cout<<endl;

    // cout<<"Postorder: ";
    // postOrder(root);
    // cout<<endl;

    // Node* min = minVal(root);
    // Node* max = maxVal(root);

    // cout<<"Minimum value in tree: "<<min->data<<" Maximum value in tree: "<<max->data;
    // cout<<endl;

    // int target;
    // cout<<"Enter the value to be deleted :";
    // cin>>target;
    // cout<<endl;

    // while(target != -1){
    //     root = deleteNode(root, target);
    //     cout<<"Tree after deletion: "<<endl;
    //     levelOrderTraversal(root);
    //     cout<<"Enter the value to be deleted :";
    //     cin>>target;
    //     cout<<endl;
    // }

    int inOrderArr[] = {-10,-3,0,5,9};
    Node* root = BSTFromInOrder(inOrderArr, 0, 5);
    levelOrderTraversal(root);
    return 0;
}