# Master Summary: Approximation Algorithms

When a problem is NP-Hard, we abandon the hope of finding a perfect (optimal) solution in polynomial time. Instead, we use **Approximation Algorithms**—algorithms that are mathematically guaranteed to find a solution that is "close" to the optimal, while running extremely fast.

---

## 1. The Core Principle: The Approximation Ratio ($\rho$)
An algorithm is a **$\rho$-approximation algorithm** if its output is always within a factor of $\rho$ of the true optimal solution.

- **For Minimization Problems:** $\frac{Cost(Algorithm)}{Cost(Optimal)} \le \rho$ (where $\rho \ge 1$)
  *(Example: A 2-approximation means our algorithm will never produce a cost worse than exactly double the optimal).*
- **For Maximization Problems:** $\frac{Cost(Optimal)}{Cost(Algorithm)} \le \rho$

**The Golden Rule of Proofs:** Since finding the true Optimal ($OPT$) is impossible (it's NP-Hard!), we mathematically prove our bounds by comparing our algorithm to an **absolute lower/upper bound** that we know $OPT$ is restricted by.

---

## 2. Load Balancing (Job Scheduling)
**The Problem:** Distribute $N$ jobs (with durations $t_i$) across $M$ identical machines to minimize the "makespan" (the time when the absolute last job finishes).

### A. Simple Greedy (List Scheduling)
- **Algorithm:** Iterate through the jobs. Assign the next job to the machine that currently has the lightest load.
- **The Bounds:** 
  1. $OPT \ge \frac{1}{M} \sum t_i$ (Average load).
  2. $OPT \ge \max(t_i)$ (The single largest job).
- **The Guarantee:** **2-Approximation**. 
- *Proof Intuition:* Let $L$ be our makespan, and let job $j$ be the final job to finish on the busiest machine. Before job $j$ was assigned, that machine had the lightest load, which means every other machine was at least that full. Thus, the load before job $j$ must be $\le$ the average load ($\le OPT$). The duration of job $j$ itself is also $\le OPT$. Therefore, $Total \le OPT + OPT = 2 \cdot OPT$.

### B. Longest Processing Time First (LPT)
- **Algorithm:** Sort the jobs in **descending order** (longest first). Then do the same greedy assignment.
- **The Guarantee:** **3/2-Approximation** (Specifically $\frac{4}{3} - \frac{1}{3M}$). 
- *Intuition:* Scheduling the massive jobs first avoids the fatal flaw of dropping a massive block onto a machine right at the very end of the schedule.

---

## 3. Vertex Cover
**The Problem:** Find the smallest set of vertices such that every single edge in the graph touches at least one vertex in the set.

- **Algorithm:** Find a "Maximal Matching" (pick an arbitrary edge, add BOTH its endpoints to your cover, delete all edges touching those two endpoints. Repeat until no edges remain).
- **The Guarantee:** **2-Approximation**.
- *Proof Intuition:* We selected a set of edges that share absolutely no vertices (a matching). To cover just these specific isolated edges, the true $OPT$ MUST pick at least one endpoint from each of them. Our algorithm picked exactly TWO endpoints from each of them. Thus, we picked exactly twice as many vertices as the absolute mathematical minimum required for those edges. $Cost \le 2 \cdot OPT$.

---

## 4. Traveling Salesperson Problem (TSP)
**The Problem:** Find the shortest possible cycle that visits every vertex exactly once.

- **Constraint:** We assume the **Triangle Inequality** holds ($Distance(A \to C) \le Distance(A \to B) + Distance(B \to C)$). This means taking a direct route is always faster than taking a detour.
- **Algorithm (The MST Approach):**
  1. Compute the Minimum Spanning Tree (MST) of the graph.
  2. Do a Depth-First Search (DFS) or Preorder Walk of the MST.
  3. Form a tour based on the walk, directly "skipping" vertices you've already visited.
- **The Guarantee:** **2-Approximation**.
- *Proof Intuition:* If you take an optimal TSP cycle and remove one edge, you get a spanning tree. Therefore, $Weight(MST) \le Weight(TSP\_OPT)$. If we walk down the MST and walk back up, that path is $2 \cdot Weight(MST)$. By skipping already-visited nodes (taking direct shortcuts), the Triangle Inequality guarantees our distance only shrinks. Thus, $Total \le 2 \cdot MST \le 2 \cdot OPT$.

---

## 5. Set Cover
**The Problem:** Given a universe of elements and a collection of subsets, pick the minimum number of subsets to cover all elements.
- **Algorithm:** Greedily pick the subset that covers the **maximum number of uncovered elements**.
- **The Guarantee:** **$O(\ln N)$-Approximation** (Logarithmic bound).
- *Intuition:* Unlike the previous algorithms that guarantee constant factors (like 2x), Set Cover's greedy approach only guarantees that your cost won't exceed $OPT \times \ln(N)$. This is actually proven to be the best possible bound unless P = NP.

---

## 6. Polynomial-Time Approximation Schemes (PTAS)
A PTAS allows us to specify a target error bound $\epsilon > 0$. The algorithm guarantees a $(1 + \epsilon)$-approximation. If you want a 1% error ($\epsilon = 0.01$), it will do it, but the runtime will increase exponentially with respect to $\frac{1}{\epsilon}$.

### Example: The Knapsack FPTAS
- **The Problem:** 0-1 Knapsack is NP-Hard due to exact DP scaling with massive capacities or massive values.
- **The Scheme:** We artificially "round down" the profit values of the items by dividing them by a scaling factor and ignoring the decimals. 
- **The Guarantee:** By deliberately losing a tiny bit of precision (the truncated decimals), we collapse the massive array dimensions of the DP table, making it run in extremely fast polynomial time, while guaranteeing the final value is within $(1 + \epsilon)$ of the true optimum!
