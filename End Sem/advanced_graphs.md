# Advanced Graph Algorithms - End Semester Master Summary

This document synthesizes three major graph algorithm units: **Single-Source Shortest Path (SSSP)**, **All-Pairs Shortest Path (APSP)**, and **Minimum Spanning Trees (MST)**. It includes complexities, core logic, and formal exam-style correctness proofs.

---

## 1. Single-Source Shortest Path (SSSP)
**Goal:** Find the shortest path (minimum total edge weight) from one specific source vertex to all other vertices in a weighted graph.

### A. Dijkstra’s Algorithm
- **Constraint:** Requires strictly **non-negative edge weights**.
- **Algorithm (Greedy):**
  1. Maintain a Min-Heap of vertices sorted by current shortest distance from the source.
  2. Extract the absolute closest unvisited vertex $u$.
  3. **Relaxation:** For every neighbor $v$ of $u$, if `dist[u] + weight(u, v) < dist[v]`, update `dist[v]` and push to the Min-Heap.
- **Complexity:** $O(E \log V)$ using a Min-Heap.

**📝 Exam-Style Correctness Proof (Proof by Contradiction):**
- **Claim:** When a vertex $u$ is extracted from the Min-Heap, `dist[u]` is mathematically optimal (i.e., `dist[u]` = $\delta(s, u)$).
- **Proof:** Suppose for contradiction that $u$ is the *first* vertex extracted where `dist[u]` $\neq \delta(s, u)$. Since we are extracting $u$, its current estimate must be too high (`dist[u]` $> \delta(s, u)$). 
  This implies there exists a strictly shorter, unvisited path from the source $s$ to $u$. Let this optimal path diverge at some unvisited vertex $y$ currently waiting in the heap.
  Because all edge weights are non-negative ($w \ge 0$), the true absolute distance to $y$ must be strictly $\le$ the true distance to $u$ (i.e., $\delta(s, y) \le \delta(s, u)$). 
  Because $y$ is on the frontier of the visited set, its current heap distance `dist[y]` is already optimally relaxed. Thus, `dist[y] = \delta(s, y) \le \delta(s, u) < dist[u]`.
  If `dist[y] < dist[u]`, the Min-Heap would have explicitly extracted $y$ *before* $u$. This perfectly contradicts the assumption that $u$ was extracted! Therefore, `dist[u]` is always unconditionally optimal upon extraction.

### B. Bellman-Ford Algorithm
- **Constraint:** Handles **negative edge weights** and detects **negative-weight cycles**.
- **Algorithm (Dynamic Programming):**
  1. Initialize all distances to $\infty$, source to $0$.
  2. Relax *every edge* exactly $V-1$ times.
  3. **Cycle Check:** Do one final pass. If any edge can still be relaxed, a negative-weight cycle exists.
- **Complexity:** $O(V \cdot E)$

**📝 Exam-Style Correctness Proof (Path-Length Induction):**
- **Claim:** After $i$ iterations of the outer loop, the algorithm accurately evaluates the optimal shortest path to all vertices reachable using $\le i$ edges.
- **Proof:** A simple shortest path (with no cycles) in a graph with $V$ vertices contains at an absolute maximum $V-1$ edges. 
  By relaxing all edges in the 1st iteration, we mathematically guarantee we capture all optimal paths of length 1. By standard induction, if we have locked in all optimal paths of length $i-1$, relaxing all edges on the $i$-th iteration guarantees we discover any optimal path extended to length $i$. 
  Therefore, exactly $V-1$ iterations guarantee all simple shortest paths are verified. If distances mutate on the $V$-th pass, it implies an optimal path with $V$ edges exists. By the Pigeonhole Principle, a path navigating $V$ edges among $V$ vertices must revisit a vertex, mathematically proving the strict existence of a negative-weight cycle.

---

## 2. All-Pairs Shortest Path (APSP)

### Floyd-Warshall Algorithm
- **Algorithm (Dynamic Programming):** 
  - Allows intermediate vertices $\{1, 2, \dots, k\}$ to be used in paths.
  - **State Transition:** `dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])`.
- **Complexity:** $O(V^3)$ Time | $O(V^2)$ Space.

**📝 Exam-Style Correctness Proof (Optimal Substructure DP):**
- **Claim:** The state $D^{(k)}_{ij}$ accurately represents the shortest path from $i$ to $j$ using strictly intermediate vertices selected only from the subset $\{1, 2, \dots, k\}$.
- **Proof:** For any evaluated path from $i \to j$ allowing intermediates up to $k$, there are exactly two mutually exclusive possibilities:
  1. **Vertex $k$ is NOT on the optimal path:** The shortest path relies purely on vertices $\{1 \dots k-1\}$, making the optimal cost identically $D^{(k-1)}_{ij}$.
  2. **Vertex $k$ IS on the optimal path:** The path can be cleanly split into two subpaths: $i \to k$ and $k \to j$. Because $k$ is an intermediate bottleneck, these subpaths only utilize intermediate vertices $\{1 \dots k-1\}$. Thus, the cumulative cost is identically $D^{(k-1)}_{ik} + D^{(k-1)}_{kj}$.
  By calculating the mathematical minimum of these two exhaustive cases at each sequential step $k$, the Bellman Equation formulation guarantees global optimality.

---

## 3. Minimum Spanning Trees (MST)

### The Minimum Cut Property (Crucial Core Theorem)
**Claim:** For any valid cut (partitioning vertices into $S$ and $V-S$) in a connected weighted graph, if an edge $e$ is the absolute minimum-weight edge crossing the cut boundary, $e$ MUST exist in the Minimum Spanning Tree.
**Proof (Exchange Argument):** Suppose for contradiction an MST $T$ does *not* contain the minimum crossing edge $e=(u, v)$. Because $T$ is a spanning tree, it inherently already contains some connected path from $u$ to $v$. This path MUST cross the cut boundary at some other edge $e'$. Since $e$ is strictly defined as the minimum crossing edge, $w(e) < w(e')$. If we physically remove $e'$ from $T$ and insert $e$, the graph remains fully connected (the loop cycle is severed), but the total structural weight of the tree strictly decreases. This massively contradicts the core assumption that $T$ was a Minimum Spanning Tree. Thus, $e$ must fundamentally be included in the MST.

### A. Kruskal’s Algorithm
- **Algorithm (Greedy + Disjoint Set):**
  1. Sort all edges in ascending order.
  2. Iterate through edges; add them to the MST if they connect two isolated trees (verified via DSU).
- **Complexity:** $O(E \log E)$

**📝 Exam-Style Correctness Proof:**
- **Proof:** Kruskal's algorithm is a direct procedural implementation of the Minimum Cut Property. Let $e=(u, v)$ be the next cheapest edge evaluated that doesn't form a cycle. Let $S$ be the isolated connected component containing $u$. Because $e$ connects $u$ to an unvisited vertex $v$, $e$ structurally crosses the cut boundary between $S$ and $V-S$. Since the algorithm sorted the edges ascending, $e$ is mathematically guaranteed to be the lightest possible edge currently crossing this boundary cut. Ergo, by the Minimum Cut Property, $e$ securely belongs in the MST.

### B. Prim’s Algorithm
- **Algorithm (Greedy + Min-Heap):**
  1. Start at an arbitrary root vertex. Push its edges into a Min-Heap.
  2. Extract the cheapest edge. If it leads to an unvisited vertex, add to MST, push its new edges.
- **Complexity:** $O(E \log V)$

**📝 Exam-Style Correctness Proof:**
- **Proof:** Prim's algorithm also continuously embodies the Minimum Cut Property. At any arbitrary processing step, let the set of currently aggregated visited vertices be $S$. The boundary between the visited matrix $S$ and the unvisited matrix $V-S$ defines a valid mathematical cut. The Priority Queue (Min-Heap) is inherently designed to isolate and extract the minimum-weight edge currently intersecting this exact cut boundary. Therefore, enforced by the Minimum Cut theorem, the edge selected at every discrete step strictly belongs in the final structural MST.
