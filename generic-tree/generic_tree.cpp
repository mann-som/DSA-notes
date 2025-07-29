#include <iostream>
#include <queue>
using namespace std;

class Node
{
public:
    int data;
    int childCount;
    Node **children;

    Node(int data)
    {
        this->data = data;
        this->childCount = 0;
        this->children = 0;
    }

    ~Node(){
        for(int i = 0; i < childCount; i++){
            delete children[i];
        }
        delete[] children;
    }
};

Node *takeInput()
{
    int data, count;
    cout << "Enter root data : ";
    cin >> data;
    Node *root = new Node(data);
    cout << "Enter the number of children for this root : ";
    cin >> count;

    root->childCount = count;
    root->children = new Node *[count];
    for (int i = 0; i < count; i++)
    {
        root->children[i] = takeInput();
    }

    return root;
}

void levelOrderTraversal(Node* root)
{
    queue<Node *> q;
    q.push(root);
    q.push(nullptr);
    while(!q.empty()){
        Node* front = q.front();
        q.pop();
        if(!front){
            cout<<endl;
            if(!q.empty()){
                q.push(nullptr);
            }
        }
        else{
            cout<<front->data<<" ";
            for(int i = 0; i < front->childCount; i++){
                q.push(front->children[i]);
            }
        }
    }
}

int main()
{

    return 0;
}