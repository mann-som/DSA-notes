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
    int n;
    unordered_map<int, list<pair<int, int>>> adjMap;

    Graph(int n){
        this->n = n;
    }

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

    // vector<pair<int, int>> adjListtoEdgeList(){
    //     vector<pair<int, int>> edgeList;

    // }

    vector<int> bellmanFord(int src){
        vector<int> dist(n, INT_MAX);
        dist[src] = 0;
        for(int i = 1; i < n; i++){
            bool updateStatus = false;
            for(auto adj:adjMap){
                int u = adj.first;
                for(auto edge:adj.second){
                    auto [v, w] = edge;
                    if(dist[u] != INT_MAX && dist[u] + w < dist[v]){
                        dist[v] = dist[u] + w;
                        updateStatus = true;
                    }
                }

            }

            if(!updateStatus) return dist;
        }

        bool updateStatus = false;
        for(auto adj:adjMap){
            int u = adj.first;
            for(auto edge:adj.second){
                auto [v, w] = edge;
                if(dist[u] != INT_MAX && dist[u] + w < dist[v]){
                    dist[v] = dist[u] + w;
                    updateStatus = true;
                }
            }
        }
        if(updateStatus) return {};
    }

};

int main() {
    // ---- Case 1: No negative cycle ----
    Graph g1(5);
    g1.addEdge(0, 1, 6);
    g1.addEdge(0, 2, 7);
    g1.addEdge(1, 2, 8);
    g1.addEdge(1, 3, 5);
    g1.addEdge(1, 4, -4);
    g1.addEdge(2, 3, -3);
    g1.addEdge(2, 4, 9);
    g1.addEdge(3, 1, -2);
    g1.addEdge(4, 0, 2);
    g1.addEdge(4, 3, 7);

    auto dist1 = g1.bellmanFord(0);
    if(dist1.empty()) {
        cout << "Negative cycle detected in g1\n";
    } else {
        cout << "Shortest distances from source (g1):\n";
        for(int i=0;i<dist1.size();i++){
            cout << "Node " << i << " -> " << (dist1[i]==INT_MAX ? -1 : dist1[i]) << "\n";
        }
    }

    // ---- Case 2: Graph with a negative cycle ----
    Graph g2(3);
    g2.addEdge(0, 1, 1);
    g2.addEdge(1, 2, -1);
    g2.addEdge(2, 0, -1); // Negative cycle: 0 -> 1 -> 2 -> 0

    auto dist2 = g2.bellmanFord(0);
    if(dist2.empty()) {
        cout << "Negative cycle detected in g2\n";
    } else {
        cout << "Shortest distances from source (g2):\n";
        for(int i=0;i<dist2.size();i++){
            cout << "Node " << i << " -> " << (dist2[i]==INT_MAX ? -1 : dist2[i]) << "\n";
        }
    }
}


