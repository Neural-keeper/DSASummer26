#include <iostream>
#include <vector>

using namespace std;

struct Edge {
    int src;
    int dest;
    int wt;
};

// ========================================================================
// 3. EDGE LIST CLASS
// Space Complexity: O(E) (since it's just edges)
// Best for: Global sorting operations and algorithms like Kruskal's
// ========================================================================
class Graph {
private:
    int V;
    vector<Edge> edges;

public:
    Graph(int vertices) : V(vertices) {}

    // Time Complexity: O(1)
    // Standard flat vector push operation back loading onto the container sequence.
    void addEdge(int u, int v, int w) {
        edges.push_back({u, v, w});
    }

    // Time Complexity: O(E)
    // Must run a full sequential scan across every single edge structure in the graph to drop matches.
    void removeEdge(int u, int v) {
        for (auto it = edges.begin(); it != edges.end(); ++it) {
            if (it->src == u && it->dest == v) {
                edges.erase(it);
                break; 
            }
        }
    }

    // Time Complexity: O(E)
    // Horribly inefficient traversal! Must loop across all global edges to evaluate if any have src == u.
    void printNeighbors(int u) const {
        cout << "Node " << u << " connects to: ";
        for (const auto& edge : edges) {
            if (edge.src == u) {
                cout << edge.dest << " (wt: " << edge.wt << ") ";
            }
        }
        cout << "\n";
    }
};

int main() {
    Graph g(4);
    g.addEdge(0, 1, 5);
    g.addEdge(0, 2, 3);
    g.printNeighbors(0);
    
    g.removeEdge(0, 1);
    cout << "After removing edge 0 -> 1:\n";
    g.printNeighbors(0);
    return 0;
}
