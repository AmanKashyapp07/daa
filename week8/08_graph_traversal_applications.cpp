/*
 * ============================================================================
 *  APPLICATIONS OF GRAPH TRAVERSAL
 * ============================================================================
 *  This file covers important applications commonly asked in exams:
 *
 *  1. BIPARTITE CHECK (BFS) — Can vertices be 2-colored?
 *  2. CONNECTED COMPONENTS (DFS/BFS) — Count/find components
 *  3. SHORTEST PATH IN UNWEIGHTED GRAPH (BFS)
 *  4. PATH EXISTENCE CHECK
 *  5. STRONGLY CONNECTED COMPONENTS (Kosaraju's Algorithm)
 *
 *  All applications use BFS or DFS as building blocks.
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
//  1. BIPARTITE CHECK (BFS 2-Coloring)
// ─────────────────────────────────────────────────────────────────────────────
// A graph is bipartite ⟺ it contains no odd-length cycle.
// Algorithm: Try to 2-color using BFS. If a neighbor has same color → not bipartite.
// Time: O(V + E) | Space: O(V)
bool isBipartite(vector<vector<int>>& adj, int V) {
    vector<int> color(V, -1); // -1 = uncolored

    for (int start = 0; start < V; start++) {
        if (color[start] != -1) continue;

        queue<int> q;
        color[start] = 0;
        q.push(start);

        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : adj[u]) {
                if (color[v] == -1) {
                    color[v] = 1 - color[u]; // Alternate color
                    q.push(v);
                } else if (color[v] == color[u]) {
                    return false; // Same color neighbor → NOT bipartite
                }
            }
        }
    }
    return true;
}

// ─────────────────────────────────────────────────────────────────────────────
//  2. CONNECTED COMPONENTS (DFS)
// ─────────────────────────────────────────────────────────────────────────────
// Find all connected components and list their vertices.
// Time: O(V + E) | Space: O(V)
void dfsComponent(int u, vector<vector<int>>& adj, vector<bool>& vis,
                  vector<int>& comp) {
    vis[u] = true;
    comp.push_back(u);
    for (int v : adj[u])
        if (!vis[v]) dfsComponent(v, adj, vis, comp);
}

vector<vector<int>> findComponents(vector<vector<int>>& adj, int V) {
    vector<bool> vis(V, false);
    vector<vector<int>> components;
    for (int i = 0; i < V; i++) {
        if (!vis[i]) {
            vector<int> comp;
            dfsComponent(i, adj, vis, comp);
            components.push_back(comp);
        }
    }
    return components;
}

// ─────────────────────────────────────────────────────────────────────────────
//  3. SHORTEST PATH IN UNWEIGHTED GRAPH (BFS)
// ─────────────────────────────────────────────────────────────────────────────
// Returns shortest distance from src to all vertices. -1 if unreachable.
// Time: O(V + E) | Space: O(V)
vector<int> shortestPathUnweighted(int src, vector<vector<int>>& adj, int V) {
    vector<int> dist(V, -1);
    queue<int> q;
    dist[src] = 0;
    q.push(src);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    return dist;
}

// ─────────────────────────────────────────────────────────────────────────────
//  4. PATH EXISTENCE CHECK (DFS)
// ─────────────────────────────────────────────────────────────────────────────
// Check if a path exists from src to dest.
// Time: O(V + E) | Space: O(V)
bool hasPath(int u, int dest, vector<vector<int>>& adj, vector<bool>& vis) {
    if (u == dest) return true;
    vis[u] = true;
    for (int v : adj[u])
        if (!vis[v] && hasPath(v, dest, adj, vis))
            return true;
    return false;
}

// ─────────────────────────────────────────────────────────────────────────────
//  5. STRONGLY CONNECTED COMPONENTS (Kosaraju's Algorithm)
// ─────────────────────────────────────────────────────────────────────────────
// A maximal set of vertices such that every vertex is reachable from every other.
// Algorithm (Kosaraju's — 2 DFS passes):
//   1. DFS on original graph, push to stack by finish time.
//   2. Transpose the graph (reverse all edges).
//   3. DFS on transposed graph in stack order → each DFS tree = one SCC.
//
// Time: O(V + E) | Space: O(V + E) for transpose
void dfs1(int u, vector<vector<int>>& adj, vector<bool>& vis, stack<int>& st) {
    vis[u] = true;
    for (int v : adj[u])
        if (!vis[v]) dfs1(v, adj, vis, st);
    st.push(u); // Push by finish time
} // this is to fill the stack with vertices in order of their finishing times in the first DFS pass

void dfs2(int u, vector<vector<int>>& radj, vector<bool>& vis, vector<int>& comp) {
    vis[u] = true;
    comp.push_back(u);
    for (int v : radj[u])
        if (!vis[v]) dfs2(v, radj, vis, comp);
} // this is to collect all vertices in the current strongly connected component during the second DFS pass on the transposed graph

vector<vector<int>> kosarajuSCC(vector<vector<int>>& adj, int V) {
    // Pass 1: DFS on original, record finish order
    stack<int> st;
    vector<bool> vis(V, false);
    for (int i = 0; i < V; i++)
        if (!vis[i]) dfs1(i, adj, vis, st);

    // Build transpose graph
    vector<vector<int>> radj(V);
    for (int u = 0; u < V; u++)
        for (int v : adj[u]) radj[v].push_back(u);

    // Pass 2: DFS on transpose in finish-time order
    fill(vis.begin(), vis.end(), false);
    vector<vector<int>> sccs;
    while (!st.empty()) {
        int u = st.top(); st.pop();
        if (!vis[u]) {
            vector<int> comp;
            dfs2(u, radj, vis, comp);
            sccs.push_back(comp);
        }
    }
    return sccs;
}

int main() {
    // --- Bipartite check ---
    cout << "=== BIPARTITE CHECK ===\n";
    // Bipartite: 0-1, 1-2, 2-3 (path graph, always bipartite)
    int V1 = 4;
    vector<vector<int>> g1(V1);
    g1[0]={1}; g1[1]={0,2}; g1[2]={1,3}; g1[3]={2};
    cout << "Path graph: " << (isBipartite(g1,V1) ? "Bipartite" : "Not bipartite") << "\n";

    // Not bipartite: triangle 0-1-2-0
    vector<vector<int>> g2(3);
    g2[0]={1,2}; g2[1]={0,2}; g2[2]={0,1};
    cout << "Triangle:   " << (isBipartite(g2,3) ? "Bipartite" : "Not bipartite") << "\n";

    // --- Connected components ---
    cout << "\n=== CONNECTED COMPONENTS ===\n";
    int V2 = 7;
    vector<vector<int>> g3(V2);
    auto add = [&](int u, int v) { g3[u].push_back(v); g3[v].push_back(u); };
    add(0,1); add(1,2); add(3,4); add(5,6);
    auto comps = findComponents(g3, V2);
    for (int i = 0; i < (int)comps.size(); i++) {
        cout << "Component " << i+1 << ": ";
        for (int v : comps[i]) cout << v << " ";
        cout << "\n";
    }

    // --- Shortest path (unweighted) ---
    cout << "\n=== SHORTEST PATH (Unweighted, from 0) ===\n";
    auto dist = shortestPathUnweighted(0, g3, V2);
    for (int i = 0; i < V2; i++)
        cout << "dist[" << i << "] = " << dist[i] << "\n";

    // --- SCC (Kosaraju's) ---
    cout << "\n=== STRONGLY CONNECTED COMPONENTS ===\n";
    /*  0→1→2→0 (SCC), 2→3→4 (chain) */
    int V3 = 5;
    vector<vector<int>> dg(V3);
    dg[0]={1}; dg[1]={2}; dg[2]={0,3}; dg[3]={4};
    auto sccs = kosarajuSCC(dg, V3);
    for (int i = 0; i < (int)sccs.size(); i++) {
        cout << "SCC " << i+1 << ": ";
        for (int v : sccs[i]) cout << v << " ";
        cout << "\n";
    }

    return 0;
}

/*
 * ============================================================================
 *  SUMMARY TABLE
 * ============================================================================
 *  Application            | Method | Time     | Space   | Key Idea
 *  -----------------------|--------|----------|---------|----------------------
 *  Bipartite check        | BFS    | O(V + E) | O(V)    | 2-coloring
 *  Connected components   | DFS    | O(V + E) | O(V)    | DFS on each unvisited
 *  Shortest path (unwtd)  | BFS    | O(V + E) | O(V)    | Level-by-level
 *  Path existence         | DFS    | O(V + E) | O(V)    | Reachability
 *  SCC (Kosaraju)         | 2×DFS  | O(V + E) | O(V+E)  | Finish order + transpose
 *
 *  EXAM TIPS:
 *  1. Bipartite ⟺ no odd cycle ⟺ 2-colorable.
 *  2. BFS gives shortest path in unweighted graphs.
 *  3. Kosaraju's: DFS finish order → transpose → DFS again.
 *  4. SCC reduces directed graph to a DAG of components.
 * ============================================================================
 */
