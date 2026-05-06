/*
 * ============================================================================
 *  CYCLE DETECTION IN DIRECTED GRAPHS
 * ============================================================================
 *  METHOD: DFS with 3-color marking.
 *
 *  Colors:
 *    WHITE (0) = unvisited
 *    GRAY  (1) = currently in DFS recursion stack (being explored)
 *    BLACK (2) = fully processed (all descendants finished)
 *
 *  RULE: If we encounter a GRAY vertex during DFS → back edge → CYCLE.
 *
 *  WHY parent-check doesn't work for directed graphs:
 *  In directed graphs, u→v and v→u are distinct edges. Simply checking
 *  "not parent" would miss cases. The 3-color approach is correct because
 *  GRAY means the vertex is an ancestor in the current DFS path.
 *
 *  TIME: O(V + E) | SPACE: O(V)
 *
 *  ALTERNATIVE: Kahn's algorithm (topological sort). If we cannot process
 *  all V vertices (result.size() < V), there's a cycle.
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


// method 1 : we are using inPath stack to check if we are visiting a node which is already in the current path of DFS, if yes then we have a cycle.
bool dfsCycle(int u, vector<vector<int>>& adj, vector<bool>& visited, vector<bool>& inPath) {
    visited[u] = true;
    inPath[u] = true; // mark current vertex as being in the current path

    for (int v : adj[u]) {
        if (!visited[v]) {
            if (dfsCycle(v, adj, visited, inPath))
                return true;
        }
        else if (inPath[v]) { // visited and in current path → back edge → cycle
            return true;
        }
    }

    inPath[u] = false; // backtrack: remove from current path
    return false;
}

bool hasCycleDirected(vector<vector<int>>& adj, int V) {
    vector<bool> visited(V, false);
    vector<bool> inPath(V, false);

    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            if (dfsCycle(i, adj, visited, inPath))
                return true;
        }
    }

    return false;
}
// ─────────────────────────────────────────────────────────────────────────────
//  METHOD 2: Kahn's Algorithm (BFS) Cycle Detection
// ─────────────────────────────────────────────────────────────────────────────
// If topological sort cannot include all vertices → cycle exists.
// Time: O(V + E) | Space: O(V)
bool hasCycleKahn(vector<vector<int>>& adj, int V) {
    vector<int> inDeg(V, 0);
    for (int u = 0; u < V; u++)
        for (int v : adj[u]) inDeg[v]++;

    queue<int> q;
    for (int i = 0; i < V; i++)
        if (inDeg[i] == 0) q.push(i);

    int processed = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        processed++;
        for (int v : adj[u]) {
            inDeg[v]--;
            if (inDeg[v] == 0) q.push(v);
        }
    }
    return processed != V; // true if cycle exists
}

// ─────────────────────────────────────────────────────────────────────────────
//  BONUS: Find and print the actual cycle path
// ─────────────────────────────────────────────────────────────────────────────
int cycleStart = -1, cycleEnd = -1;

bool dfsFindCycle(int u, vector<vector<int>>& adj, vector<int>& color,
                  vector<int>& parent) {
    color[u] = 1;
    for (int v : adj[u]) {
        if (color[v] == 1) {
            cycleEnd = u;
            cycleStart = v;
            return true;
        }
        if (color[v] == 0) {
            parent[v] = u;
            if (dfsFindCycle(v, adj, color, parent))
                return true;
        }
    }
    color[u] = 2;
    return false;
}

void printCycle(vector<vector<int>>& adj, int V) {
    vector<int> color(V, 0), parent(V, -1);
    cycleStart = cycleEnd = -1;

    for (int i = 0; i < V; i++) {
        if (color[i] == 0 && dfsFindCycle(i, adj, color, parent))
            break;
    }

    if (cycleStart == -1) { cout << "No cycle.\n"; return; }

    // Reconstruct cycle path
    vector<int> cycle;
    cycle.push_back(cycleStart);
    for (int v = cycleEnd; v != cycleStart; v = parent[v])
        cycle.push_back(v);
    cycle.push_back(cycleStart);
    reverse(cycle.begin(), cycle.end());

    cout << "Cycle: ";
    for (int i = 0; i < (int)cycle.size(); i++)
        cout << cycle[i] << (i+1 < (int)cycle.size() ? " → " : "\n");
}

int main() {
    // Graph WITH cycle: 0→1→2→0
    cout << "=== DIRECTED GRAPH WITH CYCLE ===\n";
    int V1 = 4;
    vector<vector<int>> adj1(V1);
    adj1[0]={1}; adj1[1]={2}; adj1[2]={0,3};
    cout << "DFS method: " << (hasCycleDirected(adj1,V1) ? "CYCLE" : "No cycle") << "\n";
    cout << "Kahn method: " << (hasCycleKahn(adj1,V1) ? "CYCLE" : "No cycle") << "\n";
    printCycle(adj1, V1);

    // DAG (no cycle): 0→1→3, 0→2→3
    cout << "\n=== DIRECTED ACYCLIC GRAPH ===\n";
    int V2 = 4;
    vector<vector<int>> adj2(V2);
    adj2[0]={1,2}; adj2[1]={3}; adj2[2]={3};
    cout << "DFS method: " << (hasCycleDirected(adj2,V2) ? "CYCLE" : "No cycle") << "\n";
    cout << "Kahn method: " << (hasCycleKahn(adj2,V2) ? "CYCLE" : "No cycle") << "\n";
    printCycle(adj2, V2);

    return 0;
}

/*
 * EXAM TIPS:
 * 1. Directed cycle: use 3-color DFS. GRAY neighbor = back edge = cycle.
 * 2. Undirected cycle: use parent-tracking DFS or Union-Find (different!).
 * 3. Kahn's algo gives cycle detection for free (processed < V).
 * 4. A DAG (no cycle) always has a topological ordering.
 */
