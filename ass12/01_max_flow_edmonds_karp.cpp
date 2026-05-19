/*
 * Problem A: Maximum Flow Problem - Edmonds-Karp Algorithm
 * Application: City Water Distribution Network
 *
 * Logic:
 * The Edmonds-Karp algorithm is an implementation of the Ford-Fulkerson method
 * that uses Breadth-First Search (BFS) for finding augmenting paths.
 * 1. Initialize max_flow to 0.
 * 2. While there is a path from source (S) to sink (T) in the residual graph
 *    (found using BFS):
 *    a. Find the minimum residual capacity along this path (this is the bottleneck or path flow).
 *    b. Add this path flow to the max_flow.
 *    c. Update the residual capacities of the edges and their reverse edges along the path.
 * 
 * Time Complexity Analysis:
 * - BFS takes O(V + E) time.
 * - In Edmonds-Karp, the length of the augmenting path strictly increases, and each edge
 *   can become critical at most V/2 times.
 * - Therefore, the maximum number of augmenting paths is bounded by O(V * E).
 * - Total Time Complexity: O(V * E^2), where V is the number of stations (N) and E is the number of pipelines (M).
 * 
 * Space Complexity: O(V + E) since we are using an adjacency list.
 */
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

// Structure to represent a directed edge
struct Edge {
    int v;
    int capacity;
    int flow;
    int rev_index; // Index of the reverse edge in the adjacency list
};

class MaxFlowNetwork {
private:
    int V;
    vector<vector<Edge>> adj;

    bool bfs(int s, int t, vector<int>& parent, vector<int>& parent_edge_idx) {
        vector<bool> visited(V, false);
        queue<int> q;

        q.push(s);
        visited[s] = true;
        parent[s] = -1;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int i = 0; i < adj[u].size(); i++) {
                Edge& e = adj[u][i];
                if (!visited[e.v] && e.capacity - e.flow > 0) {
                    parent[e.v] = u;
                    parent_edge_idx[e.v] = i;
                    
                    if (e.v == t) return true;
                    
                    visited[e.v] = true;
                    q.push(e.v);
                }
            }
        }
        return false;
    }

public:
    MaxFlowNetwork(int vertices) : V(vertices) {
        adj.resize(V);
    }

    void addEdge(int u, int v, int cap) {
        // Directed edge: u -> v
        adj[u].push_back({v, cap, 0, (int)adj[v].size()});
        // Reverse edge: v -> u with 0 capacity
        adj[v].push_back({u, 0, 0, (int)adj[u].size() - 1});
    }

    int edmondsKarp(int s, int t) {
        int max_flow = 0;
        vector<int> parent(V);
        vector<int> parent_edge_idx(V);

        while (bfs(s, t, parent, parent_edge_idx)) {
            int path_flow = INT_MAX;

            for (int v = t; v != s; v = parent[v]) {
                int u = parent[v];
                int idx = parent_edge_idx[v];
                path_flow = min(path_flow, adj[u][idx].capacity - adj[u][idx].flow);
            }

            for (int v = t; v != s; v = parent[v]) {
                int u = parent[v];
                int idx = parent_edge_idx[v];
                int rev_idx = adj[u][idx].rev_index;

                adj[u][idx].flow += path_flow;
                adj[v][rev_idx].flow -= path_flow;
            }

            max_flow += path_flow;
        }

        return max_flow;
    }
};

int main() {
    int N, M;
    cout << "Enter number of stations (N) and pipelines (M):\n";
    if (!(cin >> N >> M)) return 0;
    
    int S, T;
    cout << "Enter Source (S) and Sink (T):\n";
    cin >> S >> T;

    // Dynamically allocate enough vertices to handle 0-indexed or 1-indexed inputs safely
    int max_vertex = max(N, max(S, T)) + 2; 
    MaxFlowNetwork network(max_vertex);

    cout << "Enter pipelines (u v capacity):\n";
    for (int i = 0; i < M; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        network.addEdge(u, v, c);
    }

    int max_water_flow = network.edmondsKarp(S, T);
    
    cout << "\n--- Result ---\n";
    cout << "Maximum water flow from station " << S << " to " << T << ": " << max_water_flow << " liters/second\n";

    return 0;
}
