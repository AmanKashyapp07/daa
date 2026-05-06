/*
 * ============================================================================
 *  BREADTH-FIRST SEARCH (BFS)
 * ============================================================================
 *  LOGIC:
 *  - BFS explores a graph level by level, starting from a source vertex.
 *  - Uses a QUEUE (FIFO) to process vertices in order of their distance
 *    from the source.
 *  - Guarantees shortest path in UNWEIGHTED graphs.
 *
 *  ALGORITHM:
 *  1. Mark source as visited, enqueue it.
 *  2. While queue is not empty:
 *     a. Dequeue vertex u.
 *     b. For each unvisited neighbor v of u:
 *        - Mark v as visited
 *        - Record distance[v] = distance[u] + 1
 *        - Record parent[v] = u  (for path reconstruction)
 *        - Enqueue v
 *
 *  TIME COMPLEXITY:  O(V + E)  — every vertex and edge is visited once.
 *  SPACE COMPLEXITY: O(V)      — for visited array, queue, distance array.
 *
 *  KEY PROPERTIES:
 *  - BFS tree gives shortest paths from source in unweighted graphs.
 *  - BFS classifies edges as: Tree edges and Cross edges (no back edges
 *    in undirected BFS means no cycle detection via BFS directly for directed).
 *  - Used for: shortest path (unweighted), level-order traversal, bipartite
 *    check, connected components.
 *
 *  EXAM TIP: BFS finds shortest path in unweighted graphs. For weighted
 *  graphs, use Dijkstra's algorithm instead.
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
//  1. BASIC BFS — Level-by-level traversal
// ─────────────────────────────────────────────────────────────────────────────
void bfs(int source, vector<vector<int>>& adj, int V) {
    vector<bool> visited(V, false);
    queue<int> q;

    visited[source] = true;
    q.push(source);

    cout << "BFS traversal from vertex " << source << ": ";
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        cout << u << " ";

        // Explore all unvisited neighbors
        for (int v : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }
    cout << "\n";
}

// ─────────────────────────────────────────────────────────────────────────────
//  2. BFS WITH SHORTEST DISTANCE (Unweighted Graph)
// ─────────────────────────────────────────────────────────────────────────────
vector<int> bfsShortestDistance(int source, vector<vector<int>>& adj, int V) {
    vector<int> dist(V, -1);  // -1 means unreachable
    queue<int> q;

    dist[source] = 0;
    q.push(source);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : adj[u]) {
            if (dist[v] == -1) {        // Not yet visited
                dist[v] = dist[u] + 1;  // Distance = parent's distance + 1
                q.push(v);
            }
        }
    }
    return dist;
}

// ─────────────────────────────────────────────────────────────────────────────
//  3. BFS WITH PATH RECONSTRUCTION
// ─────────────────────────────────────────────────────────────────────────────
vector<int> bfsShortestPath(int source, int dest, vector<vector<int>>& adj, int V) {
    vector<int> parent(V, -1);
    vector<bool> visited(V, false);
    queue<int> q;

    visited[source] = true;
    q.push(source);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        if (u == dest) break; // Early termination

        for (int v : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                parent[v] = u;
                q.push(v);
            }
        }
    }

    // Reconstruct path by backtracking from destination to source
    vector<int> path;
    if (!visited[dest]) return path; // No path exists

    for (int v = dest; v != -1; v = parent[v]) {
        path.push_back(v);
    }
    reverse(path.begin(), path.end());
    return path;
}

// ─────────────────────────────────────────────────────────────────────────────
//  4. BFS FOR DISCONNECTED GRAPH (visit all components)
// ─────────────────────────────────────────────────────────────────────────────
void bfsDisconnected(vector<vector<int>>& adj, int V) {
    vector<bool> visited(V, false);

    int componentCount = 0;
    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            componentCount++;
            cout << "Component " << componentCount << ": ";

            queue<int> q;
            visited[i] = true;
            q.push(i);

            while (!q.empty()) {
                int u = q.front();
                q.pop();
                cout << u << " ";

                for (int v : adj[u]) {
                    if (!visited[v]) {
                        visited[v] = true;
                        q.push(v);
                    }
                }
            }
            cout << "\n";
        }
    }
    cout << "Total connected components: " << componentCount << "\n";
}

int main() {
    /*
     * Graph (undirected):
     *
     *     0 --- 1 --- 4
     *     |     |
     *     2 --- 3
     *
     *     5 --- 6    (separate component)
     */
    int V = 7;
    vector<vector<int>> adj(V);

    // Component 1
    auto addEdge = [&](int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    };
    addEdge(0, 1);
    addEdge(0, 2);
    addEdge(1, 3);
    addEdge(1, 4);
    addEdge(2, 3);

    // Component 2
    addEdge(5, 6);

    // 1. Basic BFS
    cout << "=== BASIC BFS ===\n";
    bfs(0, adj, V);

    // 2. Shortest distances
    cout << "\n=== BFS SHORTEST DISTANCES (from vertex 0) ===\n";
    vector<int> dist = bfsShortestDistance(0, adj, V);
    for (int i = 0; i < V; i++) {
        cout << "dist[" << i << "] = " << dist[i] << "\n";
    }

    // 3. Shortest path reconstruction
    cout << "\n=== SHORTEST PATH (0 → 4) ===\n";
    vector<int> path = bfsShortestPath(0, 4, adj, V);
    cout << "Path: ";
    for (int i = 0; i < path.size(); i++) {
        cout << path[i] << (i + 1 < path.size() ? " → " : "\n");
    }

    // 4. Disconnected graph BFS
    cout << "\n=== BFS ON DISCONNECTED GRAPH ===\n";
    bfsDisconnected(adj, V);

    return 0;
}

/*
 * ============================================================================
 *  SUMMARY
 * ============================================================================
 *  Algorithm       | Time     | Space | Key Use
 *  ----------------|----------|-------|-----------------------------------
 *  Basic BFS       | O(V + E) | O(V)  | Level-order traversal
 *  BFS Distance    | O(V + E) | O(V)  | Shortest path (unweighted)
 *  BFS Path        | O(V + E) | O(V)  | Path reconstruction
 *  BFS Disconnected| O(V + E) | O(V)  | Connected components count
 *
 *  KEY EXAM POINTS:
 *  1. BFS uses a QUEUE → FIFO → processes level by level.
 *  2. BFS gives shortest path in UNWEIGHTED graphs only.
 *  3. BFS time is O(V + E) because each vertex is enqueued at most once
 *     and each edge is examined at most twice (once from each endpoint).
 *  4. BFS can detect connected components in undirected graphs.
 * ============================================================================
 */
