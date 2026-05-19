/*
 * Problem B: Multi-Source Multi-Sink Maximum Flow
 *
 * Logic:
 * To solve a maximum flow problem with multiple sources and multiple sinks,
 * we can reduce it to a standard single-source, single-sink maximum flow problem.
 * 
 * Transformation steps:
 * 1. Introduce a "Super-Source" (S*) and a "Super-Sink" (T*).
 * 2. Connect the Super-Source (S*) to all actual source nodes with edges of infinite capacity.
 * 3. Connect all actual sink nodes to the Super-Sink (T*) with edges of infinite capacity.
 * 4. Run any standard max-flow algorithm (like Edmonds-Karp) from S* to T*.
 * 
 * The maximum flow from S* to T* in this transformed network will be equal to the
 * maximum flow in the original multi-source multi-sink network.
 */

#include <iostream>
#include <vector>
#include <queue>
#include <climits>

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
    int V; // Number of vertices including super-source and super-sink
    vector<vector<Edge>> adj;

    // BFS to find an augmenting path
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
        // Forward edge
        adj[u].push_back({v, cap, 0, (int)adj[v].size()});
        // Reverse edge with 0 capacity
        adj[v].push_back({u, 0, 0, (int)adj[u].size() - 1});
    }

    int edmondsKarp(int s, int t) {
        int max_flow = 0;
        vector<int> parent(V);
        vector<int> parent_edge_idx(V);

        while (bfs(s, t, parent, parent_edge_idx)) {
            int path_flow = INT_MAX;

            // Find bottleneck capacity along the path
            for (int v = t; v != s; v = parent[v]) {
                int u = parent[v];
                int idx = parent_edge_idx[v];
                path_flow = min(path_flow, adj[u][idx].capacity - adj[u][idx].flow);
            }

            // Augment flow
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
    /*
     * Example Network:
     * 4 original nodes: 0, 1, 2, 3
     * Sources: 0, 1
     * Sinks: 2, 3
     * 
     * Original Edges:
     * 0 -> 2 (Capacity: 10)
     * 0 -> 3 (Capacity: 5)
     * 1 -> 2 (Capacity: 15)
     * 1 -> 3 (Capacity: 10)
     */

    int original_vertices = 4;
    vector<int> sources = {0, 1};
    vector<int> sinks = {2, 3};

    // New vertices count = original + Super-Source + Super-Sink
    int V = original_vertices + 2; 
    int super_source = original_vertices;     // Index 4
    int super_sink = original_vertices + 1;   // Index 5

    MaxFlowNetwork network(V);

    // Add original edges
    network.addEdge(0, 2, 10);
    network.addEdge(0, 3, 5);
    network.addEdge(1, 2, 15);
    network.addEdge(1, 3, 10);

    cout << "--- Multi-Source Multi-Sink Maximum Flow ---\n\n";

    // Add edges from Super-Source to all original sources with infinite capacity
    for (int s : sources) {
        network.addEdge(super_source, s, INT_MAX);
        cout << "Added edge from Super-Source (" << super_source << ") to Source (" << s << ") with INF capacity.\n";
    }

    // Add edges from all original sinks to Super-Sink with infinite capacity
    for (int t : sinks) {
        network.addEdge(t, super_sink, INT_MAX);
        cout << "Added edge from Sink (" << t << ") to Super-Sink (" << super_sink << ") with INF capacity.\n";
    }

    cout << "\nCalculating Maximum Flow from Super-Source to Super-Sink...\n";
    int max_flow = network.edmondsKarp(super_source, super_sink);

    cout << "\nTotal Maximum Flow in the multi-source multi-sink network: " << max_flow << "\n";

    return 0;
}
