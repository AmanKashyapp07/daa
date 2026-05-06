/*
 * ============================================================================
 *  FLOYD-WARSHALL ALGORITHM (All-Pairs Shortest Path)
 * ============================================================================
 *  LOGIC:
 *  - Dynamic Programming algorithm.
 *  - Finds the shortest paths between ALL pairs of vertices.
 *  - Works with negative weight edges, but NOT negative weight cycles.
 *  - Can be used to detect negative weight cycles.
 *
 *  ALGORITHM:
 *  - Uses an adjacency matrix `dist[V][V]`.
 *  - Initializes `dist[i][j]` = weight of edge (i, j), `dist[i][i] = 0`, and
 *    `INF` if there is no edge.
 *  - Triple nested loop: Try to include vertex `k` as an intermediate
 *    vertex between `i` and `j`.
 *  - Update rule: dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])
 *
 *  TIME COMPLEXITY:  O(V^3)
 *  SPACE COMPLEXITY: O(V^2) for the distance matrix.
 *
 *  EXAM TIP:
 *  1. Negative Cycle Detection: After running Floyd-Warshall, check the
 *     diagonal `dist[i][i]`. If any `dist[i][i] < 0`, a negative cycle exists.
 *  2. For sparse graphs, running Dijkstra V times might be faster 
 *     (O(V * E log V)) than Floyd-Warshall, provided there are no negative edges.
 *  3. Pay attention to the loop order! It must be K, then I, then J.
 *     K represents the set of allowed intermediate vertices {0, 1, ..., k}.
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

#define INF 1e9 // Using a large value instead of INT_MAX to prevent overflow during addition

// ─────────────────────────────────────────────────────────────────────────────
//  FLOYD-WARSHALL ALGORITHM IMPLEMENTATION
// ─────────────────────────────────────────────────────────────────────────────
void floydWarshall(int V, vector<vector<int>>& graph) {
    // Create the distance matrix, initialize with the input graph.
    vector<vector<int>> dist = graph;

    // Core DP logic
    // k = intermediate vertex
    for (int k = 0; k < V; ++k) {
        // i = source vertex
        for (int i = 0; i < V; ++i) {
            // j = destination vertex
            for (int j = 0; j < V; ++j) {
                // If vertex k is reachable from i, and j is reachable from k
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    if (dist[i][k] + dist[k][j] < dist[i][j]) { // Relaxation step
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }
    }

    // Detect Negative Cycle
    // If distance from any vertex to itself is negative, there's a negative cycle, because it means we can keep going around that cycle to reduce the path cost indefinitely.
    bool hasNegativeCycle = false;
    for (int i = 0; i < V; ++i) {
        if (dist[i][i] < 0) {
            hasNegativeCycle = true;
            break;
        }
    }

    if (hasNegativeCycle) {
        cout << "GRAPH CONTAINS A NEGATIVE WEIGHT CYCLE!\n";
        return;
    }

    // Print the shortest distance matrix
    cout << "All-Pairs Shortest Paths Matrix:\n";
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (dist[i][j] == INF)
                cout << "INF\t";
            else
                cout << dist[i][j] << "\t";
        }
        cout << "\n";
    }
}

// ─────────────────────────────────────────────────────────────────────────────
//  DRIVER
// ─────────────────────────────────────────────────────────────────────────────
int main() {
    /*
     * Example Graph:
     *      10
     * (0)------->(3)
     *  |         /|\
     * 5|          |
     *  |          | 1
     * \|/         |
     * (1)------->(2)
     *      3
     */
    int V = 4;
    vector<vector<int>> graph(V, vector<int>(V, INF));
    
    // Set diagonal to 0
    for(int i=0; i<V; ++i) graph[i][i] = 0;

    // Add edges
    graph[0][1] = 5;
    graph[0][3] = 10;
    graph[1][2] = 3;
    graph[2][3] = 1;

    cout << "=== FLOYD-WARSHALL ===\n";
    floydWarshall(V, graph);

    return 0;
}
