#include <iostream>
#include <unordered_map>
#include <list>
#include <vector>
#include <queue>
using namespace std;

class Solution {
  public:
    unordered_map<int, list<int>> createAdjlist(vector<vector<int>>& edges){
        unordered_map<int, list<int>> adjList;
        for(int i = 0; i < edges.size(); i++){
            adjList[edges[i][0]].push_back(edges[i][1]);
            adjList[edges[i][1]].push_back(edges[i][0]);
        }
        return adjList;
    }
    
    bool isCycleHelper(int src, unordered_map<int, list<int>>& adjList, unordered_map<int, bool> &visited){
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
                else if(parent[currNode] != child){  
                    return true;
                }
            }
        }
        return false;
    }
    
    bool isCycle(int V, vector<vector<int>>& edges) {
        unordered_map<int, list<int>> adjList = createAdjlist(edges);
        unordered_map<int, bool> visited;   
        
        for(int i = 0; i < V; i++){
            if(!visited[i]){
                if(isCycleHelper(i, adjList, visited)) 
                    return true;
            }
        }
        return false;   
    }
};
