/*
 * ============================================================================
 *  DEPTH-FIRST SEARCH (DFS)
 * ============================================================================
 *  LOGIC:
 *  - Explores as deep as possible before backtracking. Uses STACK.
 *  - TIME: O(V + E) | SPACE: O(V)
 *
 *  DFS EDGE CLASSIFICATION (directed graphs):
 *  - Tree edge: to unvisited vertex (WHITE)
 *  - Back edge: to ancestor (GRAY) → CYCLE!
 *  - Forward edge: to descendant (BLACK, d[u] < d[v])
 *  - Cross edge: to different subtree (BLACK, d[u] > d[v])
 *
 *  A directed graph has a cycle ⟺ DFS finds a back edge.
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

// 1. BASIC DFS (Recursive) — O(V+E) time, O(V) space
void dfs(int u, vector<vector<int>>& adj, vector<bool>& visited) {
    visited[u] = true;
    cout << u << " ";
    for (int v : adj[u])
        if (!visited[v]) dfs(v, adj, visited);
}

void dfsAll(vector<vector<int>>& adj, int V) {
    vector<bool> vis(V, false);
    int comp = 0;
    for (int i = 0; i < V; i++) {
        if (!vis[i]) {
            cout << "Component " << ++comp << ": ";
            dfs(i, adj, vis);
            cout << "\n";
        }
    }
}

int main() {
    // Undirected graph: 0-1, 0-2, 1-3, 1-4, 2-3, and 5-6
    int V = 7;
    vector<vector<int>> adj(V);
    auto addEdge = [&](int u, int v) { adj[u].push_back(v); adj[v].push_back(u); };
    addEdge(0,1); addEdge(0,2); addEdge(1,3); addEdge(1,4); addEdge(2,3); addEdge(5,6);

    cout << "=== RECURSIVE DFS from 0 ===\n";
    vector<bool> vis(V, false);
    dfs(0, adj, vis);
    cout << "\n";
    return 0;
}

/*
 * KEY EXAM POINTS:
 * 1. DFS uses STACK (recursion or explicit). BFS uses QUEUE.
 * 2. Back edge ⟹ cycle in directed graph.
 * 3. Parenthesis theorem: [d[u],f[u]] intervals are nested or disjoint.
 * 4. DFS is foundation for: topological sort, SCC, cycle detection.
 * 5. DFS does NOT give shortest paths (unlike BFS).
 */
