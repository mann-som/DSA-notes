#include<iostream>
#include <unordered_map>
#include <list>
#include <queue>
using namespace std;

class Graph{
    public:
        unordered_map<int, list<int>> adjList;
        void addEdge(int u, int v, bool directed){
            adjList[u].push_back(v);
            if(!directed) adjList[v].push_back(u);
        }
        bool detectCycle(int src){
            unordered_map<int, bool> visited ;   
            unordered_map<int, int> parent;
            queue<int> q;

            q.push(src);
            visited[src] = 1;
            parent[src] = -1;
            while(!q.empty()){
                int currNode = q.front(); q.pop();
                
                for(auto child : adjList[currNode]){
                    if(!visited[child]){
                        q.push(child);
                        visited[child] = 1;
                        parent[child] = currNode;
                    }
                    else if(visited[currNode] && parent[currNode] != child){
                        return true;
                    }
                }
            }
            
        return false;
        }
};


int main(){
    return 0;
}
