#include <iostream>
#include <climits>
#include <queue>
using namespace std;

class heap{

    public:
        int cap, size;
        int *arr;

        heap(int _cap){
            this->cap = _cap;
            this->size = 0;
            arr = new int[cap+1];
        }

        void insert(int val){
            if(size == cap){
                cout<<"Overflow";
                return;
            }
            int index = ++size;
            arr[index] = val;

            while(index > 1){
                int parentInd = index/2;
                if(arr[index] > arr[parentInd]){
                    swap(arr[index], arr[parentInd]);
                    index = parentInd;
                }
                else{
                    break;
                }
            }
        }

        int deletion(){
            int ans = arr[1];
            arr[1] = arr[size];
            size--;

            int index = 1;
            while(index < size){
                int leftChildInd = 2*index;
                int rightChildInd = 2*index + 1;

                int largestEleInd = index;
                if(leftChildInd < size && arr[largestEleInd] < arr[leftChildInd]){
                    largestEleInd = leftChildInd;
                }
                if(rightChildInd < size && arr[largestEleInd] < arr[rightChildInd]){
                    largestEleInd = rightChildInd;
                }

                if(index == largestEleInd){
                    break;
                }
                else{
                    swap(arr[index], arr[largestEleInd]);
                    index = largestEleInd;
                }
            }

            return ans;
        }

        void printHeap(){
            cout<<"Printing the heap: "<<endl;
            for(int i = 1; i <= size; i++){
                cout<<arr[i]<<" ";
            }
            cout<<endl;
        }

};


// MAIN HEAPIFY FUNCTION
void heapify(int* arr, int n, int index){
    int leftChildInd = index*2;
    int rightChilddInd = index*2 + 1;
    int largestInd = index;

    if(leftChildInd <= n && arr[leftChildInd] > arr[largestInd]){
        largestInd = leftChildInd;
    }
    if(rightChilddInd <= n && arr[rightChilddInd] > arr[largestInd]){
        largestInd = rightChilddInd;
    }

    if(largestInd != index){
        swap(arr[largestInd], arr[index]);
        index = largestInd;
        heapify(arr, n, index);
    }
}

void buildHeap(int arr[], int n){
    for(int i = n/2; i > 0; i--){
        heapify(arr, n, i);
    }
}

void heapSort(int arr[], int n){
    while(n != 1){
        swap(arr[1], arr[n]);
        n--;
        heapify(arr, n, 1);
    }
}

class Info{
    public:
        int maxVal;
        bool isValid;
    
        Info(int val, int isValid): maxVal(val), isValid(isValid){};
};

class Node{
    public:
    int val;
    Node* left;
    Node* right;

    Node(int val): val(val), left(nullptr), right(nullptr){};
};

bool isCBT(Node* root){
    if(!root) return true;

    queue<Node*> q;
    q.push(root);
    bool nullChildSeen = false;

    while(!q.empty()){
        Node* curr = q.front();
        q.pop();

        if(curr->left){
            if(nullChildSeen) return false;
            q.push(curr->left);
        }
        else{
            nullChildSeen = true;
        }

        if(curr->right){
            if(nullChildSeen) return false;
            q.push(curr->right);
        }
        else{
            nullChildSeen = true;
        }
    }

    return true;
}

void BSTtoMaxHeap(Node* root){
     
}

Info checkMaxHeap(Node* root){
    if(!root){
        return Info(INT_MIN, true);
    }    
    if(!root->left && !root->right){
        return Info(root->val, true);
    }
    Info leftAns = checkMaxHeap(root->left);
    Info rightAns = checkMaxHeap(root->right);

    if(root->val > leftAns.maxVal && root->val > rightAns.maxVal  && leftAns.isValid && rightAns.isValid){
        Info ans(root->val, true);
        return ans;
    }
    else{
        int maxVal = max(root->val, max(leftAns.maxVal, rightAns.maxVal));
        Info ans(maxVal, false);
        return ans;
    }
}

bool checkMaxHeapV2(Node* root){
    if(!root){
        return true;
    }    
    
    bool leftAns = checkMaxHeapV2(root->left);
    bool rightAns = checkMaxHeapV2(root->right);

    if((!root->left || root->val > root->left->val) &&
       (!root->right || root->val > root->right->val) &&
       leftAns && rightAns)
    {
        return true;
    }
    return false;
}



int main(){

    // heap h(20);
    // h.insert(10);
    // h.insert(20);
    // h.insert(30);
    // h.insert(40);
    // h.insert(50);
    // h.printHeap();
    // int deleted = h.deletion();
    // cout<<"Deleted node: "<<deleted<<endl;
    // h.printHeap();

    int arr[] = {-1, 5, 10, 15, 20, 25, 12};
    int n = 6;
    buildHeap(arr, n);
    for(int i = 1; i <= n; i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
    heapSort(arr, n);
    for(int i = 1; i <= n; i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
    return 0;
}