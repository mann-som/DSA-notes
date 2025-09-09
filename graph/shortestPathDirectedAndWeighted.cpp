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

};

int main() {
    Graph g;
    int V = 4; // nodes: 0,1,2,3

    g.addEdge(0, 1, 2);
    g.addEdge(0, 2, 4);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 3, 7);
    g.addEdge(2, 3, 3);

    vector<int> dist = g.shortestPathDFS(V, 0); // source = 0

    cout << "Shortest distances from node 0:\n";
    for (int i = 0; i < V; i++) {
        if (dist[i] == INT_MAX) cout << i << ": INF\n";
        else cout << i << ": " << dist[i] << "\n";
    }
}
