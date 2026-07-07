#include <iostream>
#include <vector>

using namespace std;

// ========================================================================
// 2. ADJACENCY LIST CLASS
// Space Complexity: O(V + E) - Highly dynamic, stores pairs of {neighbor, weight}.
// Best for: Sparse graphs where memory minimization is vital.
// ========================================================================
class AdjacencyListGraph {
private:
    int V;
    vector<vector<pair<int, int>>> adj; // Stores: {destination, weight}

public:
    AdjacencyListGraph(int vertices) : V(vertices), adj(vertices) {}

    // Time Complexity: O(1)
    // Simply appends the weight pair directly to the vector array slot at index u.
    void addEdge(int u, int v, int w) {
        if (u >= 0 && u < V && v >= 0 && v < V) {
            adj[u].push_back({v, w});
        }
    }

    // Time Complexity: O(out-degree of u) -> O(V) worst case
    // Must sequentially search through node u's sub-vector to find and erase the target connection.
    void removeEdge(int u, int v) {
        if (u < 0 || u >= V) return;
        for (auto it = adj[u].begin(); it != adj[u].end(); ++it) {
            if (it->first == v) {
                adj[u].erase(it);
                break; // Assumes simple graph with no parallel duplicate edges
            }
        }
    }

    // Time Complexity: O(out-degree of u) -> O(V) worst case
    // Iterates cleanly through only the valid neighbors packed into node u's specific array list.
    void printNeighbors(int u) const {
        if (u < 0 || u >= V) return;
        cout << "Node " << u << " connects to: ";
        for (auto& [neighbor, wt] : adj[u]) {
            cout << neighbor << " (wt: " << wt << ") ";
        }
        cout << "\n";
    }
};

int main() {
    AdjacencyListGraph g(4);
    g.addEdge(0, 1, 5);
    g.addEdge(0, 2, 3);
    g.printNeighbors(0);
    
    g.removeEdge(0, 1);
    cout << "After removing edge 0 -> 1:\n";
    g.printNeighbors(0);
    return 0;
}
