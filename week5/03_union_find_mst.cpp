/*
 * ============================================================================
 *  UNION-FIND & KRUSKAL'S MST (Greedy Algorithm)
 * ============================================================================
 *  MST (Minimum Spanning Tree):
 *  - Both Kruskal's and Prim's are Greedy algorithms.
 *  - Greedy choice in Kruskal: Pick the edge with the smallest weight that 
 *    does not form a cycle.
 *  
 *  UNION-FIND (Disjoint Set Data Structure):
 *  - Used to efficiently check if adding an edge creates a cycle.
 *  - Operations:
 *    1. Find(i): Returns the root representative of the set containing i.
 *       - Optimization: Path Compression (flattens the tree during find).
 *    2. Union(i, j): Merges the sets containing i and j.
 *       - Optimization: Union by Rank (attaches smaller tree under larger tree).
 *  - Amortized Time Complexity: O(α(V)) where α is the inverse Ackermann function.
 *    Effectively O(1).
 *
 *  KRUSKAL'S TIME COMPLEXITY: O(E log E) or O(E log V) dominated by sorting the edges.
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
//  UNION-FIND IMPLEMENTATION
// ─────────────────────────────────────────────────────────────────────────────
class UnionFind {
private:
    vector<int> parent;
    vector<int> rank;

public:
    UnionFind(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        // Initially, each element is in its own set
        iota(parent.begin(), parent.end(), 0);
    }

    // Find with Path Compression
    int find(int i) {
        if (parent[i] == i) {
            return i;
        }
        // Path compression: make the parent of i directly the root
        return parent[i] = find(parent[i]);
    } // time complexity of find is O(α(n)) which is effectively O(1) for all practical purposes.

    // Union by Rank
    bool unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);

        // If they are in the same set, uniting them creates a cycle
        if (root_i == root_j) {
            return false;
        }

        // Attach smaller rank tree under root of higher rank tree
        if (rank[root_i] < rank[root_j]) {
            parent[root_i] = root_j;
        } else if (rank[root_i] > rank[root_j]) {
            parent[root_j] = root_i;
        } else {
            // Ranks are same, attach one to another and increment rank
            parent[root_j] = root_i;
            rank[root_i]++;
        }
        return true;
    } // time complexity of union is O(α(n)) which is effectively O(1) for all practical purposes.
};

// ─────────────────────────────────────────────────────────────────────────────
//  KRUSKAL'S MST
// ─────────────────────────────────────────────────────────────────────────────
struct Edge {
    int u, v, weight;
    // Overload < operator for sorting
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

void kruskalMST(int V, vector<Edge>& edges) {
    // 1. Sort edges by weight (Greedy choice)
    sort(edges.begin(), edges.end());

    UnionFind uf(V);
    int mst_weight = 0;
    int edges_added = 0;

    cout << "Edges in the Minimum Spanning Tree:\n";
    
    // 2. Iterate through sorted edges
    for (const auto& edge : edges) {
        // If uniting u and v doesn't create a cycle
        if (uf.unite(edge.u, edge.v)) {
            cout << edge.u << " -- " << edge.v << " == " << edge.weight << "\n";
            mst_weight += edge.weight;
            edges_added++;

            // Optimization: MST has exactly V-1 edges
            if (edges_added == V - 1) break;
        }
    }

    cout << "Total Cost of MST: " << mst_weight << "\n";
}

// ─────────────────────────────────────────────────────────────────────────────
//  DRIVER
// ─────────────────────────────────────────────────────────────────────────────
int main() {
    cout << "=== KRUSKAL'S MST & UNION-FIND ===\n";
    int V = 4;
    vector<Edge> edges = {
        {0, 1, 10},
        {0, 2, 6},
        {0, 3, 5},
        {1, 3, 15},
        {2, 3, 4}
    };

    kruskalMST(V, edges);

    return 0;
}

// key points of MST to remember -
// 1. MST is a subset of edges that connects all vertices with the minimum total weight and no cycles.
// 2. Kruskal's algorithm sorts edges by weight and adds them to the MST
//    if they don't create a cycle, using Union-Find to check for cycles.
// 3. Prim's algorithm grows the MST from a starting vertex by adding the smallest edge that connects the growing MST to a new vertex, using a priority queue to efficiently get the next edge
// 4. Both algorithms have a time complexity of O(E log E) or O(E log V) due to sorting edges (Kruskal's) or using a priority queue (Prim's).
// 5. cut property of MST: For any cut in the graph, the minimum weight edge crossing the cut must be in the MST. This is the basis for the greedy choice in both Prim's and Kruskal's algorithms. proof - 
