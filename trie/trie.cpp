#include<iostream>
using namespace std;

class TrieNode {
public:
    char value;
    TrieNode** children;
    bool isTerminal;

    TrieNode(char val) {
        value = val;
        children = new TrieNode*[26];
        for (int i = 0; i < 26; i++) {
            children[i] = NULL;
        }
        isTerminal = false;
    }

    ~TrieNode() {
        for (int i = 0; i < 26; i++) {
            delete children[i]; // calls destructor recursively
        }
        delete[] children;
    }
};

void insertWord(TrieNode* root, const string &word, int pos = 0) {
    if (pos == word.length()) {
        root->isTerminal = true;
        return;
    }

    int index = word[pos] - 'a';
    if (root->children[index] == NULL) {
        root->children[index] = new TrieNode(word[pos]);
    }

    insertWord(root->children[index], word, pos + 1); 
}

bool searchWord(TrieNode* root, const string &word, int pos = 0) {
    if (pos == word.length()) return root->isTerminal;

    int index = word[pos] - 'a';
    if (root->children[index] == NULL) { 
        return false;
    }

    return searchWord(root->children[index], word, pos + 1);
}

int main() {
    TrieNode* Node = new TrieNode('-');

    insertWord(Node, "mann");
    insertWord(Node, "manners");
    insertWord(Node, "man");
    insertWord(Node, "random");

    cout << searchWord(Node, "mann") << endl;    // 1
    cout << searchWord(Node, "man") << endl;     // 1
    cout << searchWord(Node, "random") << endl;  // 1
    cout << searchWord(Node, "mango") << endl;   // 0

    delete Node; // to avoid memory leak
    return 0;
}
