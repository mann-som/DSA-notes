#include <iostream>
#include <queue>
#include <algorithm>
#include <map>
using namespace std;

class Node
{
public:
    int val;
    Node *left;
    Node *right;

    Node(int val)
    {
        this->val = val;
        left = nullptr;
        right = nullptr;
    }
};

Node *createTree()
{ // returns root node of the tree
    cout << "Enter the val for node: " << endl;
    int data;
    cin >> data;

    if (data == -1)
    {
        return nullptr;
    }

    // create a new node
    Node *root = new Node(data);

    root->left = createTree();
    root->right = createTree();

    return root;
}

void preOrderTraversal(Node *root)
{
    if (!root)
    {
        return;
    }

    // NLR
    // N
    cout << root->val;
    // L
    preOrderTraversal(root->left);
    preOrderTraversal(root->right);
}

void levelOrderTravresal(Node *root)
{
    queue<Node *> q;
    q.push(root);
    q.push(nullptr);

    while (q.size() > 1)
    {
        Node *front = q.front();
        q.pop();
        if (!front)
        {
            cout << endl;
            q.push(nullptr);
        }
        else
        {
            cout << front->val << " ";
            if (front->left)
            {
                q.push(front->left);
            }
            if (front->right)
            {
                q.push(front->right);
            }
        }
    }
    cout << endl;
}

void printLeftView(Node *root, int level, vector<int> &leftView)
{
    if (!root)
    {
        return;
    }

    if (level == leftView.size())
    {
        leftView.push_back(root->val);
    }

    printLeftView(root->left, level + 1, leftView);
    printLeftView(root->right, level + 1, leftView);
}

void printRightView(Node *root, int level, vector<int> &rightView)
{
    if (!root)
    {
        return;
    }

    if (level == rightView.size())
    {
        rightView.push_back(root->val);
    }

    printRightView(root->right, level + 1, rightView);
    printRightView(root->left, level + 1, rightView);
}

void traversal(vector<int> &temp, Node *root)
{
    if (!root)
    {
        return;
    }

    temp.push_back(root->val);
    traversal(temp, root->left);
    traversal(temp, root->right);
}

void printTopView(Node *root)
{

    map<int, int> hdToNode;
    queue<pair<Node *, int>> q;

    q.push(make_pair(root, 0));
    while (!q.empty())
    {
        pair<Node *, int> temp = q.front();
        q.pop();

        Node *front = temp.first;
        int hd = temp.second;

        if (hdToNode.find(hd) == hdToNode.end())
        {
            hdToNode[hd] = front->val;
        }

        if (front->left)
        {
            q.push(make_pair(front->left, hd - 1));
        }
        if (front->right)
        {
            q.push(make_pair(front->right, hd + 1));
        }
    }

    cout << "Printing top view: " << endl;
    for (auto i : hdToNode)
    {
        cout << i.second << " ";
    }
    cout << endl;
}

void printBottomView(Node *root)
{

    map<int, int> hdToNode;
    queue<pair<Node *, int>> q;

    q.push(make_pair(root, 0));
    while (!q.empty())
    {
        pair<Node *, int> temp = q.front();
        q.pop();

        Node *front = temp.first;
        int hd = temp.second;

        hdToNode[hd] = front->val;

        if (front->left)
        {
            q.push(make_pair(front->left, hd - 1));
        }
        if (front->right)
        {
            q.push(make_pair(front->right, hd + 1));
        }
    }

    cout << "Printing bottom view: " << endl;
    for (auto i : hdToNode)
    {
        cout << i.second << " ";
    }
    cout << endl;
}

void printLeftBoundary(Node *root)
{
    if (!root)
    {
        return;
    }
    if (!root->left && !root->right)
    {
        return;
    }
    cout<<root->val<<" ";
    if (root->left)
    {
        printLeftBoundary(root->left);
    }
    else
    {
        printLeftBoundary(root->right);
    }
}

void printLeafNodes(Node* root){
    if(!root){
        return;
    }
    if(!root->left && !root->right){
        cout<<root->val<<" ";
    }
    printLeafNodes(root->left);
    printLeafNodes(root->right);
}

void printRightBoundary(Node* root){
    if(!root){
        return;
    }
    if(!root->left && !root->right){
        return;
    }
    if(root->right){
        printRightBoundary(root->right);
    }
    else{
        printRightBoundary(root->left);
    }
    cout<<root->val<<" ";

}

void boundaryTraversal(Node* root){
    if(!root){
        return;
    }

    cout<<root->val<<" ";
    printLeftBoundary(root->left);
    printLeafNodes(root->left);
    printLeafNodes(root->right);
    printRightBoundary(root->right);
}

int main()
{
    int k = 3;
    Node *root = createTree();
    cout << "preOrderTraversal: " << endl;
    preOrderTraversal(root);
    cout << endl
         << "level order traversal: " << endl;
    levelOrderTravresal(root);

    // cout<<endl<<"Making array of BST: "<<endl;
    // vector<int> bst;
    // traversal(bst, root);
    // for(auto a:bst){
    //     cout<<a;
    // }
    // cout<<endl;
    // sort(bst.begin(), bst.end());
    // cout<<"Kth smallest element in BST: "<<bst[k-1]<<endl;
    // cout<<"Left View";
    // vector<int> leftView;
    // printLeftView(root, 0, leftView);
    // for(auto lv:leftView){
    //     cout<<lv<<" ";
    // }
    // cout<<endl;
    // cout<<"right View";
    // vector<int> rightView;
    // printRightView(root, 0, rightView);
    // for(auto lv:rightView){
    //     cout<<lv<<" ";
    // }
    // cout<<"top View";
    // vector<int> rightView;
    cout << endl;
    printTopView(root);
    cout << endl;
    printBottomView(root);
    // for(auto lv:rightView){
    //     cout<<lv<<" ";
    // }
    cout<<endl;
    boundaryTraversal(root);
    cout << endl;
    return 0;
}