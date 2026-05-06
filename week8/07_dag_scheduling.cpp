/*
 * ============================================================================
 *  DAG SCHEDULING / LONGEST PATH IN DAG
 * ============================================================================
 *  PROBLEM: Given a DAG where each vertex has a processing time (weight),
 *  find the minimum time to complete all tasks (respecting dependencies).
 *  This is equivalent to finding the LONGEST PATH in a weighted DAG.
 *  DAG scheduling is a method used to determine the optimal order of tasks in a directed acyclic graph (DAG) based on their dependencies. Each task is represented as a vertex, and directed edges represent dependencies between tasks. The goal of DAG scheduling is to find an execution order that respects these dependencies while minimizing the overall completion time.
 *  WHY LONGEST PATH?
 *  - Tasks can be parallelized, but dependent tasks must wait.
 *  - The critical path (longest path) determines the minimum total time.
 *  - This is the basis of PERT/CPM (Project Evaluation & Review Technique).
 *
 *  ALGORITHM:
 *  1. Topologically sort the DAG.
 *  2. Process vertices in topological order.
 *  3. For each vertex u, relax all outgoing edges:
 *     dist[v] = max(dist[v], dist[u] + weight(u,v))
 *
 *  TIME: O(V + E) — topological sort + one pass over all edges.
 *  SPACE: O(V + E)
 *  For each task v: earliest[v] = max(earliest[u] + duration[u]) for all predecessors u.
 *  NOTE: Longest path in general graphs is NP-hard, but in DAGs it's O(V+E)
 *  because topological ordering ensures we process vertices in correct order.
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
//  1. SHORTEST PATH IN DAG (single source)
// ─────────────────────────────────────────────────────────────────────────────
// Process vertices in topological order. Relax edges, this is same like Dijkstra's but we can do it in O(V+E) because no cycles and we have topological order, 
// this will work for negative weights as well since we are not doing any reprocessing of vertices.
// Time: O(V + E) | Space: O(V)
vector<int> shortestPathDAG(int src, vector<vector<pair<int,int>>>& adj, int V) {
    // Step 1: Topological sort using Kahn's
    vector<int> inDeg(V, 0);
    for (int u = 0; u < V; u++)
        for (auto& [v, w] : adj[u]) inDeg[v]++;

    queue<int> q;
    for (int i = 0; i < V; i++)
        if (inDeg[i] == 0) q.push(i);

    vector<int> topoOrder;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        topoOrder.push_back(u);
        for (auto& [v, w] : adj[u])
            if (--inDeg[v] == 0) q.push(v);
    }

    // Step 2: Relax edges in topological order
    vector<int> dist(V, INT_MAX);
    dist[src] = 0;

    for (int u : topoOrder) {
        if (dist[u] == INT_MAX) continue; // unreachable
        for (auto& [v, w] : adj[u]) {
            dist[v] = min(dist[v], dist[u] + w); // relaxing edge u→v
        }
    }
    return dist;
}

// ─────────────────────────────────────────────────────────────────────────────
//  2. LONGEST PATH IN DAG (Critical Path)
// ─────────────────────────────────────────────────────────────────────────────
// Same as shortest path but use max instead of min.
// This gives the CRITICAL PATH for task scheduling.
// longest path signifies the minimum time to complete all tasks considering dependencies.
// Time: O(V + E) | Space: O(V)
vector<int> longestPathDAG(int src, vector<vector<pair<int,int>>>& adj, int V) {
    // Topological sort
    vector<int> inDeg(V, 0);
    for (int u = 0; u < V; u++)
        for (auto& [v, w] : adj[u]) inDeg[v]++;

    queue<int> q;
    for (int i = 0; i < V; i++)
        if (inDeg[i] == 0) q.push(i);

    vector<int> topoOrder;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        topoOrder.push_back(u);
        for (auto& [v, w] : adj[u])
            if (--inDeg[v] == 0) q.push(v);
    }

    // Relax using MAX
    vector<int> dist(V, INT_MIN);
    dist[src] = 0;

    for (int u : topoOrder) {
        if (dist[u] == INT_MIN) continue;
        for (auto& [v, w] : adj[u]) {
            dist[v] = max(dist[v], dist[u] + w); // relaxing edge u→v
        }
    }
    return dist;
}

// ─────────────────────────────────────────────────────────────────────────────
//  3. TASK SCHEDULING WITH PROCESSING TIMES
// ─────────────────────────────────────────────────────────────────────────────
// Each task has a duration. Dependencies are edges.
// Find earliest completion time for each task and overall project duration.
// Time: O(V + E) | Space: O(V)
void taskScheduling(vector<vector<int>>& deps, vector<int>& duration, int V) {
    // Topological sort
    vector<int> inDeg(V, 0);
    for (int u = 0; u < V; u++)
        for (int v : deps[u]) inDeg[v]++;

    queue<int> q;
    for (int i = 0; i < V; i++)
        if (inDeg[i] == 0) q.push(i);

    vector<int> topoOrder;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        topoOrder.push_back(u);
        for (int v : deps[u])
            if (--inDeg[v] == 0) q.push(v);
    }

    // earliest[v] = earliest start time for task v
    // = max of (earliest[u] + duration[u]) for all predecessors u
    vector<int> earliest(V, 0);

    for (int u : topoOrder) {
        for (int v : deps[u]) {
            earliest[v] = max(earliest[v], earliest[u] + duration[u]); // relaxing edge u→v
        }
    }

    cout << "Task Schedule:\n";
    int projectEnd = 0;
    for (int i = 0; i < V; i++) {
        int endTime = earliest[i] + duration[i];
        cout << "  Task " << i << ": start=" << earliest[i]
             << ", duration=" << duration[i]
             << ", finish=" << endTime << "\n";
        projectEnd = max(projectEnd, endTime);
    }
    cout << "Minimum project completion time: " << projectEnd << "\n";
}

int main() {
    /*
     * DAG for shortest/longest path:
     *   0 --5--> 1 --2--> 3
     *   0 --3--> 2 --7--> 3
     *   1 --6--> 2
     *
     * Shortest from 0: 0→1→3 = 7, 0→2 = 3
     * Longest  from 0: 0→1→2→3 = 18
     */
    int V = 4;
    vector<vector<pair<int,int>>> adj(V);
    adj[0] = {{1,5},{2,3}};
    adj[1] = {{2,6},{3,2}};
    adj[2] = {{3,7}};

    cout << "=== SHORTEST PATH IN DAG (from 0) ===\n";
    auto sp = shortestPathDAG(0, adj, V);
    for (int i = 0; i < V; i++)
        cout << "dist[" << i << "] = " << (sp[i]==INT_MAX ? -1 : sp[i]) << "\n";

    cout << "\n=== LONGEST PATH IN DAG (from 0) ===\n";
    auto lp = longestPathDAG(0, adj, V);
    for (int i = 0; i < V; i++)
        cout << "dist[" << i << "] = " << (lp[i]==INT_MIN ? -1 : lp[i]) << "\n";

    /*
     * Task Scheduling:
     *   Task 0 (3 days) → Task 2 (4 days)
     *   Task 1 (2 days) → Task 2 (4 days)
     *   Task 2 (4 days) → Task 3 (1 day)
     */
    cout << "\n=== TASK SCHEDULING ===\n";
    int V2 = 4;
    vector<vector<int>> deps(V2);
    deps[0] = {2}; deps[1] = {2}; deps[2] = {3};
    vector<int> dur = {3, 2, 4, 1};
    taskScheduling(deps, dur, V2);

    return 0;
}

/*
 * EXAM TIPS:
 * 1. DAG shortest/longest path: topological sort + relax. O(V+E).
 * 2. Longest path in general graph is NP-hard; in DAG it's polynomial.
 * 3. Critical path = longest path = minimum project duration.
 * 4. Task scheduling: earliest[v] = max(earliest[u] + dur[u]) ∀ pred u.
 * 5. This is faster than Dijkstra for DAGs (no priority queue needed).
 */
