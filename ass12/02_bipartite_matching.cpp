/*
 * Problem B: Maximum Bipartite Matching
 * Application: Worker-Job Assignment
 *
 * Logic:
 * We can solve the Maximum Bipartite Matching problem by transforming it into a
 * Maximum Flow problem.
 * 1. Create a bipartite graph where workers form one set of nodes and jobs form the other.
 * 2. Introduce a "Super-Source" (S*) and a "Super-Sink" (T*).
 * 3. Connect S* to all worker nodes with a directed edge of capacity 1.
 * 4. Connect all job nodes to T* with a directed edge of capacity 1.
 * 5. For every qualification (worker w is qualified for job j), add a directed edge
 *    from w to j with capacity 1.
 * 6. The maximum flow from S* to T* in this network is exactly the maximum number
 *    of valid job assignments.
 * 
 * Time Complexity Analysis:
 * - We use the Edmonds-Karp algorithm (BFS based Ford-Fulkerson).
 * - Total vertices V' = N (workers) + M (jobs) + 2 (super-source, super-sink).
 * - Total edges E' = E (qualifications) + N (S* to workers) + M (jobs to T*).
 * - In a unit capacity network, Edmonds-Karp runs in bounded O(E' * sqrt(V')) time, 
 *   which is faster than the general O(V * E^2) bound.
 * - This mirrors the efficiency of Hopcroft-Karp which is natively O(E * sqrt(V)).
 * - Total Time Complexity here: O(E * sqrt(N + M)).
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
    cout << "Enter number of workers (N) and jobs (M):\n";
    if (!(cin >> N >> M)) return 0;
    
    int E;
    cout << "Enter number of worker-job qualifications (E):\n";
    cin >> E;

    // We structure the IDs to avoid conflicts regardless of 0-based or 1-based indexing:
    // Workers will retain their ID 'w'.
    // Jobs will be offset by 'N' -> 'N + j'
    // Super-Source will be 'N + M + 1'
    // Super-Sink will be 'N + M + 2'
    
    int total_vertices = N + M + 5; // buffer included
    int super_source = N + M + 1;
    int super_sink = N + M + 2;

    MaxFlowNetwork network(total_vertices);

    // Connect Super-Source to all possible workers with capacity 1
    // Supports both 0-indexed and 1-indexed inputs safely
    for (int i = 0; i <= N; i++) {
        network.addEdge(super_source, i, 1);
    }

    // Connect all possible jobs to Super-Sink with capacity 1
    for (int j = 0; j <= M; j++) {
        network.addEdge(N + j, super_sink, 1);
    }

    cout << "Enter qualifications (worker job):\n";
    for (int i = 0; i < E; i++) {
        int w, j;
        cin >> w >> j;
        // Connect worker to offset job with capacity 1
        network.addEdge(w, N + j, 1);
    }

    int max_assignments = network.edmondsKarp(super_source, super_sink);
    
    cout << "\n--- Result ---\n";
    cout << "Maximum number of possible job assignments: " << max_assignments << "\n";

    return 0;
}
