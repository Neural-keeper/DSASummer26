#include <iostream>
#include <vector>
#include <algorithm> // for the "sort" function

using namespace std;

struct Edge {
    int src, dest, wt;
};

// FAST BLACK BOX: Union-Find (DSU) to catch graph cycles
int find_set(int v, vector<int>& parent) {
    if (v == parent[v]) return v;
    return parent[v] = find_set(parent[v], parent); // Path compression optimization
}

int kruskalMST(int V, vector<Edge>& edges) {
    // 1. Sort all edges globally by weight using a custom lambda function
    sort(edges.begin(), edges.end(), [](Edge a, Edge b) {
        return a.wt < b.wt;
    });

    // Initialize DSU tracking arrays, V is the number of vertices
    vector<int> parent(V);
    for (int i = 0; i < V; i++) parent[i] = i;

    int total_mst_weight = 0;
    int edges_counted = 0;

    // 2. Iterate through sorted edge list greedily
    for (const Edge& e : edges) {
        int root_src = find_set(e.src, parent);
        int root_dest = find_set(e.dest, parent);

        // If parents do not match, adding this edge creates no structural cycles
        if (root_src != root_dest) {
            total_mst_weight += e.wt;
            parent[root_src] = root_dest; // Union - setting their parents as the same
            edges_counted++;
            if (edges_counted == V - 1) break; // stops when it gets to the max edges for MST
        }
    }
    return total_mst_weight;
}

int main() {
    int V = 6;
    vector<Edge> edges = {
        {0, 1, 4}, {0, 2, 2}, {1, 2, 5}, {1, 3, 10}, {1, 5, 12}, {2, 3, 3}, {3, 5, 11}, {2, 4, 1}, {4, 5, 8}, {3, 4, 4}
    };

    cout << "Total Kruskal's MST Weight: " << kruskalMST(V, edges) << "\n";
    return 0;
}
