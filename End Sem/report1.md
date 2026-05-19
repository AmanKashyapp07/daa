# Assignment 1 - Design and Analysis of Algorithms

## Question 1: Egg Dropping in $O(\log h)$

**Algorithm Logic:**
Since we do not know $h$ (the highest floor from which the egg can be dropped without breaking) and want to find it in $O(\log h)$ drops, we cannot do a standard binary search on the total number of floors. Instead, we find a bounding range for $h$ by exponentially doubling our step size (1, 2, 4, 8, ...). Once the egg breaks at floor $2^k$, we know $h$ lies strictly between $2^{k-1}$ and $2^k$. We then perform a binary search strictly within this bounded range.

**Pseudocode:**
```text
function findHighestFloor():
    if drop(1) breaks:
        return 0
    
    step = 1
    while drop(step) does not break:
        step = step * 2
    
    // Egg broke at 'step', so h is between step/2 and step - 1
    low = step / 2
    high = step - 1
    
    while low <= high:
        mid = low + (high - low) / 2
        if drop(mid) breaks:
            high = mid - 1
        else:
            low = mid + 1
            
    return high
```
**Complexity Analysis:**
- **Time Complexity:** Finding the upper bound takes $\approx \log_2 h$ steps. The binary search range is of size $2^k - 2^{k-1} = 2^{k-1}$, so binary search takes $\approx \log_2(2^{k-1}) \approx \log_2 h$ steps. Total drops = $O(\log h)$.
- **Space Complexity:** $O(1)$

---

## Question 2: Minimum Length Subarray Sum $\ge S$

**Algorithm Logic:**
Since all numbers in the array are positive, the prefix sum array will be strictly increasing. We can compute the prefix sum array in linear time. Then, for each index $i$, we use binary search (`lower_bound`) to find the smallest index $j$ such that the sum from $i$ to $j$ is at least $S$ (i.e., `prefix[j] - prefix[i-1] >= S`). 

**Pseudocode:**
```text
function minSubarrayLen(a, S):
    n = a.length
    prefix = array of size n + 1
    prefix[0] = 0
    for i from 1 to n:
        prefix[i] = prefix[i-1] + a[i-1]
        
    min_len = infinity
    
    for i from 1 to n:
        target = prefix[i-1] + S
        // Binary search for target in prefix array
        j = lower_bound(prefix, i, n, target)
        if j != -1:
            min_len = min(min_len, j - i + 1)
            
    return min_len == infinity ? 0 : min_len
```
**Complexity Analysis:**
- **Time Complexity:** Prefix sum computation takes $O(n)$. Binary search takes $O(\log n)$ and is executed $n$ times. Total Time: $O(n \log n)$. *(Note: This can be optimized to $O(n)$ using a sliding window, but $O(n \log n)$ is explicitly addressed as per the prompt).*
- **Space Complexity:** $O(n)$ to store the prefix sum array.

---

## Question 3: Median of Two Sorted Arrays

**Algorithm Logic:**
To find the median in $O(\log n)$ time, we perform a binary search on the smaller array to find a valid "partition" index. The goal is to partition both arrays such that the left half of the combined elements has the same number of elements as the right half, and every element on the left is smaller than every element on the right.

**Pseudocode:**
```text
function findMedian(A, B):
    n = A.length
    low = 0, high = n
    
    while low <= high:
        partitionA = (low + high) / 2
        partitionB = n - partitionA
        
        maxLeftA = (partitionA == 0) ? -infinity : A[partitionA - 1]
        minRightA = (partitionA == n) ? infinity : A[partitionA]
        
        maxLeftB = (partitionB == 0) ? -infinity : B[partitionB - 1]
        minRightB = (partitionB == n) ? infinity : B[partitionB]
        
        // Check if we found the perfect partition
        if maxLeftA <= minRightB and maxLeftB <= minRightA:
            return (max(maxLeftA, maxLeftB) + min(minRightA, minRightB)) / 2.0
        else if maxLeftA > minRightB:
            high = partitionA - 1
        else:
            low = partitionA + 1
```
**Complexity Analysis:**
- **Time Complexity:** $O(\log n)$ because we are binary searching strictly over the indices of an array of size $n$.
- **Space Complexity:** $O(1)$

---

## Question 4: Two Sum in $O(n \log n)$

**Algorithm Logic:**
First, sort the array. Then, use a two-pointer approach (one pointer at the beginning, one at the end) to find the pair that sums to exactly $S$.

**Pseudocode:**
```text
function twoSum(a, S):
    sort(a) // O(n log n)
    left = 0
    right = a.length - 1
    
    while left < right:
        current_sum = a[left] + a[right]
        if current_sum == S:
            return (a[left], a[right])
        else if current_sum < S:
            left = left + 1
        else:
            right = right - 1
            
    return null // No pair found
```
**Complexity Analysis:**
- **Time Complexity:** Sorting takes $O(n \log n)$. The two-pointer traversal takes strictly $O(n)$. Total Time: $O(n \log n)$.
- **Space Complexity:** $O(1)$ (or $O(\log n)$ overhead depending on the sorting algorithm).

---

## Question 5: Check if $a = b^k$ for $k > 1$

**Algorithm Logic:**
Since $b \ge 2$, the maximum possible value for the exponent $k$ is $\log_2(a)$. We iterate over all possible values of $k \in [2, \log_2 a]$. For each fixed $k$, we perform a binary search to find a base $b$ such that $b^k = a$.

**Pseudocode:**
```text
function isPerfectPower(a):
    max_k = floor(log2(a))
    
    for k = 2 to max_k:
        low = 2
        high = a
        while low <= high:
            mid = low + (high - low) / 2
            power = mid^k
            if power == a:
                return true
            else if power < a:
                low = mid + 1
            else:
                high = mid - 1
                
    return false
```
**Complexity Analysis:**
- **Time Complexity:** There are $O(\log a)$ distinct values of $k$. For each $k$, we do a binary search over at most $O(a)$ values, requiring $O(\log a)$ steps. Computing $mid^k$ takes $O(\log k)$ operations using fast exponentiation. Thus, total time is heavily bounded by $O(\log^3 a)$. This satisfies the requirement of $O(\log^c a)$ for constant $c=3$.
- **Space Complexity:** $O(1)$

---

## Question 6: Land Redistribution

**1. What is the highest feasible value of $f$?**
The maximum feasible value for $f$ occurs when all available land is perfectly and evenly distributed among everyone. Thus, the maximum $f$ is simply the mean average of all landholdings:  
$f_{max} = \frac{\sum_{i=1}^{n} a_i}{n}$

**2. Finding the right value of $c$ for a chosen $f$:**
If we choose an $f \le f_{max}$, we need to dynamically find $c$ such that the total land taken from those with $> c$ hectares perfectly equals the land required to supplement those with $< f$ hectares. We can find $c$ using binary search in the continuous domain $[f, \max(a)]$.

**Pseudocode:**
```text
function findC(a, f):
    land_needed = 0
    for each holding in a:
        if holding < f:
            land_needed += (f - holding)
            
    low = f
    high = max(a)
    
    while high - low > epsilon: // Continuous binary search
        mid_c = (low + high) / 2
        land_taken = 0
        for each holding in a:
            if holding > mid_c:
                land_taken += (holding - mid_c)
                
        if land_taken >= land_needed:
            low = mid_c // 'c' can be larger to take less land
        else:
            high = mid_c // 'c' must be smaller to take more land
            
    return (low + high) / 2
```
**Complexity Analysis:**
- **Time Complexity:** $O(n \log(\frac{\max(a)}{\epsilon}))$ where $\epsilon$ is the tolerated precision error threshold.
- **Space Complexity:** $O(1)$

---

## Question 7: Finding Hidden Treasure in $O(N)$ Distance

**Algorithm Logic:**
To guarantee bounded $O(N)$ total distance traveled across an unknown infinite line, we must use a doubling geometric strategy that alternates directions. We move $+1, -2, +4, -8, +16 \dots$ from the origin, returning to $0$ each time. 

**Pseudocode:**
```text
function findTreasure():
    step = 1
    
    while true:
        move to location (0 + step)
        if detector beeps at any point during the movement:
            return current_location
            
        move back to 0
        step = -2 * step
```
**Complexity Analysis:**
- **Distance Complexity:** If the treasure is at distance $N$, the algorithm will sweep past it when $|step| \ge N$. The total absolute distance traveled is geometrically bounded by $2 \sum_{i=0}^{\lceil\log_2 N\rceil} 2^i = 2(2^{\lceil\log_2 N\rceil + 1} - 1) \approx 8N = O(N)$.
- **Space Complexity:** $O(1)$

---

## Question 8: Recurrences (Master's Theorem & Substitution)

1. $T(n) = T(n/2) + n^3$
   - **Master Theorem:** $a=1, b=2, f(n)=n^3$. Here $\log_b a = \log_2 1 = 0$. Since $f(n) = \Omega(n^{0+\epsilon})$, Case 3 applies.
   - **Complexity:** $\Theta(n^3)$

2. $T(n) = 4T(n/3) + n$
   - **Master Theorem:** $a=4, b=3, f(n)=n$. Here $\log_3 4 \approx 1.26$. Since $f(n) = O(n^{\log_3 4 - \epsilon})$, Case 1 applies.
   - **Complexity:** $\Theta(n^{\log_3 4})$

3. $T(n) = 4T(n/2) + n$
   - **Master Theorem:** $a=4, b=2, f(n)=n$. Here $\log_2 4 = 2$. Since $f(n) = O(n^{2-\epsilon})$, Case 1 applies.
   - **Complexity:** $\Theta(n^2)$

4. $T(n) = 3T(n-1) + 1$
   - **Substitution/Tree:** Expanding gives $T(n) = 3(3T(n-2)+1)+1 = 3^2T(n-2) + 3 + 1 \dots = 3^n T(0) + \sum_{i=0}^{n-1} 3^i$.
   - **Complexity:** $\Theta(3^n)$

5. $T(n) = 16T(n/4) + n^2$
   - **Master Theorem:** $a=16, b=4, f(n)=n^2$. Here $\log_4 16 = 2$. Since $f(n) = \Theta(n^{\log_b a})$, Case 2 applies.
   - **Complexity:** $\Theta(n^2 \log n)$

6. $T(n) = 4T(n/2) + n^2 \log n$
   - **Master Theorem:** $a=4, b=2$. Here $\log_2 4 = 2$. $f(n) = n^2 \log n = \Theta(n^{\log_b a} \log^k n)$ where $k=1$. Extended Case 2 applies.
   - **Complexity:** $\Theta(n^2 \log^2 n)$

---

## Question 9: Max Profit (Stock Buy Sell Once)

**Algorithm Logic:**
Maintain the minimum price seen so far as we iterate strictly forward through the array. For each day, calculate the potential profit if we sold today (current price - minimum price seen so far) and update the global maximum profit.

**Pseudocode:**
```text
function maxProfit(prices):
    if prices.length == 0: return 0
    
    min_price = prices[0]
    max_profit = 0
    
    for i from 1 to prices.length - 1:
        profit = prices[i] - min_price
        if profit > max_profit:
            max_profit = profit
            
        // Keep track of the lowest valley
        if prices[i] < min_price:
            min_price = prices[i]
            
    return max_profit
```
**Complexity Analysis:**
- **Time Complexity:** $O(n)$ since we do a single, linear pass over the array.
- **Space Complexity:** $O(1)$ since we only retain two tracking variables.

---

## Question 10: The Celebrity Problem

**Algorithm Logic:**
Use a two-pointer approach (or a logical elimination stack). We can permanently eliminate one person with every query. If `knows(A, B)` is true, $A$ cannot be the celebrity. If false, $B$ cannot be the celebrity. We repeat this elimination until exactly one candidate remains, then run a secondary verification pass to confirm they are indeed the celebrity.

**Pseudocode:**
```text
function findCelebrity(n):
    candidate = 0
    
    // Phase 1: Aggressively eliminate and find a potential candidate
    for i from 1 to n - 1:
        if knows(candidate, i):
            candidate = i // The old candidate knows 'i', so 'i' is the new candidate
            
    // Phase 2: Verify the isolated candidate
    for i from 0 to n - 1:
        if i != candidate:
            // The candidate must not know anyone, and everyone must know the candidate
            if knows(candidate, i) or not knows(i, candidate):
                return -1 // No celebrity exists in the room
                
    return candidate
```
**Complexity Analysis:**
- **Time Complexity:** Phase 1 takes exactly $n-1$ queries. Phase 2 takes at most $2(n-1)$ queries to verify. Total queries = $O(n)$, executing in $O(n)$ time.
- **Space Complexity:** $O(1)$
