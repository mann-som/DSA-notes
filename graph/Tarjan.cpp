#include <bits/stdc++.h>
using namespace std;

class Graph {
    int V; 
    vector<vector<int>> adj;
    vector<int> tin, low;
    vector<bool> visited;
    int timer;
public:
    Graph(int V) {
        this->V = V;
        adj.resize(V);
        tin.assign(V, -1);
        low.assign(V, -1);
        visited.assign(V, false);
        timer = 0;
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dfs(int v, int p = -1) {
        visited[v] = true;
        tin[v] = low[v] = timer++;
        for (int to : adj[v]) {
            if (to == p) continue; 
            if (visited[to]) {
                low[v] = min(low[v], tin[to]);
            } else {
                dfs(to, v);
                low[v] = min(low[v], low[to]);
                if (low[to] > tin[v]) {
                    cout << "Bridge found: " << v << " - " << to << "\n";
                }
            }
        }
    }

    void findBridges() {
        for (int i = 0; i < V; i++) {
            if (!visited[i])
                dfs(i);
        }
    }
};

int main() {
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(1, 3);
    g.addEdge(3, 4);

    g.findBridges();
    return 0;
}
