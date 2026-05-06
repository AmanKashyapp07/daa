/*
 * ============================================================================
 *  CYCLE DETECTION IN UNDIRECTED GRAPHS
 * ============================================================================
 *  Two approaches:
 *
 *  METHOD 1: DFS-based
 *  - If we visit a neighbor that is already visited AND is not the parent
 *    of the current vertex → CYCLE found.
 *  - Time: O(V + E) | Space: O(V)
 *
 *  METHOD 2: Union-Find (Disjoint Set Union)
 *  - For each edge (u, v): if u and v are in same set → CYCLE.
 *    Otherwise, union them.
 *  - Time: O(E · α(V)) ≈ O(E) | Space: O(V)
 *    (α is inverse Ackermann, practically constant)
 *
 *  KEY INSIGHT: In undirected graph, every edge creates two adjacency entries.
 *  We track the parent to avoid counting u→v→u as a cycle.
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
//  METHOD 1: DFS-Based Cycle Detection (Undirected)
// ─────────────────────────────────────────────────────────────────────────────
// Logic: If DFS reaches a visited vertex that is NOT the parent → cycle.
// Time: O(V + E) | Space: O(V)
bool dfsCycleUndirected(int u, int parent, vector<vector<int>>& adj,
                        vector<bool>& visited) {
    visited[u] = true;

    for (int v : adj[u]) {
        if (!visited[v]) {
            // Explore unvisited neighbor
            if (dfsCycleUndirected(v, u, adj, visited))
                return true;
        } else if (v != parent) {
            // Visited neighbor that is NOT parent → back edge → cycle
            return true;
        }
    }
    return false;
}

bool hasCycleDFS(vector<vector<int>>& adj, int V) {
    vector<bool> visited(V, false);
    // Check all components (graph might be disconnected)
    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            if (dfsCycleUndirected(i, -1, adj, visited))
                return true;
        }
    }
    return false;
}

// ─────────────────────────────────────────────────────────────────────────────
//  METHOD 2: Union-Find (DSU) Cycle Detection
// ─────────────────────────────────────────────────────────────────────────────
// Logic: Process each edge. If both endpoints are in same component → cycle.
// Uses path compression + union by rank for near O(1) per operation.
// Time: O(E · α(V)) ≈ O(E) | Space: O(V)
class DSU {
    vector<int> parent, rank_;
public:
    DSU(int n) : parent(n), rank_(n, 0) {
        iota(parent.begin(), parent.end(), 0); // parent[i] = i
    }

    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]); // Path compression
        return parent[x];
    }

    // Returns false if u and v are already in same set (cycle!)
    bool unite(int u, int v) {
        int pu = find(u), pv = find(v);
        if (pu == pv) return false; // Same set → cycle

        // Union by rank
        if (rank_[pu] < rank_[pv]) swap(pu, pv);
        parent[pv] = pu;
        if (rank_[pu] == rank_[pv]) rank_[pu]++;
        return true;
    }
};

bool hasCycleDSU(vector<pair<int,int>>& edges, int V) {
    DSU dsu(V);
    for (auto& [u, v] : edges) {
        if (!dsu.unite(u, v)) {
            cout << "  Cycle detected at edge (" << u << ", " << v << ")\n";
            return true;
        }
    }
    return false;
}

int main() {
    /*
     * Graph WITH cycle:       Graph WITHOUT cycle:
     *   0 - 1                   0 - 1
     *   |   |                   |
     *   3 - 2                   2 - 3
     */

    // --- Graph with cycle ---
    int V1 = 4;
    vector<vector<int>> adj1(V1);
    auto add = [](vector<vector<int>>& a, int u, int v) {
        a[u].push_back(v); a[v].push_back(u);
    };
    add(adj1,0,1); add(adj1,1,2); add(adj1,2,3); add(adj1,3,0);

    cout << "=== DFS CYCLE DETECTION ===\n";
    cout << "Graph 1 (with cycle): "
         << (hasCycleDFS(adj1, V1) ? "CYCLE FOUND" : "No cycle") << "\n";

    // --- Graph without cycle ---
    int V2 = 4;
    vector<vector<int>> adj2(V2);
    add(adj2,0,1); add(adj2,0,2); add(adj2,2,3);

    cout << "Graph 2 (no cycle):   "
         << (hasCycleDFS(adj2, V2) ? "CYCLE FOUND" : "No cycle") << "\n";

    // --- Union-Find approach ---
    cout << "\n=== UNION-FIND CYCLE DETECTION ===\n";
    vector<pair<int,int>> edges1 = {{0,1},{1,2},{2,3},{3,0}};
    cout << "Graph 1: "
         << (hasCycleDSU(edges1, 4) ? "CYCLE FOUND" : "No cycle") << "\n";

    vector<pair<int,int>> edges2 = {{0,1},{0,2},{2,3}};
    cout << "Graph 2: "
         << (hasCycleDSU(edges2, 4) ? "CYCLE FOUND" : "No cycle") << "\n";

    return 0;
}

/*
 * EXAM TIPS:
 * 1. Undirected: visited neighbor ≠ parent → cycle (DFS).
 * 2. Union-Find: same component before edge addition → cycle.
 * 3. DFS method works for adjacency list; DSU works on edge list.
 * 4. Both are O(V+E), but DSU has smaller constant factor.
 */
