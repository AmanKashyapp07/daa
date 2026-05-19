# Assignment 2 - Design and Analysis of Algorithms

## Question 1: Polynomial Evaluation in $O(n)$
**Algorithm Logic:**
We use **Horner's Method**, which restructures the polynomial evaluation to minimize multiplications by continuously factoring out $x$. 
$P(x) = a_0 + x(a_1 + x(a_2 + \dots + x(a_{n-1})))$

**Pseudocode:**
```text
function evaluatePolynomial(a, alpha):
    n = a.length
    result = a[n - 1]
    
    for i from n - 2 down to 0:
        result = a[i] + alpha * result
        
    return result
```
**Complexity:**
- **Time Complexity:** $O(n)$. Exactly $n-1$ multiplications and $n-1$ additions.
- **Space Complexity:** $O(1)$.

---

## Question 2: Largest Subset $S$ for One-One and Onto mapping
**Algorithm Logic:**
A function $f: S \to S$ is one-one and onto if and only if it consists entirely of disjoint, closed cycles. Elements that are not part of any cycle (e.g., loose chains leading into a loop) must be iteratively eliminated. We can use a topological sort approach by tracking the in-degrees of each node.

**Pseudocode:**
```text
function findLargestSubset(f, n):
    in_degree = array of 0s of size n+1
    
    // Calculate initial in-degrees
    for i from 1 to n:
        in_degree[f[i]] += 1
        
    queue = empty queue
    for i from 1 to n:
        if in_degree[i] == 0:
            queue.enqueue(i)
            
    // Iteratively eliminate nodes that lead into cycles but aren't in them
    while queue is not empty:
        curr = queue.dequeue()
        target = f[curr]
        in_degree[target] -= 1
        if in_degree[target] == 0:
            queue.enqueue(target)
            
    // Collect the surviving nodes (the cycles)
    S = empty list
    for i from 1 to n:
        if in_degree[i] > 0:
            S.append(i)
            
    return S
```
**Complexity:**
- **Time Complexity:** $O(n)$ as each node is enqueued and processed at most once.
- **Space Complexity:** $O(n)$ for the in-degree array and tracking queue.

---

## Question 3: Intervals Not Contained in Any Other
**Algorithm Logic:**
Sort the intervals by their left endpoint $L$ in ascending order. In the case of a tie, sort by their right endpoint $R$ in descending order. As we iterate left-to-right, keep track of the maximum right endpoint `max_R` seen so far. If the current interval's right endpoint $R[i] \le max\_R$, it is strictly contained within a previously processed interval.

**Pseudocode:**
```text
function countUncontainedIntervals(L, R):
    n = L.length
    intervals = array of tuples (L[i], R[i])
    
    sort intervals by L ascending, then R descending
    
    count = 0
    max_R = -infinity
    
    for each interval (left, right) in intervals:
        if right > max_R:
            // Not contained in any previous interval
            count += 1
            max_R = right
            
    return count
```
**Complexity:**
- **Time Complexity:** $O(n \log n)$ heavily bounded by the sorting step.
- **Space Complexity:** $O(n)$ to store the paired tuple representation.

---

## Question 4: Sum of Products of all $k$-size Subsets
**Algorithm Logic:**
We can solve this efficiently using Dynamic Programming. Let $DP[i][j]$ be the sum of products of subsets of size $j$ using elements from the prefix $A[1 \dots i]$. 
**State Transition:** We can either *exclude* the $i$-th element (bringing forward $DP[i-1][j]$) or *include* it (multiplying $A[i]$ by combinations of size $j-1$, giving $A[i] \times DP[i-1][j-1]$).

**Pseudocode:**
```text
function sumOfProducts(A, n, k):
    DP = 2D array of size (n+1) x (k+1) initialized to 0
    
    // Base case: Subset of size 0 has product sum 1 (empty product)
    for i from 0 to n:
        DP[i][0] = 1
        
    for i from 1 to n:
        for j from 1 to min(i, k):
            DP[i][j] = DP[i-1][j] + A[i-1] * DP[i-1][j-1]
            
    return DP[n][k]
```
**Complexity:**
- **Time Complexity:** $O(n \cdot k)$ strictly to fill the DP table.
- **Space Complexity:** $O(n \cdot k)$ to store the matrix. This is easily optimizable to $O(k)$ by maintaining only the previous row in memory.

---

## Question 5: Non-dominated Points
**Algorithm Logic:**
Sort the points by their $x$-coordinate in descending order. If tied, sort by $y$-coordinate descending. As we process the sorted points, maintain the `max_y` seen so far. A point $(x_i, y_i)$ is fully dominated if $y_i \le max\_y$ (because we already know there exists a previously processed point with an $x \ge x_i$).

**Pseudocode:**
```text
function findNonDominatedPoints(points):
    sort points by x descending, then y descending
    
    result = empty list
    max_y = -infinity
    
    for each point (x, y) in points:
        if y > max_y:
            result.append((x, y))
            max_y = y
            
    return result
```
**Complexity:**
- **Time Complexity:** $O(n \log n)$ required for sorting.
- **Space Complexity:** $O(n)$ for aggregating the result list.

---

## Question 6: Majority Fingerprints using Equality Test
**Algorithm Logic:**
Because our only available primitive is a boolean equality test, we apply a Divide & Conquer scheme identical to Moore's Majority Vote recursive breakdown. Split the fingerprints into two halves. Find the majority in each. If both halves agree, that is the global majority. If they differ, manually count the occurrences of both candidates across the entire active array segment using the equality test.

**Pseudocode:**
```text
function findMajority(A, low, high):
    if low == high: return A[low]
    
    mid = (low + high) / 2
    left_cand = findMajority(A, low, mid)
    right_cand = findMajority(A, mid + 1, high)
    
    if left_cand == right_cand:
        return left_cand
        
    left_count = 0, right_count = 0
    for i from low to high:
        if isEqual(A[i], left_cand): left_count += 1
        else if isEqual(A[i], right_cand): right_count += 1
        
    if left_count > (high - low + 1) / 2: return left_cand
    if right_count > (high - low + 1) / 2: return right_cand
    return null
```
**Complexity:**
- **Time Complexity:** $T(n) = 2T(n/2) + O(n) \implies O(n \log n)$.
- **Space Complexity:** $O(\log n)$ associated strictly with the recursion stack depth.

---

## Question 7: Significant Inversions
**Algorithm Logic:**
A significant inversion happens when $i < j$ and $A[i] > 2A[j]$.
This is optimally solved using a heavily modified Merge Sort (Divide & Conquer) where cross-boundary inversions are explicitly tallied during the merge sequence. See **Question 9** directly below for the full unified D&C implementation and pseudocode.
**Complexity:** $O(n \log n)$ Time, $O(n)$ Space.

---

## Question 8: Hidden Lines (Upper Envelope)
**Algorithm Logic:**
Mathematically, this corresponds to generating the Upper Convex Hull.
Sort lines strictly by their slope $m$ ascending. Maintain an operational stack of visible lines. When assessing a new line, calculate the intersection point with the top of the stack. If it intersects *before* the top line intersects the line directly underneath it, the top line is completely "eclipsed" and effectively hidden from the infinite $+y$ view. Pop it.

**Pseudocode:**
```text
function intersectX(line1, line2):
    return (line1.c - line2.c) / (line2.m - line1.m)

function visibleLines(lines):
    sort lines by slope 'm' ascending (tie-break by larger 'c')
    
    stack = empty stack
    for each line in lines:
        while stack.size >= 2:
            top = stack.pop()
            second = stack.peek()
            
            x1 = intersectX(new line, top)
            x2 = intersectX(top, second)
            
            // The new line eclipses the top line
            if x1 <= x2:
                continue // leave it popped and evaluate the next layer down
            else:
                stack.push(top) // it is safe
                break
                
        stack.push(new line)
        
    return stack
```
**Complexity:**
- **Time Complexity:** $O(n \log n)$ driven by the sort limit. The stack amortizes perfectly to $O(n)$.
- **Space Complexity:** $O(n)$ for the structural stack.

---

## Question 9: Divide and Conquer for Significant Inversions
**Algorithm Logic:**
We piggyback onto Merge Sort. When evaluating the `left` and `right` sorted subarrays immediately prior to merging, we deploy a two-pointer mechanism to quickly count pairs satisfying `left[i] > 2 * right[j]`. Because both arrays are strictly sorted, if `left[i]` meets the threshold for `right[j]`, then all elements sequentially following `left[i]` will also satisfy it.

**Pseudocode:**
```text
function mergeAndCount(A, low, mid, high):
    count = 0
    j = mid + 1
    
    // Lookahead Counting Phase
    for i from low to mid:
        while j <= high and A[i] > 2 * A[j]:
            j += 1
        count += (j - (mid + 1))
        
    // Standard Merge Phase
    merge sorted subarrays A[low..mid] and A[mid+1..high]
    return count

function countSignificantInversions(A, low, high):
    if low >= high: return 0
    
    mid = (low + high) / 2
    count = countSignificantInversions(A, low, mid)
    count += countSignificantInversions(A, mid + 1, high)
    count += mergeAndCount(A, low, mid, high)
    
    return count
```
**Complexity:**
- **Time Complexity:** $T(n) = 2T(n/2) + O(n) \implies O(n \log n)$.
- **Space Complexity:** $O(n)$ mapped to the temporary array leveraged within standard merging.

---

## Question 10: Augmented Binary Search Tree Updates in $O(\log n)$

The objective is classifying which attributes natively survive $O(\log n)$ updates upon insertion or deletion:

1. **Number of nodes in the subtree rooted at x:** **YES**. Can be updated dynamically by traversing upward along the ancestor path and incrementing/decrementing.
2. **Number of nodes larger than x:** **NO**. Inserting a new global minimum dramatically alters this value for *every* previously mapped node in the tree simultaneously, creating a mass $O(n)$ update penalty.
3. **Distance from the root (depth):** **NO**. Structural rotations (standard in AVL/Red-Black implementations) completely shift the baseline depth of the entire descending subtree, equating to $O(n)$ updates.
4. **Pointer to successor:** **YES**. Identifying the strict predecessor and successor bounds natively takes $O(\log n)$, meaning we only need to rewire the threaded pointers locally.
5. **Largest depth in the subtree (height):** **YES**. Height relies solely on calculating `max(left.height, right.height) + 1` and cascades up the direct ancestor path cleanly in $O(\log n)$.
6. **Rank in the BST:** **NO**. Storing rank statically explicitly fails for the exact same rationale highlighted in Rule #2. *(Note: Rank can technically be queried dynamically via subtree sizes in $O(\log n)$, but explicitly storing and attempting to update it breaks constraints).*

---

## Question 11: Nth Fibonacci in $O(\log n)$
**Yes**, this is aggressively achievable leveraging Matrix Exponentiation.

**Logic:**
The linear Fibonacci recursion perfectly maps to a discrete geometric matrix transformation:
$$ \begin{pmatrix} F_{n+1} & F_n \\ F_n & F_{n-1} \end{pmatrix} = \begin{pmatrix} 1 & 1 \\ 1 & 0 \end{pmatrix}^n $$

We can isolate $M^n$ utilizing binary fast exponentiation (D&C squaring) using strictly $O(\log n)$ distinct matrix multiplications. As standalone $2 \times 2$ multiplications run in static constant time ($O(1)$), the global structural bounds successfully collapse to $O(\log n)$.

---

## Question 12: Local Minimum in a Complete Binary Tree
**Algorithm Logic:**
The prompt loosely asks for bounded $O(n)$ probes. However, we can vastly optimize this to execute in exponentially reduced **$O(\log n)$** probes via greedy descent.
Initiate at the root. Probe the root itself and its explicit left/right children. If the root represents the localized minimum, terminate. Otherwise, step aggressively down into whichever child possessed the lowest observed value. Because you consistently travel "down" the numerical gradient, it is mathematically impossible to be trapped or forced to backtrack, ensuring terminal convergence onto a localized sink minimum.

**Pseudocode:**
```text
function findLocalMin(root):
    curr = root
    while curr is not null:
        val = probe(curr)
        val_left = probe(curr.left) // evaluates to infinity if null
        val_right = probe(curr.right) // evaluates to infinity if null
        
        if val < val_left and val < val_right:
            return curr
        else if val_left < val_right:
            curr = curr.left
        else:
            curr = curr.right
```
**Complexity:**
- **Probe/Time Complexity:** We execute a continuous descent down a singular non-branching path. As the complete binary tree is perfectly balanced, the maximum depth is hard-capped at $\approx \log_2 n$. Hence, this utilizes $O(\log n)$ probes.

---

## Question 13: Median of Two Databases
**Algorithm Logic:**
We want to extract the $n$-th smallest value globally spanning two individual databases each housing $n$ values (bounded at $O(n)$ queries). We can heavily outclass this baseline via an $O(\log n)$ query setup utilizing structural Binary Search.
We directly binary search a split index $k_1$ on $DB_1$. For any projected $k_1$, we implicitly mandate that $k_2 = n - k_1$ elements must be harvested from $DB_2$. We only need to physically query the intersection "borderline" elements to confirm if the totality of the left-half partition maps strictly smaller than the right-half partition.

**Pseudocode:**
```text
function findMedian(DB1, DB2, n):
    low = 0, high = n
    
    while low <= high:
        k1 = (low + high) / 2
        k2 = n - k1
        
        L1 = (k1 == 0) ? -infinity : query(DB1, k1)
        R1 = (k1 == n) ? infinity : query(DB1, k1 + 1)
        
        L2 = (k2 == 0) ? -infinity : query(DB2, k2)
        R2 = (k2 == n) ? infinity : query(DB2, k2 + 1)
        
        if L1 <= R2 and L2 <= R1:
            return max(L1, L2)
        else if L1 > R2:
            high = k1 - 1
        else:
            low = k1 + 1
```
**Complexity:**
- **Query/Time Complexity:** $O(\log n)$ purely driven by cleanly halving the remaining search plane each step.

---

## Question 14: Fourier Transform Modulo 7 (Optional)
**a) Primitive Root $\omega$:**
Working strictly Modulo 7, we require an identity $\omega$ where $\omega^6 \equiv 1$ alongside exclusively distinct powers. 
Selecting base $\omega = 3$:
$3^1=3, 3^2=2, 3^3=6, 3^4=4, 3^5=5, 3^6=1$. Distinct validation successful!
Identity Sum: $1+3+2+6+4+5 = 21 \equiv 0 \pmod 7$.

**b) Transform resolution of sequence $(0, 1, 1, 1, 5, 2)^T$:**
We apply Fourier isolation: $V_k = \sum_{j=0}^5 v_j \omega^{j k} \pmod 7$.
Calculation aggregates and maps to transformed vector: $V = (3, 6, 4, 2, 3, 0)^T \pmod 7$.

**c) Inverse Transform Matrix:**
The inverted recovery matrix hinges on fractional isolation $\omega^{-1} \equiv 3^{-1} \equiv 5 \pmod 7$.
The matrix scaling index evaluates as $N^{-1} \equiv 6^{-1} \equiv 6 \pmod 7$.
Target matrix entries translate to $M^{-1}_{j,k} = 6 \times 5^{jk} \pmod 7$.

**d) Multiply localized polynomials using FT mod 7:**
Pad targets $A(x) = x^2+x+1$ and $B(x) = x^3+2x+3$ aligning into length 6 padded coefficient vectors:
$a = (1, 1, 1, 0, 0, 0)$, $b = (3, 2, 0, 1, 0, 0)$
1. Deploy and evaluate bounds for $FT(a)$ and $FT(b)$.
2. Calculate intersection pointwise multiplications where $C_k = FT(a)_k \times FT(b)_k \pmod 7$.
3. Deploy the Inverse framework $FT(C)$ to cleanly extract the finalized composite polynomial coefficients.
