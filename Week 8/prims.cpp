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
    int numNodes = 6;
    vector<vector<pair<int, int>>> adj(numNodes); // adjacency list rep

    // A=0, B=1, C=2, D=3, E=4, F=5
    adj[0] = {{1, 4}, {2, 2}};
    adj[1] = {{0, 4}, {2, 5}, {3, 10}, {5, 12}};
    adj[2] = {{0, 2}, {1, 5}, {3, 3}, {4, 1}};
    adj[3] = {{1, 10}, {2, 3}, {4, 4}, {5, 11}};
    adj[4] = {{2, 1}, {3, 4}, {5, 8}};
    adj[5] = {{1, 12}, {3, 11}, {4, 8}};

    cout << "Total Prim's MST Weight: " << primMST(0, numNodes, adj) << "\n";
    return 0;
}
