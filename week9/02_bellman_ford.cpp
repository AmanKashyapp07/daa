/*
 * ============================================================================
 *  BELLMAN-FORD ALGORITHM (Single-Source Shortest Path)
 * ============================================================================
 *  LOGIC:
 *  - Dynamic Programming approach.
 *  - Finds shortest path from a single source to all vertices.
 *  - Works with NEGATIVE weight edges (unlike Dijkstra).
 *  - Also detects NEGATIVE WEIGHT CYCLES.
 *
 *  ALGORITHM:
 *  1. Initialize dist[source] = 0, all other dist = INF.
 *  2. Relax ALL edges (V - 1) times.
 *     - Why V - 1? Because the longest possible simple path in a graph
 *       with V vertices has exactly V - 1 edges.
 *  3. Do one more pass over all edges. If any distance can still be
 *     relaxed, it means there is a NEGATIVE WEIGHT CYCLE.
 *
 *  TIME COMPLEXITY:  O(V * E)
 *  SPACE COMPLEXITY: O(V)
 *
 *  EXAM TIP:
 *  - Bellman-Ford is slower than Dijkstra. Only use it when:
 *    a) The graph has negative weights.
 *    b) You need to check for negative cycles.
 *  - In network routing, the Routing Information Protocol (RIP) uses a
 *    distributed version of Bellman-Ford.
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

// Structure to represent a directed edge
struct Edge {
    int u, v, weight;
};

// ─────────────────────────────────────────────────────────────────────────────
//  BELLMAN-FORD ALGORITHM IMPLEMENTATION
// ─────────────────────────────────────────────────────────────────────────────
void bellmanFord(int source, int V, int E, const vector<Edge>& edges) {
    // Step 1: Initialize distances
    vector<int> dist(V, INT_MAX);
    vector<int> parent(V, -1);
    dist[source] = 0;

    // Step 2: Relax all edges (V - 1) times, because the longest path can have at most V-1 edges, so, we need to repeat the process V-1 times to ensure all shortest paths are found.
    for (int i = 1; i <= V - 1; ++i) {
        bool updated = false; // Optimization: Stop early if no distances change
        for (const auto& edge : edges) {
            int u = edge.u;
            int v = edge.v;
            int weight = edge.weight;

            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
                updated = true;
            }
        }
        if (!updated) break; // No changes in this pass, shortest paths found
    }

    // Step 3: Check for negative-weight cycles
    // If we can still relax an edge, a negative cycle exists.
    bool negativeCycle = false;
    for (const auto& edge : edges) {
        int u = edge.u;
        int v = edge.v;
        int weight = edge.weight;

        if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
            negativeCycle = true;
            break;
        }
    }

    if (negativeCycle) {
        cout << "GRAPH CONTAINS A NEGATIVE WEIGHT CYCLE!\n";
        cout << "Shortest paths are not well-defined.\n";
        return;
    }

    // Print shortest distances
    cout << "Shortest distances from source " << source << ":\n";
    for (int i = 0; i < V; ++i) {
        if (dist[i] == INT_MAX) {
            cout << "Vertex " << i << ": INF\n";
        } else {
            cout << "Vertex " << i << ": " << dist[i] << "\n";
        }
    }
}

// ─────────────────────────────────────────────────────────────────────────────
//  DRIVER
// ─────────────────────────────────────────────────────────────────────────────
int main() {
    // Example 1: Graph WITHOUT negative cycle
    cout << "=== BELLMAN-FORD (No Negative Cycle) ===\n";
    int V1 = 5, E1 = 8;
    vector<Edge> edges1 = {
        {0, 1, -1}, {0, 2, 4},
        {1, 2, 3}, {1, 3, 2}, {1, 4, 2},
        {3, 2, 5}, {3, 1, 1}, {4, 3, -3}
    };
    bellmanFord(0, V1, E1, edges1);

    // Example 2: Graph WITH negative cycle
    // 0 -> 1 -> 2 -> 3 -> 1 (cycle weight: 2 - 5 + 1 = -2)
    cout << "\n=== BELLMAN-FORD (With Negative Cycle) ===\n";
    int V2 = 4, E2 = 4;
    vector<Edge> edges2 = {
        {0, 1, 1},
        {1, 2, 2},
        {2, 3, -5},
        {3, 1, 1}
    };
    bellmanFord(0, V2, E2, edges2);

    return 0;
}
