#include <iostream>
#include <vector>
#include <queue>
#include <stack>

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

// DFS: Iterative Approach using a stack
void dfsi(int start, const vector<vector<pair<int, int>>>& adj) {
    int V = adj.size();
    vector<bool> visited(adj.size(), false);
    stack<int> st;

    st.push(start);

    while (!st.empty()) {
        int curr = st.top();
        st.pop(); //remove the current top of stack

        if (!visited[curr]) {
            cout << curr << ", ";
            visited[curr] = true;
        }

        // we'll be iterating through the adjacent vertices in reverse (rbegin)
        // prefix ++ is faster
        for (auto it = adj[curr].rbegin(); it != adj[curr].rend(); ++it) {
            auto& [neighbor, wt] = *it;

            if (!visited[neighbor]) {
                st.push(neighbor);
            }
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
    int V = 5;
    vector<vector<pair<int, int>>> adj(V);
    
    // ample unweighted graph (weight = 1)
    adj[0].push_back({1, 1}); adj[0].push_back({2, 1});
    adj[1].push_back({3, 1}); adj[1].push_back({4, 1});
    adj[2].push_back({0, 1}); adj[2].push_back({4, 1});
    adj[3].push_back({1, 1});
    adj[4].push_back({1, 1}); adj[4].push_back({2, 1});

    vector<bool> visited(V, false);
    cout << "DFS Order: ";  dfs(0, adj, visited);     cout << "\n";
    cout << "DFS Order (Iterative): ";  dfsi(0, adj); cout << "\n";
    cout << "BFS Order: ";  bfs(0, adj);              cout << "\n";
    // for the test cases, I might continue having multiple lines together, it's so much neater
    return 0;
}
