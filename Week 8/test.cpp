#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

struct Edge {
    int to;
    int weight;
};

struct Node {
    int id;
    int distance;
    bool operator>(const Node& other) const { return distance > other.distance; }
};

// reconstruct the path from parent array
void printPath(int target, const vector<int>& parent) {
    if (target == -1) return;
    printPath(parent[target], parent);
    cout << (char)('A' + target) << (target == -1 ? "" : " ");
}

void dijkstra(int start, int numNodes, const vector<vector<Edge>>& adj) {
    vector<int> dist(numNodes, INT_MAX);
    vector<int> parent(numNodes, -1); // Store the predecessor
    priority_queue<Node, vector<Node>, greater<Node>> pq;

    dist[start] = 0;
    pq.push({start, 0});

    while (!pq.empty()) {
        int u = pq.top().id;
        int d = pq.top().distance;
        pq.pop();

        if (d > dist[u]) continue;

        for (const auto& edge : adj[u]) {
            if (dist[u] + edge.weight < dist[edge.to]) {
                dist[edge.to] = dist[u] + edge.weight;
                parent[edge.to] = u; // Update parent
                pq.push({edge.to, dist[edge.to]});
            }
        }
    }

    // Print paths for all nodes
    for (int i = 0; i < numNodes; ++i) {
        cout << "Path to " << (char)('A' + i) << " (Dist: " << dist[i] << "): ";
        if (dist[i] == INT_MAX) cout << "No path";
        else printPath(i, parent);
        cout << endl;
    }
}

int main() {
    int numNodes = 6;
    vector<vector<Edge>> adj(numNodes);
    
    // Mapping: A=0, B=1, C=2, D=3, E=4, F=5
    adj[0] = {{1, 4}, {2, 2}};
    adj[1] = {{0, 4}, {2, 5}, {3, 10}, {5, 12}};
    adj[2] = {{0, 2}, {1, 5}, {3, 3}, {4, 1}};
    adj[3] = {{1, 10}, {2, 3}, {4, 4}, {5, 11}};
    adj[4] = {{2, 1}, {3, 4}, {5, 8}};
    adj[5] = {{1, 12}, {3, 11}, {4, 8}};
    // you found the hidden way to get the answer for the attendance form!

    dijkstra(0, numNodes, adj);

    return 0;
}