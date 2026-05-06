/*
 * ============================================================================
 *  SHORTEST PATH IMPLEMENTATIONS & LABORATORY APPLICATIONS
 * ============================================================================
 *  This file covers specific problem variations often asked in laboratories:
 *
 *  1. MULTI-SOURCE SHORTEST PATH:
 *     - Given multiple sources, find the shortest path from ANY source to 
 *       all other nodes. 
 *     - TRICK: Add a "Dummy Super Source" (Vertex S*), add a 0-weight edge
 *       from S* to all original sources. Run Dijkstra/BFS from S*.
 *
 *  2. SHORTEST PATH WITH AT MOST K EDGES:
 *     - Find the shortest path from U to V using at most K edges.
 *     - TRICK: Modify Bellman-Ford to only run K iterations. Use a temporary
 *       distance array each iteration to prevent cascading updates within 
 *       the same pass.
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
//  1. MULTI-SOURCE SHORTEST PATH (Using Super Source trick)
// ─────────────────────────────────────────────────────────────────────────────
// E.g., multiple fire stations, find shortest time for a firetruck to reach
// every building, we cannot use multi source BFS directly because of varying edge weights, so we use Dijkstra with a super source.
void multiSourceShortestPath(int V, const vector<vector<pair<int, int>>>& adj, const vector<int>& sources) {
    vector<int> dist(V, INT_MAX);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    // Push all sources simultaneously with distance 0
    // This is mathematically equivalent to the "Super Source" trick
    for (int src : sources) {
        dist[src] = 0;
        pq.push({0, src});
    }

    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d > dist[u]) continue;

        for (auto edge : adj[u]) {
            int v = edge.first;
            int weight = edge.second;

            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    cout << "Shortest distance from nearest source to each vertex:\n";
    for (int i = 0; i < V; ++i) {
        cout << "Vertex " << i << ": " << (dist[i] == INT_MAX ? -1 : dist[i]) << "\n";
    }
}

// ─────────────────────────────────────────────────────────────────────────────
//  2. SHORTEST PATH WITH AT MOST K EDGES (Modified Bellman-Ford)
// ─────────────────────────────────────────────────────────────────────────────
// E.g., Cheapest flight from A to B with at most K stops (K+1 edges)
// this can also be solved using a modified Dijkstra's algorithm with a state that includes the number of edges used, but here we demonstrate the Bellman-Ford approach which is more straightforward for this problem.
struct Edge { int u, v, weight; };

void shortestPathAtMostKEdges(int V, int source, int dest, int K, const vector<Edge>& edges) {
    // Distance array initialized to INF
    vector<int> dist(V, INT_MAX);
    dist[source] = 0;

    // We can use up to K stops => K + 1 edges
    for (int i = 0; i <= K; ++i) {
        // Copy dist array because we want to use distances from the previous iteration to prevent cascading updates within the same pass.
        // cascading updates mean if we update dist[v] in the middle of the loop, and then use that updated value to relax another edge in the same iteration, it would be incorrect because it would allow paths with more than K edges to influence the result.
        vector<int> temp_dist = dist;
        
        for (const auto& edge : edges) {
            int u = edge.u;
            int v = edge.v;
            int weight = edge.weight;

            // Notice we use dist[u] (from previous iteration) to update temp_dist[v]
            if (dist[u] != INT_MAX && dist[u] + weight < temp_dist[v]) {
                temp_dist[v] = dist[u] + weight;
            }
        }
        dist = temp_dist;
    }

    if (dist[dest] == INT_MAX) {
        cout << "No path from " << source << " to " << dest << " with at most " << K << " stops.\n";
    } else {
        cout << "Shortest path from " << source << " to " << dest << " with at most " << K << " stops: " << dist[dest] << "\n";
    }
}

void shortestPathAtMostKEdgesDijkstra(int V, int source, int dest, int K, const vector<vector<pair<int, int>>>& adj) {
    // Priority queue holds (cost, vertex, edges_used)
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq;
    pq.push({0, source, 0}); // (cost=0, vertex=source, edges_used=0)

    while (!pq.empty()) {
        auto [cost, u, edges_used] = pq.top(); // sorted by lowest cost first, then by edges used
        pq.pop();

        if (u == dest) {
            cout << "Shortest path from " << source << " to " << dest << " with at most " << K << " stops: " << cost << "\n";
            return;
        }

        if (edges_used > K) continue; // Exceeded stop limit

        for (auto edge : adj[u]) {
            int v = edge.first;
            int weight = edge.second;
            pq.push({cost + weight, v, edges_used + 1});
        }
    }
}

// ─────────────────────────────────────────────────────────────────────────────
//  DRIVER
// ─────────────────────────────────────────────────────────────────────────────
int main() {
    cout << "=== 1. MULTI-SOURCE SHORTEST PATH ===\n";
    int V1 = 5;
    vector<vector<pair<int, int>>> adj(V1);
    adj[0].push_back({2, 1});
    adj[1].push_back({2, 3});
    adj[2].push_back({3, 2});
    adj[2].push_back({4, 5});
    adj[3].push_back({4, 1});
    
    // Nodes 0 and 1 are sources (e.g., Fire stations)
    vector<int> sources = {0, 1};
    multiSourceShortestPath(V1, adj, sources);

    cout << "\n=== 2. SHORTEST PATH WITH AT MOST K STOPS ===\n";
    int V2 = 3;
    vector<Edge> edges = {
        {0, 1, 100},
        {1, 2, 100},
        {0, 2, 500}
    };
    int src = 0, dst = 2, K = 0; // 0 stops = 1 edge
    cout << "Query: K=" << K << " stops.\n";
    shortestPathAtMostKEdges(V2, src, dst, K, edges);

    K = 1; // 1 stop = 2 edges
    cout << "Query: K=" << K << " stops.\n";
    shortestPathAtMostKEdges(V2, src, dst, K, edges);

    return 0;
}
