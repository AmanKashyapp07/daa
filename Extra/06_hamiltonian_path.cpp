/*
 * Hamiltonian Path and Cycle
 *
 * Description:
 * A Hamiltonian path is a path in an undirected graph that visits every vertex exactly once.
 * If there is an edge from the last visited vertex to the first, it is a Hamiltonian Cycle.
 *
 * Time Complexity: O(V!) - Upper bound for exploring all permutations of vertices.
 * Space Complexity: O(V) - Array for storing path and call stack.
 */
#include <iostream>
#include <vector>

using namespace std;

class Hamiltonian {
private:
    bool isSafe(int v, const vector<vector<int>>& graph, const vector<int>& path, int pos) {
        // Check if there is an edge from previously added vertex to this vertex
        if (graph[path[pos - 1]][v] == 0) {
            return false;
        }

        // Check if the vertex has already been included
        for (int i = 0; i < pos; i++) {
            if (path[i] == v) {
                return false;
            }
        }
        return true;
    }

    bool hamiltonianCycleUtil(const vector<vector<int>>& graph, vector<int>& path, int pos) {
        int V = graph.size();
        // Base case: If all vertices are included
        if (pos == V) {
            // Check if there is an edge from the last included vertex to the first vertex
            if (graph[path[pos - 1]][path[0]] == 1) {
                return true; // Hamiltonian CYCLE exists
            } else {
                return false; // Only a path, not a cycle
            }
        }

        // Try different vertices as the next candidate in Hamiltonian Cycle
        for (int v = 1; v < V; v++) { // Start at 1, keeping 0 as the source
            if (isSafe(v, graph, path, pos)) {
                path[pos] = v; // ASSIGN

                if (hamiltonianCycleUtil(graph, path, pos + 1)) {
                    return true;
                }

                path[pos] = -1; // BACKTRACK
            }
        }
        return false;
    }

public:
    void solve(const vector<vector<int>>& graph) {
        int V = graph.size();
        vector<int> path(V, -1);
        
        path[0] = 0; // Fix vertex 0 as starting point

        if (hamiltonianCycleUtil(graph, path, 1)) {
            cout << "Hamiltonian Cycle found:\n";
            for (int i = 0; i < V; i++) {
                cout << path[i] << " -> ";
            }
            cout << path[0] << " (Cycle back)\n";
        } else {
            cout << "No Hamiltonian Cycle exists.\n";
        }
    }
};

int main() {
    cout << "--- Hamiltonian Cycle Problem (Backtracking) ---\n";
    vector<vector<int>> graph = {
        {0, 1, 0, 1, 0},
        {1, 0, 1, 1, 1},
        {0, 1, 0, 0, 1},
        {1, 1, 0, 0, 1},
        {0, 1, 1, 1, 0}
    };
    Hamiltonian solver;
    solver.solve(graph);
    return 0;
}
