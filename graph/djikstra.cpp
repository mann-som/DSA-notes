#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>
#include <stack>
#include <climits>
#include <set>
using namespace std;

class Graph
{
public:
    unordered_map<int, list<pair<int, int>>> adjMap;

    void addEdge(int u, int v, int w)
    {
        adjMap[u].push_back({v, w});
    }

    void createTopoStack(int node, stack<int> &topo, vector<int> &visited)
    {
        visited[node] = 1;
        for (auto nbr : adjMap[node])
        {
            if (!visited[nbr.first])
                createTopoStack(nbr.first, topo, visited);
        }
        topo.push(node);
    }

    vector<int> shortestPathDFS(int V, int src)
    {
        
        stack<int> topo;
        vector<int> visited(V, 0);
        for (int i = 0; i < V; i++)
        {
            if (!visited[i])
                createTopoStack(i, topo, visited);
        }

        vector<int> dist(V, INT_MAX);
        dist[src] = 0;

        while (!topo.empty())
        {
            int u = topo.top();
            topo.pop();

            if (dist[u] != INT_MAX)
            {
                for (auto nbr : adjMap[u])
                {
                    int v = nbr.first;
                    int w = nbr.second;
                    if (dist[u] + w < dist[v])
                    {
                        dist[v] = dist[u] + w;
                    }
                }
            }
        }
        return dist;
    }

    void djikstraShortestPath(int V, int src, int dest){
        vector<int> dist(V, INT_MAX);
        set<pair<int, int>> st;  // {distance, node}

        dist[src] = 0;
        st.insert({0, src});

        while(!st.empty()){
            auto currNodeAdd = st.begin();
            auto currNode = *currNodeAdd;
            int currNodeDist = currNode.first;
            int currNodeNode = currNode.second;

            st.erase(currNodeAdd);

            for(auto nbr : adjMap[currNodeNode]){
                int nbrNode = nbr.first;
                int nbrDist = nbr.second;

                if(currNodeDist + nbrDist < dist[nbrNode]){
                    auto prevEntry = st.find({dist[nbrNode], nbrNode});
                    if(prevEntry != st.end()) st.erase(prevEntry);

                    dist[nbrNode] = currNodeDist + nbrDist;
                    st.insert({dist[nbrNode], nbrNode});
                }
            }
        }

        cout << "Distance to " << dest << " is " << dist[dest] << endl;
    }

};

int main() {
    Graph g;
    g.addEdge(0, 1, 2);
    g.addEdge(0, 2, 4);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 3, 7);
    g.addEdge(2, 4, 3);
    g.addEdge(3, 4, 1);

    g.djikstraShortestPath(5, 0, 4); // should output Distance to 4 is 6
}

