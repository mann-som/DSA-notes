#include<iostream>
#include <unordered_map>
#include <list>
#include <queue>
#include <algorithm>
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

        vector<int> shortestPath(int src, int dest){
            queue<int> q;
            unordered_map<int, int> parents;
            unordered_map<int, bool> vis;

            q.push(src);
            vis[src] = 1;
            parents[src] = -1;

            while(!q.empty()){
                int frontNode = q.front(); q.pop();

                for(auto nbr : adjList[frontNode]){
                    if(!vis[nbr]){
                        q.push(nbr);
                        parents[nbr] = src;
                        vis[nbr] = 1;
                    }
                }
            }

            vector<int> ans;
            while(dest != -1){
                ans.push_back(dest);
                dest = parents[dest];
            }

            reverse(ans.begin(), ans.end());
            return ans;
        }
};


int main(){
    return 0;
}
