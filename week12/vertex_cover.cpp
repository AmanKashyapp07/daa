#include <iostream>
#include <vector>
#include <list>

using namespace std;

class Graph {
    int V; // Number of vertices
    vector<list<int>> adj; // Adjacency list

public:
    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u); // Undirected graph
    }

    // The 2-Approximation Algorithm for Vertex Cover
    void approximateVertexCover() {
        // Initialize all vertices as not included in the cover
        vector<bool> visited(V, false);

        // Iterate through all edges
        for (int u = 0; u < V; u++) {
            // If vertex 'u' is not yet visited
            if (visited[u] == false) {
                // Check all adjacent vertices of 'u'
                for (int v : adj[u]) {
                    // Find the first adjacent vertex 'v' that is also not visited.
                    // This means we found an edge (u, v) where neither endpoint is in the cover.
                    if (visited[v] == false) {
                        // Add BOTH endpoints to the vertex cover
                        visited[u] = true;
                        visited[v] = true;
                        break; // Move to the next unvisited vertex in the outer loop
                    }
                }
            }
        }

        // Print the calculated vertex cover
        cout << "Approximate Vertex Cover includes nodes: ";
        for (int i = 0; i < V; i++) {
            if (visited[i]) {
                cout << i << " ";
            }
        }
        cout << endl;
    }
};

int main() {
    // Recreating the "Star Graph" example where the approximation grabs extra nodes
    Graph g(5);
    g.addEdge(0, 1); // 0 is the center node
    g.addEdge(0, 2);
    g.addEdge(0, 3);
    g.addEdge(0, 4);

    cout << "Running 2-Approximation Algorithm...\n";
    g.approximateVertexCover();
    
    // Note: The optimal cover is just {0}. 
    // The algorithm will pick an edge (e.g., 0-1), mark both 0 and 1 as visited.
    // Since 0 is now visited, it won't pick any other edges connected to 0.
    // Result size is 2. (2 <= 2 * 1) holds true!

    return 0;
}