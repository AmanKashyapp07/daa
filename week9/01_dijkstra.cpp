/*
 * ============================================================================
 *  DIJKSTRA'S ALGORITHM (Single-Source Shortest Path)
 * ============================================================================
 *  LOGIC:
 *  - Greedy algorithm. Finds the shortest path from a single source to all
 *    other vertices in a weighted graph.
 *  - Maintains a set of vertices whose shortest distance from source is known.
 *  - At each step, it picks the vertex with the minimum distance that hasn't
 *    been processed yet (using a Priority Queue / Min-Heap).
 *  - It then "relaxes" all outgoing edges of this vertex:
 *    If dist[u] + weight(u, v) < dist[v], update dist[v] = dist[u] + weight
 *
 *  IMPORTANT LIMITATION:
 *  - DOES NOT work with negative weight edges. The greedy choice assumes
 *    once a vertex is extracted from the PQ, its shortest path is final.
 *    Negative edges can violate this assumption.
 *
 *  TIME COMPLEXITY:  O((V + E) log V) with Min-Heap (priority_queue).
 *                    (For dense graphs, an O(V^2) implementation without PQ
 *                     might be faster, but PQ is standard).
 *  SPACE COMPLEXITY: O(V) for the distance array and Priority Queue.
 *  Interesting Fact : Dijkstra is used in Google Maps, GPS navigation, and network routing protocols like OSPF, but google maps and GPS navigation use a more complex version of Dijkstra's algorithm called A* search algorithm which uses heuristics to speed up the search, which means
 *  it estimates the distance to the target and uses that to prioritize which vertices to explore, making it faster than Dijkstra in many cases.
 *  EXAM TIP:
 *  1. If graph is unweighted, use BFS (O(V+E)) instead of Dijkstra.
 *  2. If graph is a DAG, use Topological Sort + Relaxation (O(V+E)).
 *  3. In C++, priority_queue is max-heap by default. We use
 *     priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>>
 *     to make it a min-heap.
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
//  DIJKSTRA'S ALGORITHM IMPLEMENTATION
// ─────────────────────────────────────────────────────────────────────────────
void dijkstra(int source, int V, const vector<vector<pair<int, int>>>& adj) {
    // Distance array, initialized to infinity
    vector<int> dist(V, INT_MAX);
    // Parent array for path reconstruction
    vector<int> parent(V, -1);
    
    // Min-heap to store {distance, vertex}
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    // Start with the source vertex
    dist[source] = 0;
    pq.push({0, source});

    while (!pq.empty()) {
        // Extract the vertex with the minimum distance
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        // Optimization: If we find a longer distance in the queue, skip it.
        // This happens because we might push the same vertex multiple times
        // with different distances instead of updating it (std::priority_queue
        // doesn't support decrease-key natively).
        if (d > dist[u]) continue;

        // Relax all adjacent edges
        for (auto edge : adj[u]) {
            int v = edge.first;
            int weight = edge.second;

            // Relaxation step
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) { // relaxing edge u→v
                dist[v] = dist[u] + weight;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
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

    // Example of Path Reconstruction (Path from source to vertex 4)
    int target = 4;
    if (target < V && dist[target] != INT_MAX) {
        cout << "\nShortest path to vertex " << target << ": ";
        vector<int> path;
        for (int v = target; v != -1; v = parent[v]) {
            path.push_back(v);
        }
        reverse(path.begin(), path.end());
        for (size_t i = 0; i < path.size(); ++i) {
            cout << path[i] << (i == path.size() - 1 ? "" : " -> ");
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
     * (0) ---10---> (1)
     *  |             | \
     *  5             1  2
     *  |             |   \
     *  v             v    v
     * (2) ---3----> (3)-4-(4)
     *  |             ^
     *  9             2
     *  |             |
     *  +----(5)------+
     */
    int V = 6;
    vector<vector<pair<int, int>>> adj(V);

    // Adding edges: u -> {v, weight}
    auto addEdge = [&](int u, int v, int w) {
        adj[u].push_back({v, w});
        // Uncomment the below line if graph is undirected
        // adj[v].push_back({u, w}); 
    };

    addEdge(0, 1, 10);
    addEdge(0, 2, 5);
    addEdge(1, 3, 1);
    addEdge(1, 4, 2);
    addEdge(2, 3, 3);
    addEdge(2, 5, 9);
    addEdge(5, 3, 2);
    addEdge(3, 4, 4);

    cout << "=== DIJKSTRA'S ALGORITHM ===\n";
    dijkstra(0, V, adj);

    return 0;
}
