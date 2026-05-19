/*
 * m Coloring Problem (Graph Coloring)
 *
 * Description:
 * Given an undirected graph and a number m, determine if the graph can be colored with at
 * most m colors such that no two adjacent vertices of the graph are colored with the same color.
 *
 * Time Complexity: O(m^V) - There are m colors and V vertices.
 * Space Complexity: O(V) - Array for storing colors and call stack.
 */
#include <iostream>
#include <vector>

using namespace std;

class GraphColoring {
private:
    bool isSafe(int v, const vector<vector<int>>& graph, const vector<int>& color, int c) {
        // Check all adjacent vertices to ensure no collision
        for (int i = 0; i < graph.size(); i++) {
            if (graph[v][i] == 1 && color[i] == c) {
                return false;
            }
        }
        return true;
    }

    bool graphColoringUtil(const vector<vector<int>>& graph, int m, vector<int>& color, int v) {
        // Base case: All vertices are successfully assigned a color
        if (v == graph.size()) {
            return true;
        }

        // Try different colors for vertex v
        for (int c = 1; c <= m; c++) {
            if (isSafe(v, graph, color, c)) {
                color[v] = c; // ASSIGN

                // RECURSE to next vertex
                if (graphColoringUtil(graph, m, color, v + 1)) {
                    return true;
                }

                // BACKTRACK
                color[v] = 0;
            }
        }
        return false;
    }

public:
    void solve(const vector<vector<int>>& graph, int m) {
        int V = graph.size();
        vector<int> color(V, 0); // 0 means unassigned

        if (graphColoringUtil(graph, m, color, 0)) {
            cout << "Solution Exists! Coloring arrangement:\n";
            for (int i = 0; i < V; i++) {
                cout << "Vertex " << i << " ---> Color " << color[i] << "\n";
            }
        } else {
            cout << "Solution does not exist for m = " << m << " colors.\n";
        }
    }
};

int main() {
    cout << "--- m Graph Coloring Problem (Backtracking) ---\n";
    // 4 Vertices graph
    // (0)---(1)
    //  | \   |
    //  |  \  |
    // (3)---(2)
    vector<vector<int>> graph = {
        {0, 1, 1, 1},
        {1, 0, 1, 0},
        {1, 1, 0, 1},
        {1, 0, 1, 0}
    };
    int m = 3; // Number of colors
    GraphColoring solver;
    solver.solve(graph, m);
    return 0;
}
