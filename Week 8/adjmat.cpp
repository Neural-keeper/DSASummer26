#include <iostream>
#include <vector>

using namespace std;

// ========================================================================
// 1. ADJACENCY MATRIX CLASS
// Space Complexity: O(V^2) - Always allocates a dense V x V grid.
// Best for: Dense graphs where edge lookups happen constantly.
// ========================================================================
class AdjacencyMatrixGraph {
private:
    int V;
    vector<vector<int>> matrix;

public:
    AdjacencyMatrixGraph(int vertices) : V(vertices), matrix(vertices, vector<int>(vertices, 0)) {}

    // Time Complexity: O(1)
    // Instantly targets the exact row and column to insert the weight.
    void addEdge(int u, int v, int w) {
        if (u >= 0 && u < V && v >= 0 && v < V) {
            matrix[u][v] = w;
        }
    }

    // Time Complexity: O(1)
    // Instantly sets the coordinates back to 0.
    void removeEdge(int u, int v) {
        if (u >= 0 && u < V && v >= 0 && v < V) {
            matrix[u][v] = 0;
        }
    }

    // Time Complexity: O(V)
    // Must scan the entire row of size V to find which columns contain non-zero weights.
    void printNeighbors(int u) const {
        if (u < 0 || u >= V) return;
        cout << "Node " << u << " connects to: ";
        for (int v = 0; v < V; ++v) {
            if (matrix[u][v] != 0) {
                cout << v << " (wt: " << matrix[u][v] << ") ";
            }
        }
        cout << "\n";
    }
};

int main() {
    AdjacencyMatrixGraph g(4);
    g.addEdge(0, 1, 5);
    g.addEdge(0, 2, 3);
    g.printNeighbors(0);
    
    g.removeEdge(0, 1);
    cout << "After removing edge 0 -> 1:\n";
    g.printNeighbors(0);
    return 0;
}
