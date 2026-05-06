/*
 * ============================================================================
 *  GRAPH REPRESENTATIONS
 * ============================================================================
 *  Two primary ways to represent a graph G = (V, E):
 *
 *  1. ADJACENCY MATRIX:
 *     - A 2D array adj[V][V] where adj[i][j] = 1 if edge (i,j) exists.
 *     - Space: O(V^2)
 *     - Edge lookup: O(1)
 *     - Add edge: O(1)
 *     - List all neighbors of u: O(V)
 *     - Best for: Dense graphs (E ≈ V^2)
 *
 *  2. ADJACENCY LIST:
 *     - An array of lists. adj[u] contains all vertices v such that (u,v) ∈ E.
 *     - Space: O(V + E)
 *     - Edge lookup: O(degree(u))
 *     - Add edge: O(1)
 *     - List all neighbors of u: O(degree(u))
 *     - Best for: Sparse graphs (E << V^2), which is the common case.
 *
 *  EXAM TIP: Most graph algorithms use adjacency list because real-world
 *  graphs are sparse. Adjacency matrix is useful when you need O(1) edge
 *  queries or the graph is dense.
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <deque>
#include <limits>
#include <climits>
#include <cstring>
#include <numeric>
using namespace std;

// ─────────────────────────────────────────────────────────────────────────────
//  1. ADJACENCY MATRIX REPRESENTATION
// ─────────────────────────────────────────────────────────────────────────────
class GraphMatrix {
    int V;
    vector<vector<int>> adj;

public:
    GraphMatrix(int V) : V(V), adj(V, vector<int>(V, 0)) {}

    // Add edge (undirected). For directed, remove the second line.
    void addEdge(int u, int v) {
        adj[u][v] = 1;
        adj[v][u] = 1; // Remove for directed graph
    }

    // Check if edge exists — O(1)
    bool hasEdge(int u, int v) {
        return adj[u][v] == 1;
    }

    // Print all neighbors of vertex u — O(V)
    void printNeighbors(int u) {
        cout << "Neighbors of " << u << ": ";
        for (int v = 0; v < V; v++) {
            if (adj[u][v]) cout << v << " ";
        }
        cout << "\n";
    }

    // Print full matrix
    void printMatrix() {
        cout << "Adjacency Matrix:\n";
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                cout << adj[i][j] << " ";
            }
            cout << "\n";
        }
    }
};

// ─────────────────────────────────────────────────────────────────────────────
//  2. ADJACENCY LIST REPRESENTATION
// ─────────────────────────────────────────────────────────────────────────────
class GraphList {
    int V;
    vector<vector<int>> adj;

public:
    GraphList(int V) : V(V), adj(V) {}

    // Add edge (undirected). For directed, remove the second line.
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u); // Remove for directed graph
    }

    // Print all neighbors of vertex u — O(degree(u))
    void printNeighbors(int u) {
        cout << "Neighbors of " << u << ": ";
        for (int v : adj[u]) {
            cout << v << " ";
        }
        cout << "\n";
    }

    // Print full adjacency list
    void printList() {
        cout << "Adjacency List:\n";
        for (int i = 0; i < V; i++) {
            cout << i << " -> ";
            for (int v : adj[i]) {
                cout << v << " ";
            }
            cout << "\n";
        }
    }
};

// ─────────────────────────────────────────────────────────────────────────────
//  3. WEIGHTED GRAPH (Adjacency List with weights)
// ─────────────────────────────────────────────────────────────────────────────
class WeightedGraph {
    int V;
    vector<vector<pair<int, int>>> adj; // adj[u] = {(v, weight), ...}

public:
    WeightedGraph(int V) : V(V), adj(V) {}

    void addEdge(int u, int v, int w) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w}); // Remove for directed
    }

    void printList() {
        cout << "Weighted Adjacency List:\n";
        for (int i = 0; i < V; i++) {
            cout << i << " -> ";
            for (auto& [v, w] : adj[i]) {
                cout << "(" << v << ", w=" << w << ") ";
            }
            cout << "\n";
        }
    }
};

// ─────────────────────────────────────────────────────────────────────────────
//  DRIVER
// ─────────────────────────────────────────────────────────────────────────────
int main() {
    /*
     * Example graph (undirected):
     *
     *     0 --- 1
     *     |   / |
     *     |  /  |
     *     | /   |
     *     2 --- 3
     */

    cout << "=== ADJACENCY MATRIX ===\n";
    GraphMatrix gm(4);
    gm.addEdge(0, 1);
    gm.addEdge(0, 2);
    gm.addEdge(1, 2);
    gm.addEdge(1, 3);
    gm.addEdge(2, 3);
    gm.printMatrix();
    gm.printNeighbors(1);
    cout << "Edge (0,3) exists? " << (gm.hasEdge(0, 3) ? "Yes" : "No") << "\n";
    cout << "Edge (0,1) exists? " << (gm.hasEdge(0, 1) ? "Yes" : "No") << "\n";

    cout << "\n=== ADJACENCY LIST ===\n";
    GraphList gl(4);
    gl.addEdge(0, 1);
    gl.addEdge(0, 2);
    gl.addEdge(1, 2);
    gl.addEdge(1, 3);
    gl.addEdge(2, 3);
    gl.printList();
    gl.printNeighbors(1);

    cout << "\n=== WEIGHTED GRAPH ===\n";
    WeightedGraph wg(4);
    wg.addEdge(0, 1, 10);
    wg.addEdge(0, 2, 6);
    wg.addEdge(1, 2, 3);
    wg.addEdge(1, 3, 7);
    wg.addEdge(2, 3, 4);
    wg.printList();

    return 0;
}

/*
 * ============================================================================
 *  COMPLEXITY COMPARISON TABLE
 * ============================================================================
 *
 *  Operation           | Adj. Matrix | Adj. List
 *  --------------------|-------------|------------------
 *  Space               | O(V^2)      | O(V + E)
 *  Add Edge            | O(1)        | O(1)
 *  Remove Edge         | O(1)        | O(E)
 *  Check Edge (u,v)    | O(1)        | O(degree(u))
 *  List Neighbors(u)   | O(V)        | O(degree(u))
 *  Iterate All Edges   | O(V^2)      | O(V + E)
 *
 * ============================================================================
 *  WHEN TO USE WHAT:
 *  - Adjacency Matrix: Dense graphs, frequent edge-existence queries.
 *  - Adjacency List:   Sparse graphs (most practical cases), BFS/DFS.
 * ============================================================================
 */
