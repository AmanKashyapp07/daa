/*
 * ============================================================================
 *  TOPOLOGICAL SORTING
 * ============================================================================
 *  DEFINITION: A linear ordering of vertices in a DAG (Directed Acyclic Graph)
 *  such that for every directed edge u→v, u comes before v in the ordering.
 *
 *  PREREQUISITE: Graph must be a DAG. If cycle exists, no topological order.
 *
 *  TWO METHODS:
 *  1. DFS-based (Cormen/CLRS): Run DFS, push to stack on finish → reverse, this cannot be used for cycle detection.
 *  2. Kahn's Algorithm (BFS): Repeatedly remove vertices with in-degree 0, this can detect cycles.
 *
 *  TIME: O(V + E) for both methods.
 *  SPACE: O(V)
 *
 *  APPLICATIONS:
 *  - Course prerequisite scheduling
 *  - Build system dependency resolution (Makefile)
 *  - Task scheduling in DAGs
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
//  1. TOPOLOGICAL SORT USING DFS (CLRS Method)
// ─────────────────────────────────────────────────────────────────────────────
// Logic: Run DFS. When a vertex finishes (all descendants explored), push it
// onto a stack. The stack (reversed) gives topological order
// WHY: Vertex finishes after all its dependents → it appears before them.
//
// Time: O(V + E) | Space: O(V)
void dfsTopo(int u, vector<vector<int>>& adj, vector<bool>& visited,
             stack<int>& topoStack) {
    visited[u] = true;
    for (int v : adj[u]) {
        if (!visited[v]) {
            dfsTopo(v, adj, visited, topoStack);
        }
    }
    // Push AFTER all neighbors are processed (post-order)
    topoStack.push(u);
}

vector<int> topologicalSortDFS(vector<vector<int>>& adj, int V) {
    vector<bool> visited(V, false);
    stack<int> topoStack;

    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            dfsTopo(i, adj, visited, topoStack);
        }
    }

    vector<int> result;
    while (!topoStack.empty()) {
        result.push_back(topoStack.top());
        topoStack.pop();
    }
    return result;
}

// ─────────────────────────────────────────────────────────────────────────────
//  2. TOPOLOGICAL SORT USING KAHN'S ALGORITHM (BFS-based)
// ─────────────────────────────────────────────────────────────────────────────
// Logic:
// 1. Compute in-degree of all vertices.
// 2. Add all vertices with in-degree 0 to queue (no prerequisites).
// 3. While queue not empty:
//    a. Dequeue vertex u, add to result.
//    b. For each neighbor v of u: decrement in-degree[v].
//       If in-degree[v] becomes 0, enqueue v.
// 4. If result size < V → cycle exists (not a DAG).
//
// Time: O(V + E) | Space: O(V)
vector<int> topologicalSortKahn(vector<vector<int>>& adj, int V) {
    vector<int> inDegree(V, 0);

    // Step 1: Compute in-degrees
    for (int u = 0; u < V; u++) {
        for (int v : adj[u]) {
            inDegree[v]++;
        }
    }

    // Step 2: Enqueue all vertices with in-degree 0
    queue<int> q;
    for (int i = 0; i < V; i++) {
        if (inDegree[i] == 0) {
            q.push(i);
        }
    }

    vector<int> result;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        result.push_back(u);

        // Step 3: Reduce in-degree of neighbors
        for (int v : adj[u]) {
            inDegree[v]--;
            if (inDegree[v] == 0) {
                q.push(v);
            }
        }
    }

    // Step 4: Check for cycle
    if ((int)result.size() != V) {
        cout << "CYCLE DETECTED! Graph is not a DAG.\n";
        return {};
    }
    return result;
}

int main() {
    /*
     * DAG Example (course prerequisites):
     *
     *   5 → 0 ← 4
     *   5 → 2    4 → 1
     *        ↓     ↓
     *        3 ← 1
     *
     * Vertices: 0=Math, 1=Physics, 2=CS101, 3=CS201, 4=English, 5=Intro
     * One valid topological order: 4, 5, 0, 2, 1, 3
     * Another valid order:         5, 4, 2, 0, 1, 3
     */
    int V = 6;
    vector<vector<int>> adj(V);
    adj[5].push_back(0);
    adj[5].push_back(2);
    adj[4].push_back(0);
    adj[4].push_back(1);
    adj[2].push_back(3);
    adj[1].push_back(3);

    cout << "=== TOPOLOGICAL SORT (DFS-based) ===\n";
    vector<int> order1 = topologicalSortDFS(adj, V);
    for (int v : order1) cout << v << " ";
    cout << "\n";

    cout << "\n=== TOPOLOGICAL SORT (Kahn's BFS-based) ===\n";
    vector<int> order2 = topologicalSortKahn(adj, V);
    for (int v : order2) cout << v << " ";
    cout << "\n";

    // Test with a cyclic graph
    cout << "\n=== KAHN'S ON CYCLIC GRAPH ===\n";
    int V2 = 3;
    vector<vector<int>> cyclic(V2);
    cyclic[0].push_back(1);
    cyclic[1].push_back(2);
    cyclic[2].push_back(0); // Creates cycle
    topologicalSortKahn(cyclic, V2);

    return 0;
}

/*
 * ============================================================================
 *  COMPARISON
 * ============================================================================
 *  Method           | Time     | Space | Cycle Detection | Notes
 *  -----------------|----------|-------|-----------------|------------------
 *  DFS-based        | O(V + E) | O(V)  | No (need extra) | Uses finish times
 *  Kahn's (BFS)     | O(V + E) | O(V)  | Yes (built-in)  | Uses in-degree
 *
 *  EXAM TIPS:
 *  1. Topological sort exists ONLY for DAGs.
 *  2. Kahn's naturally detects cycles (result.size() < V).
 *  3. Multiple valid orderings may exist.
 *  4. DFS-based: vertex with latest finish time comes first.
 *  5. Topological sort is used in: task scheduling, dependency resolution,
 *     shortest path in DAG, course prerequisite ordering.
 * ============================================================================
 */
