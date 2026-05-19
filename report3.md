# Assignment 3 - Design and Analysis of Algorithms

## Question 1: Skier–Ski Assignment Problem
**Algorithm 1:** (Greedy by Minimum Difference)
- **Status:** **Incorrect**.
- **Counterexample:** Consider skiers of heights $\{0, 10\}$ and skis of heights $\{4, 5\}$.
  - Algorithm 1 pairs the minimum difference: Skier $10$ with Ski $5$ (diff $5$) or Skier $0$ with Ski $4$ (diff $4$). It pairs Skier $0$ with Ski $4$. 
  - The remaining pair is Skier $10$ and Ski $5$ (diff $5$). 
  - Total absolute difference = $4 + 5 = 9$.
  - **Optimal solution:** Pair Skier $0$ with Ski $5$ (diff $5$) and Skier $10$ with Ski $4$ (diff $6$). Wait, $5+6=11$. 
  - Let's use a better counterexample: Skiers $\{2, 6\}$, Skis $\{4, 8\}$. 
    - Algo 1 pairs $(6, 4)$ with diff $2$. Remaining is $(2, 8)$ with diff $6$. Sum = $8$.
    - Optimal pairs $(2, 4)$ diff $2$ and $(6, 8)$ diff $2$. Sum = $4$. Algorithm 1 fails.

**Algorithm 2:** (Greedy by Sorting)
- **Status:** **Correct**.
- **Proof by Exchange Argument:** Assume an optimal assignment exists where the sorted order is violated. This means there is a pair of skiers $p_i \le p_j$ assigned to skis $s_{\sigma(i)} > s_{\sigma(j)}$.
  The cost contribution of these two is $|p_i - s_{\sigma(i)}| + |p_j - s_{\sigma(j)}|$.
  If we swap their skis, the new cost is $|p_i - s_{\sigma(j)}| + |p_j - s_{\sigma(i)}|$.
  Since $p_i \le p_j$ and $s_{\sigma(j)} < s_{\sigma(i)}$, basic absolute value inequalities confirm that "uncrossing" these pairings strictly minimizes the sum: $|p_i - s_{\sigma(j)}| + |p_j - s_{\sigma(i)}| \le |p_i - s_{\sigma(i)}| + |p_j - s_{\sigma(j)}|$.
  By repeating this exchange, any optimal solution can be transformed into the sorted greedy solution without increasing the cost. Thus, Algorithm 2 is optimal.

**Pseudocode:**
```text
function assignSkis(skiers, skis):
    sort(skiers)
    sort(skis)
    sum_diff = 0
    for i from 0 to skiers.length - 1:
        sum_diff += abs(skiers[i] - skis[i])
    return sum_diff
```
- **Time Complexity:** $O(n \log n)$ due to sorting.
- **Space Complexity:** $O(1)$.

---

## Question 2: Job Scheduling with Release Times and Deadlines
**Warm-up Problem (Fixed Machine Intervals):**
- **Algorithm:** Earliest Deadline First (EDF). Sort available machine time intervals chronologically. At each available $1$-unit interval $t$, assign the uncompleted job that is currently available ($r_j \le t$) and has the **earliest deadline** $d_j$.
- **Exchange Argument:** Assume the optimal schedule places job $A$ before job $B$ where $A$ has a later deadline ($d_A > d_B$) and both are available. Since $B$ is scheduled later and still finishes before its earlier deadline $d_B$, swapping $A$ and $B$ guarantees both still finish before their respective deadlines. Thus, the greedy choice never degrades the optimal solution.

**Main Problem (Minimizing Machine Power-on Intervals of length L):**
- **Algorithm:** Sort the jobs primarily by their deadlines $d_j$ in ascending order. Iterate through the sorted jobs. For the first uncompleted job $j$, it must be scheduled by $d_j - 1$. To maximize overlap for future jobs, turn the machine on for the interval $[d_j - L, d_j]$. Schedule as many valid jobs as possible in this $L$-length window (up to $L$ jobs, prioritizing earliest deadlines). Repeat for the next uncompleted job.
- **Exchange Argument:** Suppose the optimal solution places an interval differently. If it shifts the interval earlier, it covers job $j$ but potentially misses jobs further to the right. By aligning the right endpoint of the interval exactly with the critical deadline $d_j$, the greedy algorithm mathematically maximizes the intersection with future job release windows without failing the current job. Any valid optimal interval can be "shifted right" to match the greedy choice without invalidating job $j$.

---

## Question 3: Gas Station Refueling Strategy
**Goal:** Minimize the *total time spent stopped for gas*.
The prompt states: *"If you stop to fill your tank... you spend $V/r$ minutes refueling"* (Time is strictly proportional to volume pumped). 
Because total gas consumed is fixed (Distance $\times F$), the total time spent refueling is strictly dependent on the total volume of gas pumped. To minimize time, we must end the trip with exactly $0$ liters of gas left in the tank.

**Algorithm 1:** (Fill just enough to reach the next station)
- **Status:** **Correct**.
- **Proof:** This algorithm ensures that upon arriving at destination $B$, the tank is exactly empty. The total gas pumped precisely equals the minimum gas inherently required to traverse the highway. No excess gas is ever pumped, mathematically minimizing the time $V/r$. Any exchange/deviation that pumps more gas would linearly increase the time penalty.

**Algorithm 2:** (Stop only when empty, fill completely)
- **Status:** **Incorrect**.
- **Counterexample:** If you fill the tank completely at the final gas station before $B$, but $B$ is only $5$ km away, you will arrive at $B$ with a massive surplus of gas. Because you pumped excess gas that wasn't strictly necessary for the trip, you spent extra, unrecoverable time at the pump.

---

## Question 4: Minimum Unit Interval Cover
**Algorithm (a):** (Greedily pick interval covering MAX points)
- **Status:** **Incorrect**.
- **Counterexample:** Points at $\{0.0, 0.9, 1.0, 1.9, 2.0\}$. 
  - Algo (a) picks $[0.9, 1.9]$ because it covers 3 points: $\{0.9, 1.0, 1.9\}$. Remaining points are $\{0.0, 2.0\}$. It then needs two more intervals to cover them, totaling **3** intervals.
  - **Optimal:** $[0.0, 1.0]$ covers $\{0.0, 0.9, 1.0\}$ and $[1.1, 2.1]$ covers $\{1.9, 2.0\}$. Total is **2** intervals.

**Algorithm (b):** (Pick leftmost point, cover $[a_j, a_j+1]$)
- **Status:** **Correct**.
- **Proof by Exchange Argument:** Let the leftmost uncovered point be $a_1$. Any valid optimal solution must cover $a_1$ with some interval $[x, y]$. Since it covers $a_1$, $x \le a_1 \le y \le x+1$. If we replace this optimal interval with the greedy interval $[a_1, a_1+1]$, we shift the coverage window to the right. Because $a_1$ is the leftmost point, shifting right discards empty space to the left and can only potentially cover *more* points to the right. Thus, swapping the optimal interval for the greedy one will never require more intervals.

**Pseudocode:**
```text
function minIntervals(points):
    sort(points)
    count = 0
    i = 0
    while i < points.length:
        count += 1
        end_of_interval = points[i] + 1
        // Skip all points covered by this interval
        while i < points.length and points[i] <= end_of_interval:
            i += 1
    return count
```
- **Time Complexity:** $O(n \log n)$ for sorting.
- **Space Complexity:** $O(1)$.

---

## Question 5: Integer Knapsack Problem (Unbounded)
**Algorithm Logic:**
This is the Unbounded Knapsack problem where duplicates are permitted. We use a 1D Dynamic Programming array where `dp[w]` stores the maximum value achievable with exactly capacity `w`. For every capacity from $1$ to $C$, we evaluate adding each item type.

**Pseudocode:**
```text
function unboundedKnapsack(C, sizes, values):
    dp = array of size C + 1 initialized to 0
    
    for w from 1 to C:
        for i from 0 to sizes.length - 1:
            if sizes[i] <= w:
                dp[w] = max(dp[w], dp[w - sizes[i]] + values[i])
                
    return dp[C]
```
**Complexity:**
- **Time Complexity:** $O(n \cdot C)$.
- **Space Complexity:** $O(C)$ for the 1D DP array.

---

## Question 6: Box Stacking
**Algorithm Logic:**
A dynamic programming approach similar to Longest Increasing Subsequence (LIS).
Since boxes can be rotated, each box yields up to 3 different valid base permutations $(length, width, height)$. We generate all $3n$ permutations, ensuring $length > width$ for standardized comparison. We sort these $3n$ boxes descending by their base area. Let `dp[i]` be the maximum stack height ending with box $i$ on top.

**Pseudocode:**
```text
function maxStackHeight(boxes):
    rotations = generate all 3 rotations per box (make length > width)
    sort rotations descending by base area (length * width)
    
    dp = array of size 3n
    for i from 0 to 3n - 1: dp[i] = rotations[i].height
    
    for i from 1 to 3n - 1:
        for j from 0 to i - 1:
            if rotations[i].length < rotations[j].length and 
               rotations[i].width < rotations[j].width:
                dp[i] = max(dp[i], dp[j] + rotations[i].height)
                
    return max(dp)
```
**Complexity:**
- **Time Complexity:** $O(n^2)$ due to the nested LIS loops over $3n$ elements.
- **Space Complexity:** $O(n)$ to store the augmented boxes and DP array.

---

## Question 7: Optimal Strategy for a Game (Coins in a row)
**Algorithm Logic:**
We use a minimax Dynamic Programming approach. Let `dp[i][j]` represent the maximum guaranteed value a player can extract from the sub-array of coins $i$ to $j$. 
If Player 1 takes `v[i]`, Player 2 will optimally force Player 1 into the worst-case remaining state `min(dp[i+2][j], dp[i+1][j-1])`.
If Player 1 takes `v[j]`, Player 2 forces them into `min(dp[i+1][j-1], dp[i][j-2])`.

**Pseudocode:**
```text
function maxCoinGame(v):
    n = v.length
    dp = 2D array of size n x n initialized to 0
    
    for gap from 0 to n - 1:
        for i from 0 to n - gap - 1:
            j = i + gap
            
            x = (i + 2 <= j) ? dp[i+2][j] : 0
            y = (i + 1 <= j - 1) ? dp[i+1][j-1] : 0
            z = (i <= j - 2) ? dp[i][j-2] : 0
            
            take_left = v[i] + min(x, y)
            take_right = v[j] + min(y, z)
            
            dp[i][j] = max(take_left, take_right)
            
    return dp[0][n-1]
```
**Complexity:**
- **Time Complexity:** $O(n^2)$ to fill the DP table.
- **Space Complexity:** $O(n^2)$ to store the DP table.

---

## Question 8: Two-Person Traversal of a Sequence of Cities
**Algorithm Logic:**
The cities must be visited chronologically $1 \dots n$. At any point, the next city $k = \max(i, j) + 1$ must be assigned to either Person A (currently at city $i$) or Person B (currently at city $j$). 
Let `dp[i][j]` be the minimum distance cost where Person A's last visited city is $i$ and Person B's last visited city is $j$. Note that at all times, the next city to visit is $\max(i, j) + 1$. Since one of the indices is always the "current max", we can optimize state tracking.

**Pseudocode:**
```text
function minTraversalDistance(dist, n):
    // dp[i][j] initialized to infinity
    dp = 2D array of size (n+1) x (n+1)
    dp[0][0] = 0 // Both start at virtual node 0
    
    for k from 0 to n - 1: // k is the highest city visited so far
        for i from 0 to k:
            // State: One person is at 'k', the other is at 'i'. 
            // The next city to assign is 'k + 1'.
            
            // Assign k+1 to the person at k:
            dp[k+1][i] = min(dp[k+1][i], dp[k][i] + dist[k][k+1])
            
            // Assign k+1 to the person at i:
            dp[k+1][k] = min(dp[k+1][k], dp[k][i] + dist[i][k+1])
            
    // Find min cost where all cities are visited (one person is at n)
    min_dist = infinity
    for i from 0 to n - 1:
        min_dist = min(min_dist, dp[n][i])
        
    return min_dist
```
*(Note: `dist[0][x] = 0` since the first city assigned effectively acts as their starting point without penalty).*
**Complexity:**
- **Time Complexity:** $O(n^2)$ since we iterate `k` and `i < k`.
- **Space Complexity:** $O(n^2)$ for the DP table, which can be optimized to $O(n)$ by only storing the current row `k`.
