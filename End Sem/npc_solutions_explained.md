# NP-Complete Problem Set: Intuition Guide & Solutions

This report breaks down the 7 NP-Complete reduction problems from your problem set. Instead of dense mathematical proofs, this guide focuses on **"The Trick"**—the core intuitive logic you need to memorize to understand *why* the reduction works.

Remember the golden rule of reductions: To prove a *Target Problem* is NP-Complete, we take a *Known Hard Problem* and trick the Target Problem's solver into solving it for us.

---

## 1. SAT $\to$ DOUBLE-SAT
**The Goal:** Prove that finding *two* satisfying assignments is NP-Complete by reducing from standard SAT (finding just *one* assignment).

**The Intuition (The Dummy Variable Trick):** 
If we have a standard SAT formula $\psi$ and we want to trick a DOUBLE-SAT solver into answering for us, we just add a completely useless dummy variable $y$. 
We change the formula to: $\psi \text{ AND } (y \text{ OR NOT } y)$.
Because $(y \text{ OR NOT } y)$ is always mathematically true, it has zero effect on whether $\psi$ is solvable. However, $y$ can exist in exactly 2 states (True or False). 
So, if the original formula $\psi$ had exactly 1 valid solution, our new formula now inherently has **exactly 2** valid solutions (one where $y$ is True, one where $y$ is False). We successfully tricked the DOUBLE-SAT solver into solving SAT!

---

## 2. Vertex Cover (VC) $\to$ Weighted Vertex Cover (WVC)
**The Goal:** Prove that finding a vertex cover with restricted weights is NP-Complete.

**The Intuition (The Restriction Trick):** 
Weighted Vertex Cover is just the original Vertex Cover problem with extra features (weights). To reduce from VC to WVC, we just turn off the extra features! 
We set the weight of every single vertex to exactly $1$. Now, asking the WVC solver to find a cover with "total weight $\le k$" is mathematically identical to asking for a cover of "size $\le k$". Since WVC can effortlessly mimic VC, it must be at least as hard.

---

## 3. HALF-CLIQUE $\to$ CLIQUE
**The Goal:** Prove standard CLIQUE is NP-Complete by reducing from HALF-CLIQUE (finding a clique of exactly size $|V|/2$).

**The Intuition (The Restriction Trick):** 
Just like Question 2, standard CLIQUE is more powerful than HALF-CLIQUE because you can ask for a clique of *any* size $k$. To prove it's hard, just set $k = |V|/2$. Now the CLIQUE solver is perfectly mimicking the HALF-CLIQUE problem.

---

## 4. CLIQUE $\to$ HALF-CLIQUE *(The Hardest Problem)*
**The Goal:** Prove HALF-CLIQUE is NP-Complete. You have a solver that **only** works if you ask it for a clique of exactly half the nodes. But you have a graph $G$ with $m$ nodes and want to find a clique of an arbitrary size $k$. 

**The Intuition (The Padding Trick):** 
You have to manually "pad" the graph with fake dummy nodes until your arbitrary target $k$ magically becomes exactly half of the total node count $n$.
- **Scenario A ($k$ is too small, $k < m/2$):** You need the solver to look for a *bigger* clique. So you inject a bunch of fake nodes that are perfectly connected to everything (a super-clique). The solver will blindly grab these free fake nodes first, inflating the clique size it finds until the size matches exactly half the graph.
- **Scenario B ($k$ is too big, $k > m/2$):** You need $k$ to represent a *smaller* percentage of the total graph. So, you inject a bunch of completely floating, isolated dummy nodes. Because they have no edges, the solver can never include them in a clique. But because they count towards the total graph size, your target $k$ shrinks in proportion until it equals exactly half.

---

## 5. SUBSET-SUM $\to$ KNAPSACK
**The Goal:** Prove KNAPSACK is NP-Complete.

**The Intuition (The Restriction Trick):** 
KNAPSACK is basically SUBSET-SUM but with two variables per item (Value and Weight) instead of one. To reduce SUBSET-SUM to KNAPSACK, just strip away the complexity:
Force the weight of every item to exactly equal its value ($w = v$). Then, force the target knapsack capacity $W$ to equal the target value requirement $V$. 
Now, you are just looking for a subset of items whose values sum to exactly $V$. The KNAPSACK solver is now just a SUBSET-SUM solver!

---

## 6. k-Colouring $\to$ Class Scheduling
**The Goal:** Prove scheduling $n$ classes into $k$ rooms without time overlaps is NP-Complete.

**The Intuition (The Renaming Trick):** 
These two problems are literally the exact same problem wearing different disguises. You just need to build a translation dictionary:
- Graph Vertices $\to$ Classes.
- Edges (Conflicts) $\to$ Overlapping time slots.
- Colors $\to$ Classrooms.
If the Graph Colouring rules state "Two connected vertices cannot share the same color", the Scheduling rules translate that to "Two classes with overlapping times cannot share the same classroom." Finding a $k$-colouring instantly gives you a $k$-room schedule.

---

## 7. SUBSET-SUM $\to$ Multi-Path
**The Goal:** Prove that finding a path of exact distance $k$ in a graph without repeating edges is NP-Complete.

**The Intuition (The Petal Graph Trick):** 
We need to build a graph where "choosing an edge to walk on" feels exactly like "choosing a number for our subset sum". 
- Create a graph with just ONE single vertex $v$. 
- For every number $x$ in your SUBSET-SUM list, draw an edge that loops directly from $v$ back to $v$, and give it a distance of $x$. (The graph will look like a flower with many petals).
- Because you start and end at $v$, you can choose to walk along any petal, or skip it. If you want to walk a total distance of exactly $k$, you simply pick a subset of these petals whose distances sum to $k$. Thus, finding this path mathematically solves the SUBSET-SUM problem!
