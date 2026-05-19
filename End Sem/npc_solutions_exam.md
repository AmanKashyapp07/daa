# Formal Exam-Style Proofs: NP-Complete Reductions

To fetch full marks on an exam, every NP-Completeness proof must follow a strict three-part structure:
1. **Proof of NP:** State the certificate and verify it runs in polynomial time.
2. **The Reduction:** Explicitly map the Known Problem to the Target Problem in polynomial time.
3. **Correctness ($\iff$):** Prove the forward ($\Rightarrow$) and backward ($\Leftarrow$) logic mathematically.

---

## 1. DOUBLE-SAT is NP-Complete (Reduction from SAT)
**Target:** DOUBLE-SAT ($\psi$ has $\ge 2$ satisfying assignments)
**Known:** SAT ($\psi$ has $\ge 1$ satisfying assignment)

**1. DOUBLE-SAT $\in$ NP:**
A certificate is a truth assignment to the variables. We can evaluate the finite boolean formula $\psi$ under this assignment in $O(N)$ polynomial time.

**2. Polynomial Reduction:**
Given a SAT formula $\psi$, we construct a new formula $\psi' = \psi \wedge (y \vee \neg y)$, where $y$ is a completely new dummy variable. This construction adds a constant number of logical gates and takes $O(1)$ polynomial time.

**3. Correctness ($\iff$):**
- **($\Rightarrow$):** If $\psi$ has a valid satisfying assignment $A$, then for the new formula $\psi'$, we can assign $A \cup \{y=True\}$ and $A \cup \{y=False\}$. Both are valid because $(y \vee \neg y)$ is a tautology. Thus, $\psi'$ strictly has $\ge 2$ satisfying assignments.
- **($\Leftarrow$):** If $\psi'$ has $\ge 2$ satisfying assignments, it must evaluate to True. Because the appended clause $(y \vee \neg y)$ is universally True, the formula's truth value depends exclusively on $\psi$. Therefore, $\psi$ must have at least 1 valid assignment.

---

## 2. Weighted Vertex Cover (WVC) is NP-Complete (Reduction from VC)
**Target:** WVC (Cover of total weight $\le k$)
**Known:** VC (Cover of total size $\le k$)

**1. WVC $\in$ NP:**
A certificate is a subset of vertices $V'$. We can sum their weights to verify $W \le k$, and iterate over all edges $E$ to ensure every edge has at least one endpoint in $V'$. Both take polynomial time.

**2. Polynomial Reduction:**
Given an instance of Vertex Cover $(G, k)$, we map it to WVC $(G', w, k')$ by setting $G' = G$, $k' = k$, and assigning an explicit weight $w(v) = 1$ for every vertex $v \in V$. This mapping loop takes $O(|V|)$ polynomial time.

**3. Correctness ($\iff$):**
Because the weight of every individual vertex is precisely $1$, the total weight of any selected subset $V'$ is mathematically identical to the total number of vertices in $V'$. Therefore, a valid vertex cover of weight $\le k$ exists in $G'$ if and only if a valid vertex cover of size $\le k$ exists in $G$.

---

## 3. CLIQUE is NP-Complete (Reduction from HALF-CLIQUE)
**Target:** CLIQUE (Find clique of size $k$)
**Known:** HALF-CLIQUE (Find clique of size $|V|/2$)

**1. CLIQUE $\in$ NP:**
A certificate is a subset of $k$ vertices. We can verify if every pair of vertices in this subset is connected by an edge in $O(k^2)$ polynomial time.

**2. Polynomial Reduction:**
Given a HALF-CLIQUE instance $G(V, E)$, we map it to a CLIQUE instance $(G', k)$ by setting $G' = G$ and defining the parameter $k = |V|/2$. This assignment takes $O(1)$ time.

**3. Correctness ($\iff$):**
By explicitly restricting the arbitrary parameter $k$ to strictly equal $|V|/2$, the CLIQUE solver is perfectly evaluating the exact bounds of the HALF-CLIQUE problem. Thus, a YES instance occurs in CLIQUE if and only if a YES instance occurs in HALF-CLIQUE.

---

## 4. HALF-CLIQUE is NP-Complete (Reduction from CLIQUE)
**Target:** HALF-CLIQUE (Find clique of size $|V|/2$)
**Known:** CLIQUE (Find clique of size $k$)

**1. HALF-CLIQUE $\in$ NP:**
A certificate is a subset of $|V|/2$ vertices. We can verify if every pair is connected by an edge in $O(|V|^2)$ polynomial time.

**2. Polynomial Reduction:**
Given a CLIQUE instance $(G, k)$ where $|V| = m$, we construct a new graph $G'$ with total nodes $n$:
- **If $k < m/2$:** We add $m - 2k$ new vertices to $G$. We draw edges connecting these new vertices to every original vertex in $G$, and to each other (forming a complete graph extension). The new total node count is $n = 2m - 2k$.
- **If $k > m/2$:** We add $2k - m$ entirely isolated vertices (degree 0) to $G$. The new total node count is $n = 2k$.
This construction processes a maximum of $O(V^2)$ edges, which is polynomial.

**3. Correctness ($\iff$):**
- **Case 1 ($k < m/2$):** The HALF-CLIQUE target is $n/2 = m - k$. If $G$ has a $k$-clique, it perfectly combines with the $m-2k$ fully connected new vertices to form a clique of size $k + m - 2k = m - k = n/2$. Conversely, if $G'$ has an $n/2$-clique, at most $m-2k$ can come from the new vertices, meaning at least $k$ vertices must come directly from $G$, forming a $k$-clique in $G$.
- **Case 2 ($k > m/2$):** The HALF-CLIQUE target is $n/2 = k$. If $G$ has a $k$-clique, $G'$ intrinsically contains it. Conversely, if $G'$ has an $n/2$-clique (which equals $k$), absolutely none of the new vertices can be part of it because they are fully isolated (degree 0). Thus, the entire $k$-clique must belong to the original graph $G$.

---

## 5. KNAPSACK is NP-Complete (Reduction from SUBSET-SUM)
**Target:** KNAPSACK (Subset with Total Weight $\le W$ and Total Value $\ge V$)
**Known:** SUBSET-SUM (Subset summing to exactly $t$)

**1. KNAPSACK $\in$ NP:**
A certificate is a subset of items. We can linearly sum their weights and values in $O(N)$ polynomial time and logically verify $w \le W$ and $v \ge V$.

**2. Polynomial Reduction:**
Given a SUBSET-SUM instance containing a set $S$ and target $t$. We map this to KNAPSACK by creating an item for every element $s_i \in S$, setting both its weight and value identical to $s_i$ ($w_i = v_i = s_i$). We establish the knapsack boundaries as $W = t$ and $V = t$. This mapping is $O(|S|)$.

**3. Correctness ($\iff$):**
The KNAPSACK conditions demand a selection of items whose aggregate sum $X$ simultaneously satisfies $X \le t$ (Weight constraint) and $X \ge t$ (Value constraint). The only mathematical possibility that satisfies both bounds is $X = t$. Therefore, a valid Knapsack subset exists if and only if a subset summing exactly to $t$ exists in the original set $S$.

---

## 6. Class Scheduling is NP-Complete (Reduction from k-Colouring)
**Target:** Scheduling (Assign $n$ classes into $k$ rooms with no overlapping time slots)
**Known:** k-Colouring (Assign $k$ colours to $V$ vertices with no adjacent vertices sharing a colour)

**1. Scheduling $\in$ NP:**
A certificate is an array mapping each class to a specific room. We can iterate through each room and verify no time constraints overlap in polynomial time.

**2. Polynomial Reduction:**
Given a Graph $G(V, E)$ and integer $k$. We map this to Scheduling by creating one "class" for every vertex $v \in V$. For every edge $(u, v) \in E$, we explicitly define the time slots for class $u$ and class $v$ such that they directly overlap. We set the available rooms identically to $k$. This mapping runs in $O(|V| + |E|)$ time.

**3. Correctness ($\iff$):**
By structural definition, two classes possess overlapping time slots if and only if their representative vertices share a physical edge. The constraint "no overlapping classes can share a room" is mathematically identical to the constraint "no adjacent vertices can share a color". Thus, a valid schedule into $k$ rooms exists if and only if a valid $k$-colouring of the graph exists.

---

## 7. Multi-Path is NP-Complete (Reduction from SUBSET-SUM)
**Target:** Multi-Path (Find a path from $v \to v$ repeating no edges with distance exactly $k$)
**Known:** SUBSET-SUM (Subset summing to exactly $t$)

**1. Multi-Path $\in$ NP:**
A certificate is an ordered sequence of edges. We can verify that no edge is repeated, that the sequence forms a closed loop, and that the sum of edge weights equals $k$, all in $O(|E|)$ polynomial time.

**2. Polynomial Reduction:**
Given a SUBSET-SUM instance $(X, t)$, we construct a graph $G$ containing exactly one single vertex $v$. For every numeric element $x_i \in X$, we add a self-loop edge $e_i$ directly from $v \to v$, assigning it a physical weight of $x_i$. We set the target path distance $k = t$. Construction takes $O(|X|)$ polynomial time.

**3. Correctness ($\iff$):**
- **($\Rightarrow$):** If a valid subset $X'$ summing to $t$ exists, a path traversing the self-loops corresponding to the elements in $X'$ will start at $v$, end at $v$, repeat no edges, and sum to exactly $t$ (which equals $k$).
- **($\Leftarrow$):** If a valid path of length $k$ exists, it must structurally consist of a sequence of non-repeating self-loops (since only one vertex exists). The sum of these loop weights is $k$. Because each edge weight maps to an element in $X$, these chosen edges define a distinct subset of numbers in $X$ that sum to exactly $t$.
