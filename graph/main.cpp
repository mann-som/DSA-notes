#include<iostream>
#include <unordered_map>
#include <list>
using namespace std;

class Graph{
    public:
        unordered_map<int, list<int>> adjList;
        void addEdge(int u, int v, bool directed){
            adjList[u].push_back(v);
            if(!directed) adjList[v].push_back(u);
        }
};


int main(){
    return 0;
}