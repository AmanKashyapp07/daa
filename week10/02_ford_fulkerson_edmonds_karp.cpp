/*
 * ============================================================================
 *  MAXIMUM FLOW (Ford-Fulkerson & Edmonds-Karp)
 * ============================================================================
 *  CONCEPTS:
 *  - A Flow Network is a directed graph where each edge has a capacity.
 *  - Source (s): Produces flow. Sink (t): Consumes flow.
 *  - Constraints:
 *    1. Capacity Constraint: Flow on an edge cannot exceed its capacity.
 *    2. Flow Conservation: For all vertices (except s and t), incoming flow
 *       must equal outgoing flow.
 *
 *  FORD-FULKERSON METHOD:
 *  - Maintain a "Residual Graph" which shows remaining capacities.
 *  - While there is an "Augmenting Path" (a path from s to t in the residual 
 *    graph with capacity > 0):
 *    1. Find the bottleneck capacity (min capacity) along the path.
 *    2. Add this bottleneck capacity to the total flow.
 *    3. Update the residual graph: subtract flow from forward edges, add 
 *       flow to backward edges (allowing the algorithm to "undo" flow).
 *  - Time: O(E * max_flow) - depends on max flow value, can be slow.
 *
 *  EDMONDS-KARP ALGORITHM (Implementation of Ford-Fulkerson):
 *  - Uses BFS to find the augmenting path (shortest path in terms of number 
 *    of edges).
 *  - Guarantees termination and polynomial time complexity.
 *  - Time: O(V * E^2)
 *
 *  EXAM TIP:
 *  - Edmonds-Karp is just Ford-Fulkerson using BFS. 
 *  - Max-Flow Min-Cut Theorem: The maximum flow from s to t is equal to the 
 *    capacity of the minimum cut separating s and t.
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
//  EDMONDS-KARP ALGORITHM
// ─────────────────────────────────────────────────────────────────────────────
// BFS to find an augmenting path. Returns true if a path from s to t exists.
bool bfs(int s, int t, int V, const vector<vector<int>>& residualGraph, vector<int>& parent) {
    vector<bool> visited(V, false);
    queue<int> q;

    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < V; ++v) {
            // If v is not visited and there is residual capacity
            if (!visited[v] && residualGraph[u][v] > 0) {
                if (v == t) {
                    parent[v] = u;
                    return true;
                }
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
    return false;
}

// Returns the maximum flow from s to t in the given graph
int edmondsKarp(int s, int t, int V, vector<vector<int>>& graph) {
    int u, v;

    // Create a residual graph initialized identically to the original graph
    vector<vector<int>> residualGraph = graph;

    // Array to store the augmenting path found by BFS
    vector<int> parent(V);

    int max_flow = 0;

    // Augment the flow while there is a path from source to sink
    while (bfs(s, t, V, residualGraph, parent)) {
        // Find the bottleneck capacity of the augmenting path
        int path_flow = INT_MAX;
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            path_flow = min(path_flow, residualGraph[u][v]);
        }

        // Update residual capacities of the edges and reverse edges along the path
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            residualGraph[u][v] -= path_flow; // Forward edge
            residualGraph[v][u] += path_flow; // Backward edge
        }

        // Add path flow to overall flow
        max_flow += path_flow;
    }

    return max_flow;
}

// ─────────────────────────────────────────────────────────────────────────────
//  DRIVER
// ─────────────────────────────────────────────────────────────────────────────
int main() {
    /*
     * Example Flow Network:
     *      (1) ---12---> (3)
     *     / |             | \
     *  16/  |             |  \20
     *   /   |10           |9  \
     * (0)   |             |   (5) Sink
     *   \   v             v   /
     *  13\  (2) ---14---> (4)/4
     *     \ /             /
     *      4             /
     *       \-----------/
     */
    int V = 6;
    vector<vector<int>> graph(V, vector<int>(V, 0));

    // Capacity edges (u, v)
    graph[0][1] = 16;
    graph[0][2] = 13;
    graph[1][2] = 10;
    graph[1][3] = 12;
    graph[2][1] = 4;
    graph[2][4] = 14;
    graph[3][2] = 9;
    graph[3][5] = 20;
    graph[4][3] = 7;
    graph[4][5] = 4;

    cout << "=== MAXIMUM FLOW (Edmonds-Karp) ===\n";
    cout << "The maximum possible flow is " << edmondsKarp(0, 5, V, graph) << "\n";

    return 0;
}
