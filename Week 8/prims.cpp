#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int primMST(int start, int V, const vector<vector<pair<int, int>>>& adj) {
    vector<bool> visited(V, false);
    
    // Min-Heap Priority Queue tracking elements as: {edge_weight, target_node}
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    
    int total_mst_weight = 0;
    pq.push({0, start}); // Start with a seed cost of 0

    while (!pq.empty()) {
        // Extract the absolute cheapest edge currently visible to our visited cluster
        auto [wt, curr] = pq.top(); 
        pq.pop();

        if (visited[curr]) continue; 
        visited[curr] = true;
        total_mst_weight += wt;

        for (auto& [neighbor, edge_wt] : adj[curr]) {
            if (!visited[neighbor]) {
                pq.push({edge_wt, neighbor}); // Push edge cost onto min-heap
            }
        }
    }
    return total_mst_weight;
}

int main() {
    int V = 4;
    vector<vector<pair<int, int>>> adj(V);
    // Standard triangle graph with a central chord
    adj[0].push_back({1, 1}); adj[1].push_back({0, 1});
    adj[1].push_back({2, 3}); adj[2].push_back({1, 3});
    adj[0].push_back({2, 5}); adj[2].push_back({0, 5});
    adj[2].push_back({3, 2}); adj[3].push_back({2, 2});

    cout << "Total Prim's MST Weight: " << primMST(0, V, adj) << "\n";
    return 0;
}
