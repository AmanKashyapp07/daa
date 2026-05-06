/*
 * ============================================================================
 *  VERTEX COVER & CLIQUE (NP-Complete Problems)
 * ============================================================================
 *  CONCEPTS:
 *  - Vertex Cover: A set of vertices such that every edge has at least one 
 *    endpoint in the set.
 *  - Clique: A subset of vertices where every two distinct vertices are 
 *    adjacent (a complete subgraph).
 *  - Independent Set: A subset of vertices where no two vertices are adjacent.
 *
 *  REDUCTIONS (A <=p B):
 *  - Clique to Independent Set: Graph G has a Clique of size K iff its 
 *    complement graph G' has an Independent Set of size K.
 *  - Independent Set to Vertex Cover: Graph G has an Independent Set of size K 
 *    iff it has a Vertex Cover of size V - K.
 *
 *  SOLVING NP-COMPLETE PROBLEMS:
 *  Since finding an exact solution is exponential (worst-case), we use:
 *  1. Backtracking / Exhaustive Search: Guaranteed correct, but slow O(2^V).
 *  2. Approximation Algorithms / Heuristics: Fast (Polynomial), but doesn't 
 *     guarantee the optimal answer (though it might guarantee being within a 
 *     certain factor of optimal).
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
//  1. EXACT VERTEX COVER (Backtracking - Exponential Time O(2^V))
// ─────────────────────────────────────────────────────────────────────────────
// Checks if the current 'included' subset is a valid vertex cover
bool isCover(int V, const vector<pair<int, int>>& edges, const vector<bool>& included) {
    for (auto edge : edges) {
        if (!included[edge.first] && !included[edge.second]) {
            return false;
        }
    }
    return true;
}

// Backtracking to find minimum vertex cover
void minVertexCoverBacktracking(int idx, int V, const vector<pair<int, int>>& edges, 
                                vector<bool>& included, int& min_size, vector<int>& best_cover) {
    if (idx == V) {
        if (isCover(V, edges, included)) {
            int current_size = 0;
            for (int i = 0; i < V; i++) if (included[i]) current_size++;
            
            if (current_size < min_size) {
                min_size = current_size;
                best_cover.clear();
                for (int i = 0; i < V; i++) if (included[i]) best_cover.push_back(i);
            }
        }
        return;
    }

    // Choice 1: Include vertex idx
    included[idx] = true;
    minVertexCoverBacktracking(idx + 1, V, edges, included, min_size, best_cover);

    // Choice 2: Exclude vertex idx
    included[idx] = false;
    minVertexCoverBacktracking(idx + 1, V, edges, included, min_size, best_cover);
}

// ─────────────────────────────────────────────────────────────────────────────
//  2. APPROXIMATE VERTEX COVER (Greedy Heuristic - Polynomial Time)
// ─────────────────────────────────────────────────────────────────────────────
// A standard 2-approximation algorithm for Vertex Cover.
// Pick an arbitrary edge, add BOTH endpoints to the cover, remove all edges 
// attached to both. Repeat. Guaranteed to be <= 2 * OPTIMAL.
void approximateVertexCover(int V, vector<pair<int, int>> edges) {
    vector<bool> visited(V, false);
    vector<int> cover;

    for (int i = 0; i < edges.size(); ++i) {
        int u = edges[i].first;
        int v = edges[i].second;

        if (!visited[u] && !visited[v]) {
            // Add both endpoints to the cover
            visited[u] = true;
            visited[v] = true;
            cover.push_back(u);
            cover.push_back(v);
        }
    }

    cout << "Approximate Vertex Cover size: " << cover.size() << "\nVertices: ";
    for (int v : cover) cout << v << " ";
    cout << "\n";
}

// ─────────────────────────────────────────────────────────────────────────────
//  DRIVER
// ─────────────────────────────────────────────────────────────────────────────
int main() {
    int V = 5;
    vector<pair<int, int>> edges = {
        {0, 1}, {0, 2}, {1, 2}, {1, 3}, {2, 4}, {3, 4}
    };

    cout << "=== EXACT VERTEX COVER (Backtracking) ===\n";
    vector<bool> included(V, false);
    int min_size = INT_MAX;
    vector<int> best_cover;

    minVertexCoverBacktracking(0, V, edges, included, min_size, best_cover);

    cout << "Optimal Vertex Cover size: " << min_size << "\nVertices: ";
    for (int v : best_cover) cout << v << " ";
    cout << "\n\n";


    cout << "=== APPROXIMATE VERTEX COVER (Heuristic) ===\n";
    approximateVertexCover(V, edges);

    return 0;
}
