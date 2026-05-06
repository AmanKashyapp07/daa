/*
 * ============================================================================
 *  MINIMUM SPANNING TREE (MST) & CORRECTNESS PROOFS
 * ============================================================================
 *  CONCEPTS:
 *  - Spanning Tree: A subgraph that is a tree and includes all vertices.
 *  - Minimum Spanning Tree (MST): A spanning tree with the minimum possible
 *    total edge weight.
 *
 *  CORRECTNESS PROOF - THE CUT PROPERTY:
 *  - A "Cut" divides the vertices of a graph into two disjoint sets (S and V-S).
 *  - A "Crossing Edge" is an edge connecting a vertex in S to a vertex in V-S.
 *  - THEOREM: For any cut, the crossing edge with the MINIMUM weight must
 *    belong to the MST.
 *  - PROOF (by contradiction): Suppose the MST doesn't include the minimum
 *    crossing edge 'e'. Since the MST is connected, there must be some other
 *    crossing edge 'e_alt' connecting the two sets in the MST. If we remove
 *    'e_alt' and add 'e', the graph remains connected (still a spanning tree),
 *    but the total weight decreases (since weight(e) < weight(e_alt)).
 *    This contradicts the assumption that it was a *Minimum* Spanning Tree.
 *
 *  ALGORITHMS:
 *  1. KRUSKAL'S ALGORITHM:
 *     - Sort all edges by weight.
 *     - Pick the smallest edge. If it doesn't form a cycle (using Union-Find),
 *       add it to the MST.
 *     - Time: O(E log E) or O(E log V)
 *
 *  2. PRIM'S ALGORITHM:
 *     - Start with an arbitrary vertex.
 *     - Grow the MST by adding the minimum weight edge that connects a vertex
 *       in the MST to a vertex outside the MST (using Priority Queue).
 *     - Time: O((V + E) log V)
 *  For any cut (partition of vertices into S and V−S),
    the minimum weight edge crossing the cut is always part of some MST.
    In any cycle, the maximum weight edge cannot be part of MST.
 *  EXAM TIP:
 *  - Kruskal's is better for sparse graphs (E is small).
 *  - Prim's is better for dense graphs (E is large, closer to V^2).
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
//  KRUSKAL'S ALGORITHM
// ─────────────────────────────────────────────────────────────────────────────
struct Edge {
    int u, v, weight;
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

class DSU {
    vector<int> parent, rank;
public:
    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        iota(parent.begin(), parent.end(), 0); // Initialize parent[i] = i
    }
    int find(int i) {
        if (parent[i] == i) return i;
        return parent[i] = find(parent[i]); // Path compression
    }
    bool unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            if (rank[root_i] < rank[root_j]) swap(root_i, root_j);
            parent[root_j] = root_i;
            if (rank[root_i] == rank[root_j]) rank[root_i]++;
            return true;
        }
        return false;
    }
};

void kruskalMST(int V, vector<Edge>& edges) {
    sort(edges.begin(), edges.end()); // Sort edges by weight
    DSU dsu(V);
    int mst_weight = 0;
    cout << "Kruskal's MST Edges:\n";
    for (const auto& edge : edges) {
        if (dsu.unite(edge.u, edge.v)) { // If u and v are in different sets, unite them and include this edge
            cout << edge.u << " -- " << edge.v << " == " << edge.weight << "\n";
            mst_weight += edge.weight;
        }
    }
    cout << "Total MST Weight (Kruskal): " << mst_weight << "\n\n";
}

// ─────────────────────────────────────────────────────────────────────────────
//  PRIM'S ALGORITHM
// ─────────────────────────────────────────────────────────────────────────────
void primMST(int V, const vector<vector<pair<int, int>>>& adj) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> key(V, INT_MAX); // Minimum weight edge to connect vertex to MST
    vector<int> parent(V, -1);
    vector<bool> inMST(V, false);

    int start_vertex = 0;
    pq.push({0, start_vertex});
    key[start_vertex] = 0;

    int mst_weight = 0;

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (inMST[u]) continue;
        inMST[u] = true;

        for (auto x : adj[u]) {
            int v = x.first;
            int weight = x.second;

            if (!inMST[v] && key[v] > weight) {
                key[v] = weight;
                pq.push({key[v], v});
                parent[v] = u;
            }
        }
    }

    cout << "Prim's MST Edges:\n";
    for (int i = 1; i < V; ++i) {
        if (parent[i] != -1) {
            cout << parent[i] << " -- " << i << " == " << key[i] << "\n";
            mst_weight += key[i];
        }
    }
    cout << "Total MST Weight (Prim): " << mst_weight << "\n";
}

// ─────────────────────────────────────────────────────────────────────────────
//  DRIVER
// ─────────────────────────────────────────────────────────────────────────────
int main() {
    int V = 5;
    // Edge list for Kruskal
    vector<Edge> edges = {
        {0, 1, 2}, {0, 3, 6}, {1, 2, 3},
        {1, 3, 8}, {1, 4, 5}, {2, 4, 7}, {3, 4, 9}
    };

    // Adjacency list for Prim
    vector<vector<pair<int, int>>> adj(V);
    for (const auto& e : edges) {
        adj[e.u].push_back({e.v, e.weight});
        adj[e.v].push_back({e.u, e.weight});
    }

    kruskalMST(V, edges);
    primMST(V, adj);

    return 0;
}
