# Elementary Graph Algorithms - End Semester Master Summary

This document serves as a comprehensive, exam-aligned summary of the "Elementary Graph Algorithms" lecture. It includes core mechanics, complexities, and intuitive correctness proofs designed specifically for exam retention.

---

## 1. Graph Representations
Graphs $G = (V, E)$ can be represented in two primary ways:

1. **Adjacency Matrix:** A $V \times V$ matrix where $A[i][j] = 1$ if edge $(i, j)$ exists.
   - **Space Complexity:** $\Theta(V^2)$
   - **Edge Lookup:** $O(1)$
   - **Best for:** Dense graphs where $|E|$ is close to $|V|^2$.

2. **Adjacency List:** An array of $V$ linked lists, where list $i$ contains all neighbors of vertex $i$.
   - **Space Complexity:** $\Theta(V + E)$
   - **Edge Lookup:** $O(\text{degree}(v))$
   - **Best for:** Sparse graphs where $|E|$ is much less than $|V|^2$.

---

## 2. Breadth-First Search (BFS)
**Goal:** Explore a graph radially outward from a source vertex $s$. It discovers all vertices at distance $k$ before discovering any vertices at distance $k+1$.

**Mechanism:** Uses a **Queue (FIFO)**.
- **Colors used to track state:**
  - **White:** Undiscovered.
  - **Gray:** Discovered but frontier (in the queue).
  - **Black:** Fully explored (all neighbors discovered).

**Complexity:** $O(V + E)$

### 🧠 Correctness Proof & Intuition (Shortest Path)
- **Claim:** BFS correctly finds the shortest path (minimum number of edges) from the source $s$ to all reachable vertices.
- **Intuition to Remember (The Ripple Effect):** Think of BFS as dropping a stone in water. The ripples expand uniformly. Because BFS uses a FIFO (First-In-First-Out) queue, it completely processes all vertices at distance $1$, then distance $2$, then distance $3$. 
- **Proof Logic:** We prove by induction. Since the queue inherently strictly maintains distance order (e.g., $Q = [d, d, d, d+1, d+1]$), it is physically impossible for the algorithm to discover a vertex via a longer path first. The very first time a vertex turns from White to Gray, it *must* have been reached by the shortest possible sequence of edges.

---

## 3. Depth-First Search (DFS)
**Goal:** Explore as deeply as possible along each branch before backtracking. 

**Mechanism:** Uses a **Stack (LIFO)** or recursion.
- Associates two timestamps with every vertex $v$:
  1. $d[v]$: Discovery time (when it turns Gray).
  2. $f[v]$: Finishing time (when it turns Black).

**Key Theorems:**
1. **Parenthesis Theorem:** Timestamps behave like perfectly nested parentheses. For any two vertices $u$ and $v$, either:
   - They are completely disjoint $[u..u] \ [v..v]$.
   - One is fully nested inside the other $[u \ [v..v] \ u]$ (meaning $v$ is a descendant of $u$).
2. **White-Path Theorem:** $v$ is a descendant of $u$ if and only if at time $d[u]$, there is a path of exclusively white vertices from $u$ to $v$.

**Edge Classification in DFS:**
1. **Tree Edge:** Explores a new (white) vertex.
2. **Back Edge:** Connects a vertex to an ancestor (gray vertex). Indicates a **cycle**.
3. **Forward Edge:** Connects a vertex to a descendant (black vertex) that is not a tree edge.
4. **Cross Edge:** All other edges (between branches).

**Complexity:** $\Theta(V + E)$

---

## 4. Directed Acyclic Graphs (DAGs) & Topological Sort
**DAG:** A directed graph with absolutely **no cycles**.
> **Critical Lemma:** A directed graph is a DAG if and only if a DFS yields **no back edges**.

**Topological Sort Algorithm:**
1. Call `DFS(G)` to compute finishing times $f[v]$ for every vertex.
2. As each vertex is finished, insert it onto the **front** of a linked list. (Effectively sorting by **decreasing** finishing times).

**Complexity:** $\Theta(V + E)$

### 🧠 Correctness Proof & Intuition (Topological Sort)
- **Claim:** If there is a directed edge $u \to v$, then $u$ appears before $v$ in the sorted list (i.e., $f[u] > f[v]$).
- **Intuition to Remember (The Dependency Check):** Imagine $u$ is a prerequisite for $v$. We must prove that $u$ always finishes *after* $v$. Let's look at the color of $v$ when we explore the edge $u \to v$:
  1. **If $v$ is White:** $v$ becomes a descendant of $u$. $v$ will fully process and finish while $u$ is still waiting. Thus, $f[u] > f[v]$.
  2. **If $v$ is Black:** $v$ has already finished entirely in the past. We are currently inside $u$, so $u$ hasn't finished yet. Thus, $f[u] > f[v]$.
  3. **If $v$ is Gray:** This means $v$ is currently open and is an ancestor of $u$. But this forms a cycle (a back-edge)! Since we are in a DAG, this is mathematically impossible.
- **Conclusion:** In all valid cases, $f[u] > f[v]$. Therefore, sorting by decreasing finishing time is perfectly correct.

---

## 5. Strongly Connected Components (SCC)
**Definition:** An SCC is a maximal subset of vertices where every pair $u, v$ has a path from $u \to v$ AND from $v \to u$.

**Component Graph ($G_{SCC}$):** If you condense every SCC into a single "super-vertex", $G_{SCC}$ is always a **DAG**.
**Transpose Graph ($G^T$):** The graph with all edge directions reversed. It shares the exact same SCCs as $G$.

### Kosaraju's Algorithm:
1. Call `DFS(G)` to compute finishing times $f[u]$ for all vertices.
2. Compute the transpose graph $G^T$.
3. Call `DFS(G^T)`, exploring vertices in **decreasing order of $f[u]$** (from step 1).
4. Each distinct depth-first tree formed in this second pass is one SCC.

**Complexity:** $\Theta(V + E)$

### 🧠 Correctness Proof & Intuition (Kosaraju's Algorithm)
- **Claim:** Reversing the graph and traversing by decreasing finishing times perfectly isolates SCCs.
- **Intuition to Remember (The Sink Trap):** 
  - Imagine two SCC components: $A$ pointing to $B$ ($A \to B$). 
  - **The Timing Rule:** The first DFS guarantees that the highest finishing time in $A$ will ALWAYS be strictly greater than the highest finishing time in $B$ ($f(A) > f(B)$). 
    - *Why?* If we start in $A$, we flow into $B$, finish all of $B$, then finish $A$. If we start in $B$, we finish $B$, get stuck (can't reach $A$), restart in $A$, and finish $A$ later. Either way, $A$ finishes last!
  - **The Reversal Trap:** When we compute the Transpose $G^T$, the edge $A \to B$ flips to $B \to A$.
  - **The Execution:** The second DFS tells us to start at the node with the highest finishing time. Since $f(A) > f(B)$, we **must start in $A$**. 
  - Now, because we are in $G^T$ and the edge points backwards ($B \to A$), we **cannot escape $A$ to reach $B$**. We are perfectly trapped inside $A$!
  - The DFS floods everything inside $A$ (because it's strongly connected internally) and stops exactly at its boundary. Once $A$ is isolated, the algorithm moves to the next highest time (which is $B$) and traps itself inside $B$.
