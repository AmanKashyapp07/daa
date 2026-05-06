/*
 * ============================================================================
 *  MAXIMUM BIPARTITE MATCHING
 * ============================================================================
 *  CONCEPTS:
 *  - Bipartite Graph: A graph whose vertices can be divided into two disjoint
 *    sets U and V such that every edge connects a vertex in U to one in V.
 *  - Matching: A set of edges without common vertices.
 *  - Maximum Bipartite Matching: Finding a matching with the maximum possible
 *    number of edges.
 *
 *  REDUCING TO MAX FLOW:
 *  - We can solve this using Ford-Fulkerson!
 *  - Construct a Flow Network:
 *    1. Add a Super Source (s). Connect s to all vertices in U with capacity 1.
 *    2. Direct all original bipartite edges from U to V with capacity 1.
 *    3. Add a Super Sink (t). Connect all vertices in V to t with capacity 1.
 *  - The Maximum Flow from s to t is equal to the Maximum Bipartite Matching.
 *
 *  DFS AUGMENTING PATH ALGORITHM (Equivalent to Max Flow):
 *  - Since all capacities are 1, we can use a simpler DFS-based approach.
 *  - Try to find an augmenting path for each vertex in U.
 *  - If we find an unmatched vertex in V, match it. If the vertex in V is 
 *    already matched, recursively try to find an augmenting path for its 
 *    current match.
 *
 *  TIME COMPLEXITY: O(V * E) where V is vertices in U.
 *
 *  EXAM TIP:
 *  - Job Assignment Problem: U = Applicants, V = Jobs. Edge means applicant 
 *    can do the job. Find max applicants that can get jobs.
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
//  BIPARTITE MATCHING IMPLEMENTATION
// ─────────────────────────────────────────────────────────────────────────────
// DFS-based function that returns true if a matching for vertex u is possible
bool bpm(const vector<vector<int>>& bpGraph, int u, vector<bool>& visited, vector<int>& match) {
    int N = bpGraph[0].size(); // Number of vertices in V

    for (int v = 0; v < N; ++v) {
        // If there's an edge from u to v and v is not visited
        if (bpGraph[u][v] && !visited[v]) {
            // Mark v as visited
            visited[v] = true;

            // If job 'v' is not assigned to an applicant OR previously assigned 
            // applicant for job v (which is match[v]) has an alternate job available.
            if (match[v] < 0 || bpm(bpGraph, match[v], visited, match)) {
                match[v] = u;
                return true;
            }
        }
    }
    return false;
}

// Returns maximum number of matching from U to V
int maxBPM(const vector<vector<int>>& bpGraph) {
    int M = bpGraph.size();    // Number of applicants (Set U)
    int N = bpGraph[0].size(); // Number of jobs (Set V)

    // An array to keep track of the applicants assigned to jobs. 
    // match[i] is the applicant ID assigned to job i. -1 means nobody.
    vector<int> match(N, -1);

    int result = 0;
    for (int u = 0; u < M; ++u) {
        // Mark all jobs as not visited for next applicant
        vector<bool> visited(N, false);

        // Find if applicant 'u' can get a job
        if (bpm(bpGraph, u, visited, match)) {
            result++;
        }
    }

    // Print the matching
    cout << "Matching Assignments:\n";
    for (int v = 0; v < N; ++v) {
        if (match[v] != -1) {
            cout << "Applicant " << match[v] << " assigned to Job " << v << "\n";
        }
    }

    return result;
}

// ─────────────────────────────────────────────────────────────────────────────
//  DRIVER
// ─────────────────────────────────────────────────────────────────────────────
int main() {
    /*
     * Example Bipartite Graph (Applicants and Jobs):
     * M = 6 Applicants (0 to 5)
     * N = 6 Jobs (0 to 5)
     * bpGraph[i][j] = 1 if applicant i is interested in job j.
     */
    vector<vector<int>> bpGraph = {
        {0, 1, 1, 0, 0, 0},
        {1, 0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0, 0},
        {0, 0, 1, 1, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1}
    };

    cout << "=== MAXIMUM BIPARTITE MATCHING ===\n";
    int max_matching = maxBPM(bpGraph);
    cout << "\nMaximum number of applicants that can get jobs: " << max_matching << "\n";

    return 0;
}
