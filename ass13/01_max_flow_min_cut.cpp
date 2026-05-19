/*
 * Problem A: Maximum Flow and Minimum Cut
 * Application: City Water Supply Network
 *
 * Logic:
 * 1. Maximum Flow: We use the Edmonds-Karp algorithm (Ford-Fulkerson using BFS).
 *    We repeatedly find an augmenting path from the source (reservoir) to the
 *    sink (city center) in the residual graph. We push the maximum possible flow
 *    along this path and update the residual capacities.
 * 2. Minimum Cut: Once no more augmenting paths can be found, the flow is maximized.
 *    The residual graph will have a set of vertices reachable from the source (Set S)
 *    and the rest unreachable (Set T). 
 *    The pipes (edges) that the enemy should target are those going from a vertex
 *    in Set S to a vertex in Set T in the original network. These pipes will be
 *    completely full (residual capacity = 0).
 * 3. Max-Flow Min-Cut Theorem: The total capacity of the pipes in the minimum cut
 *    will be exactly equal to the maximum flow.
 */
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <climits>

using namespace std;

// Number of vertices in the given graph
#define V 6

// BFS to find an augmenting path. Returns true if there is a path from source 's' to sink 't'.
// Also fills parent[] to store the path.
bool bfs(int rGraph[V][V], int s, int t, int parent[]) {
    bool visited[V];
    memset(visited, 0, sizeof(visited));

    queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < V; v++) {
            if (visited[v] == false && rGraph[u][v] > 0) {
                // If we find a connection to the sink node, then there is no point in BFS anymore
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

// DFS to find all reachable vertices from source in the residual graph
void dfs(int rGraph[V][V], int s, bool visited[]) {
    visited[s] = true;
    for (int i = 0; i < V; i++)
        if (rGraph[s][i] > 0 && !visited[i])
            dfs(rGraph, i, visited);
}

void maxFlowMinCut(int graph[V][V], int s, int t) {
    int u, v;

    // Create a residual graph and fill the residual graph with given capacities
    // rGraph[i][j] indicates residual capacity of edge from i to j
    int rGraph[V][V];
    for (u = 0; u < V; u++)
        for (v = 0; v < V; v++)
             rGraph[u][v] = graph[u][v];

    int parent[V];  // This array is filled by BFS and to store path
    int max_flow = 0;

    // Augment the flow while there is path from source to sink
    while (bfs(rGraph, s, t, parent)) {
        // Find minimum residual capacity of the edges along the path filled by BFS.
        int path_flow = INT_MAX;
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }

        // update residual capacities of the edges and reverse edges along the path
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }

        max_flow += path_flow;
    }

    cout << "1. Maximum water that can flow from reservoir to city: " << max_flow << endl;

    // Find all vertices reachable from the source in the final residual graph
    bool visited[V];
    memset(visited, 0, sizeof(visited));
    dfs(rGraph, s, visited);

    // Print all edges that are from a reachable vertex to non-reachable vertex in the original graph
    cout << "\n2. Minimum Cut (Pipes the enemy should target):\n";
    int min_cut_capacity = 0;
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (visited[i] && !visited[j] && graph[i][j] > 0) {
                cout << "   Pipe from Node " << i << " to Node " << j << " (Capacity: " << graph[i][j] << ")\n";
                min_cut_capacity += graph[i][j];
            }
        }
    }

    cout << "\n3. Proof of Max-Flow Min-Cut Theorem:\n";
    cout << "   Maximum Flow = " << max_flow << "\n";
    cout << "   Minimum Cut Capacity = " << min_cut_capacity << "\n";
    if (max_flow == min_cut_capacity) {
        cout << "   Hence, Maximum Flow equals Minimum Cut Capacity!\n";
    }
}

int main() {
    // Example Graph (Water Network)
    // Node 0: Reservoir (Source)
    // Node 5: City Center (Sink)
    int graph[V][V] = {
        {0, 16, 13, 0, 0, 0},
        {0, 0, 10, 12, 0, 0},
        {0, 4, 0, 0, 14, 0},
        {0, 0, 9, 0, 0, 20},
        {0, 0, 0, 7, 0, 4},
        {0, 0, 0, 0, 0, 0}
    };

    cout << "--- Water Supply Network Analysis ---\n\n";
    maxFlowMinCut(graph, 0, 5);

    return 0;
}
