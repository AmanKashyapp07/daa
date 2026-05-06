/*
 * ============================================================================
 *  FLOW-BASED APPLICATIONS & MIN-CUT
 * ============================================================================
 *  CONCEPTS:
 *  1. S-T MINIMUM CUT:
 *     - An s-t cut partitions the vertices into two sets S and T such that
 *       s ∈ S and t ∈ T.
 *     - The capacity of the cut is the sum of capacities of edges from S to T.
 *     - Max-Flow Min-Cut Theorem: Max flow value = Min cut capacity.
 *
 *  HOW TO FIND THE EDGES IN THE MIN-CUT:
 *  - Run Ford-Fulkerson / Edmonds-Karp to get the final residual graph.
 *  - Perform a BFS/DFS from the source 's' strictly on edges with POSITIVE 
 *    residual capacity.
 *  - All reachable vertices belong to set S. All unreachable vertices belong 
 *    to set T.
 *  - The Min-Cut edges are the original edges crossing from S to T.
 *
 *  2. MULTI-SOURCE MULTI-SINK MAX FLOW:
 *     - If a network has multiple sources and multiple sinks.
 *     - TRICK: Add a "Super Source" connected to all original sources with 
 *       infinite capacity. Add a "Super Sink" connected to all original sinks 
 *       from them with infinite capacity.
 *     - Compute standard Max Flow from Super Source to Super Sink.
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

// BFS for finding augmenting paths
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

// DFS to find all reachable vertices from source in residual graph
void dfsReachable(int u, int V, const vector<vector<int>>& residualGraph, vector<bool>& visited) {
    visited[u] = true;
    for (int v = 0; v < V; ++v) {
        if (!visited[v] && residualGraph[u][v] > 0) {
            dfsReachable(v, V, residualGraph, visited);
        }
    }
}

// ─────────────────────────────────────────────────────────────────────────────
//  MIN-CUT IMPLEMENTATION
// ─────────────────────────────────────────────────────────────────────────────
void minCut(int s, int t, int V, const vector<vector<int>>& graph) {
    vector<vector<int>> residualGraph = graph;
    vector<int> parent(V);

    // 1. Run Edmonds-Karp to saturate the flow network
    while (bfs(s, t, V, residualGraph, parent)) {
        int path_flow = INT_MAX;
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            path_flow = min(path_flow, residualGraph[u][v]);
        }
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            residualGraph[u][v] -= path_flow;
            residualGraph[v][u] += path_flow;
        }
    }

    // 2. Find reachable vertices from s in the final residual graph
    vector<bool> visited(V, false);
    dfsReachable(s, V, residualGraph, visited);

    // 3. Print the edges that form the min cut
    // Edges (u,v) where u is reachable (in S) and v is not reachable (in T)
    // AND the edge existed in the original graph
    cout << "Min-Cut edges separating source " << s << " and sink " << t << ":\n";
    int min_cut_capacity = 0;
    for (int u = 0; u < V; ++u) {
        for (int v = 0; v < V; ++v) {
            if (visited[u] && !visited[v] && graph[u][v] > 0) {
                cout << u << " -- " << v << " (Capacity: " << graph[u][v] << ")\n";
                min_cut_capacity += graph[u][v];
            }
        }
    }
    cout << "Total Min-Cut Capacity (which equals Max Flow): " << min_cut_capacity << "\n";
}

// ─────────────────────────────────────────────────────────────────────────────
//  DRIVER
// ─────────────────────────────────────────────────────────────────────────────
int main() {
    /*
     * Example Graph for Min-Cut:
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

    cout << "=== MINIMUM CUT FINDER ===\n";
    minCut(0, 5, V, graph);

    return 0;
}
