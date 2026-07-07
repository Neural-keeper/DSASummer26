/*
Pretty much just the extras
*/

// Incidence Matrix
#include <iostream>
#include <vector>

using namespace std;

// ========================================================================
// 4. INCIDENCE MATRIX CLASS
// Space Complexity: O(V * E) - Massive space overhead mapping nodes vs edges.
// Best for: Specialized mathematical modeling (flows / physics vectors). Unviable for code traversals.
// ========================================================================
class IncidenceMatrixGraph {
private:
    int V;
    int edgeCount;
    vector<vector<int>> matrix; // V rows x E columns. Stores edge directional signs.
    vector<int> edgeWeights;    // Separate lookup vector tracking edge weights mapped by column index.
    vector<pair<int, int>> edgeConnections; // Tracks {src, dest} for each column index.

public:
    IncidenceMatrixGraph(int vertices) : V(vertices), edgeCount(0) {}

    // Time Complexity: O(V)
    // Adding an edge appends a completely new column. Every single existing row must be resized.
    void addEdge(int u, int v, int w) {
        if (u < 0 || u >= V || v < 0 || v >= V) return;
        
        edgeCount++;
        for (int i = 0; i < V; ++i) {
            matrix[i].push_back(0); // Add a slot for the new column index
        }
        
        int currentEdgeColumn = edgeCount - 1;
        matrix[u][currentEdgeColumn] = -1; // -1 marks leaving the node (source)
        matrix[v][currentEdgeColumn] = 1;  //  1 marks entering the node (dest)
        
        edgeWeights.push_back(w);
        edgeConnections.push_back({u, v});
    }

    // Time Complexity: O(V * E)
    // Dropping a connection involves identifying the column index, erasing elements out of rows,
    // and adjusting structural state. Wastes immense computational cycles.
    void removeEdge(int u, int v) {
        int targetColumn = -1;
        for (int e = 0; e < edgeCount; ++e) {
            if (matrix[u][e] == -1 && matrix[v][e] == 1) {
                targetColumn = e;
                break;
            }
        }
        
        if (targetColumn == -1) return; // Edge not found

        // Erase column data across all row vectors
        for (int i = 0; i < V; ++i) {
            matrix[i].erase(matrix[i].begin() + targetColumn);
        }
        edgeWeights.erase(edgeWeights.begin() + targetColumn);
        edgeConnections.erase(edgeConnections.begin() + targetColumn);
        edgeCount--;
    }

    // Time Complexity: O(E)
    // Must scan through every edge column index mapping to see if row index u is flagged as a source (-1).
    void printNeighbors(int u) const {
        if (u < 0 || u >= V) return;
        cout << "Node " << u << " connects to: ";
        for (int e = 0; e < edgeCount; ++e) {
            if (matrix[u][e] == -1) { // Node u is the departure point
                int destinationNode = edgeConnections[e].second;
                cout << destinationNode << " (wt: " << edgeWeights[e] << ") ";
            }
        }
        cout << "\n";
    }
};

int main() {
    IncidenceMatrixGraph g(4);
    g.addEdge(0, 1, 5);
    g.addEdge(0, 2, 3);
    g.printNeighbors(0);
    
    g.removeEdge(0, 1);
    cout << "After removing edge 0 -> 1:\n";
    g.printNeighbors(0);
    return 0;
}
