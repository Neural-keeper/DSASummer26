#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// DFS: Deep exploration via Call Stack (Recursion)
void dfs(int node, const vector<vector<pair<int, int>>>& adj, vector<bool>& visited) {
    cout << node << " ";
    visited[node] = true;

    // Structured binding syntax: breaks the pair down cleanly into neighbor and weight
    for (auto& [neighbor, wt] : adj[node]) {
        if (!visited[neighbor]) {
            dfs(neighbor, adj, visited);
        }
    }
}

// BFS: Layer-by-layer exploration via an iterative Queue
void bfs(int start, const vector<vector<pair<int, int>>>& adj) {
    vector<bool> visited(adj.size(), false);
    queue<int> q;

    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        cout << curr << " ";

        for (auto& [neighbor, wt] : adj[curr]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
}

int main() {
    int V = 4;
    vector<vector<pair<int, int>>> adj(V);
    
    // Build a sample unweighted path for tracking (weight = 1)
    adj[0].push_back({1, 1}); adj[1].push_back({2, 1}); adj[2].push_back({3, 1});

    vector<bool> visited(V, false);
    cout << "DFS Order: ";  dfs(0, adj, visited); cout << "\n";
    cout << "BFS Order: ";  bfs(0, adj);          cout << "\n";
    return 0;
}
