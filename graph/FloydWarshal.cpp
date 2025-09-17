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

    vector<vector<int>> floydWarshal(){
        vector<vector<int>> dist(n, vector<int>(n, 1e9));
        for(int i = 0; i < n; i++){
            dist[i][i] = 0;
        }

        for(auto& [u, edges]:adjMap){
            for(auto& [v, w]:edges){
                dist[u][v] = w;
            }
        }

        for(int helper = 0; helper < n; helper++){
            for(int src = 0; src < n; src++){
                for(int dest = 0; dest < n; dest++){
                    if(dist[src][helper] < 1e9 && dist[helper][dest] < 1e9)
                        dist[src][dest] = min(dist[src][dest], dist[src][helper] + dist[helper][dest]);
                }
            }
        }

        for(int i = 0; i < n; i++){
            if(dist[i][i] < 0) return {{}};
        }

        return dist;
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

    // auto dist1 = g1.bellmanFord(0);
    // if(dist1.empty()) {
    //     cout << "Negative cycle detected in g1\n";
    // } else {
    //     cout << "Shortest distances from source (g1):\n";
    //     for(int i=0;i<dist1.size();i++){
    //         cout << "Node " << i << " -> " << (dist1[i]==INT_MAX ? -1 : dist1[i]) << "\n";
    //     }
    // }

    // // ---- Case 2: Graph with a negative cycle ----
    // Graph g2(3);
    // g2.addEdge(0, 1, 1);
    // g2.addEdge(1, 2, -1);
    // g2.addEdge(2, 0, -1); // Negative cycle: 0 -> 1 -> 2 -> 0

    // auto dist2 = g2.bellmanFord(0);
    // if(dist2.empty()) {
    //     cout << "Negative cycle detected in g2\n";
    // } else {
    //     cout << "Shortest distances from source (g2):\n";
    //     for(int i=0;i<dist2.size();i++){
    //         cout << "Node " << i << " -> " << (dist2[i]==INT_MAX ? -1 : dist2[i]) << "\n";
    //     }
    // }
}


