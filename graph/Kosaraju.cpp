#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class Graph {
public:
    int n;
    vector<vector<int>> adjList;

    Graph(int n) {
        this->n = n;
        adjList.resize(n);
    }

    void addEdge(int u, int v) {
        adjList[u].push_back(v);
    }

    void createTopoStack(int node, stack<int> &topo, vector<int> &visited) {
        visited[node] = 1;
        for (auto nbr : adjList[node]) {
            if (!visited[nbr])
                createTopoStack(nbr, topo, visited);
        }
        topo.push(node);
    }

    void reverseTheGraph(vector<vector<int>> &reverseGraph) {
        reverseGraph.assign(n, {});
        for (int u = 0; u < n; u++) {
            for (int v : adjList[u]) {
                reverseGraph[v].push_back(u);
            }
        }
    }

    void dfs(int src, vector<vector<int>> &graph, vector<bool> &visited) {
        visited[src] = true;
        for (int child : graph[src]) {
            if (!visited[child]) dfs(child, graph, visited);
        }
    }
    
    int stronglyConnectedComponents() {
        int numOfSCC = 0;
        stack<int> order;
        vector<int> vis(n, 0);

        for (int i = 0; i < n; i++) {
            if (!vis[i]) createTopoStack(i, order, vis);
        }

        vector<vector<int>> reverseGraph;
        reverseTheGraph(reverseGraph);

        vector<bool> visited(n, false);
        while (!order.empty()) {
            int src = order.top(); order.pop();
            if (!visited[src]) {
                dfs(src, reverseGraph, visited);
                numOfSCC++;
            }
        }

        return numOfSCC;
    }
};

int main() {
    Graph g(5);
    g.addEdge(0, 2);
    g.addEdge(2, 1);
    g.addEdge(1, 0);
    g.addEdge(0, 3);
    g.addEdge(3, 4);

    cout << "SCC count: " << g.stronglyConnectedComponents() << endl;
    return 0;
}
