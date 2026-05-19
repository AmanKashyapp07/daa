# Master Theorem: Ultimate Exam Cheat Sheet

The Master Theorem is a recipe for solving recurrence relations of the form:
$$T(n) = a T\left(\frac{n}{b}\right) + f(n)$$

### What do the variables mean?
- **$a$**: The number of subproblems in the recursion ($a \ge 1$).
- **$b$**: The factor by which the problem size is divided ($b > 1$).
- **$f(n)$**: The cost of the work done strictly *outside* the recursive calls (usually the cost of dividing the problem and combining the results).
- **$n^{\log_b a}$**: The "Watershed" function. This represents the amount of work done at the very bottom level (the leaves) of the recursion tree.

### The Core Intuition
To find the final time complexity, you are always battling two forces against each other:
1. **$f(n)$**: The work done at the **Root**.
2. **$n^{\log_b a}$**: The work done at the **Leaves**.

Whichever side is "polynomially larger" dictates the final time complexity.

---

## The Three Cases

### Case 1: The Leaves Dominate
If the work at the leaves is polynomially *larger* than the work at the root.
- **Condition:** $f(n) = O(n^{\log_b a - \epsilon})$ for some constant $\epsilon > 0$.
- **Result:** **$T(n) = \Theta(n^{\log_b a})$**

### Case 2: The Work is Evenly Distributed
If the work at the root and the work at the leaves are exactly the same size (or differ only by a $\log^k n$ factor).
- **Condition:** $f(n) = \Theta(n^{\log_b a} \log^k n)$ for some constant $k \ge 0$.
- **Result:** **$T(n) = \Theta(n^{\log_b a} \log^{k+1} n)$**
- *(Intuition: Because every level of the tree does the exact same amount of work, you just multiply the work per level by the number of levels, which is $\log n$)*.

### Case 3: The Root Dominates
If the work at the root is polynomially *larger* than the work at the leaves.
- **Condition:** $f(n) = \Omega(n^{\log_b a + \epsilon})$ for some constant $\epsilon > 0$.
  - *(And it must satisfy the **Regularity Condition**: $a f(n/b) \le c f(n)$ for some $c < 1$. In 99% of exam problems where $f(n)$ is a polynomial, this is automatically true).*
- **Result:** **$T(n) = \Theta(f(n))$**

---

## 5 High-Quality Exam Examples

### Example 1: Classic Case 1 (Leaves Dominate)
**Recurrence:** $T(n) = 4T(n/2) + n$
1. **Extract Variables:** $a = 4, b = 2, f(n) = n$
2. **Calculate Watershed:** $n^{\log_b a} = n^{\log_2 4} = n^2$
3. **Compare:** We compare $f(n) = n^1$ against $n^2$. Since $n^1$ is polynomially smaller than $n^2$ (by a factor of $n^1$, so $\epsilon = 1$), the leaves dominate.
4. **Answer:** **$T(n) = \Theta(n^2)$**

### Example 2: Classic Case 2 (Merge Sort)
**Recurrence:** $T(n) = 2T(n/2) + n$
1. **Extract Variables:** $a = 2, b = 2, f(n) = n$
2. **Calculate Watershed:** $n^{\log_b a} = n^{\log_2 2} = n^1 = n$
3. **Compare:** We compare $f(n) = n$ against $n$. They are perfectly equal! This matches Case 2 with $k = 0$.
4. **Answer:** Multiply by $\log n \implies$ **$T(n) = \Theta(n \log n)$**

### Example 3: Advanced Case 2 (Poly-logarithmic)
**Recurrence:** $T(n) = 2T(n/2) + n \log n$
1. **Extract Variables:** $a = 2, b = 2, f(n) = n \log n$
2. **Calculate Watershed:** $n^{\log_b a} = n^{\log_2 2} = n$
3. **Compare:** We compare $f(n) = n \log^1 n$ against $n$. They are identical except for a $\log^1 n$ factor. This matches Case 2 with $k = 1$.
4. **Answer:** Bump the log power by $1 \implies$ **$T(n) = \Theta(n \log^2 n)$**

### Example 4: Classic Case 3 (Root Dominates)
**Recurrence:** $T(n) = 3T(n/4) + n \log n$
1. **Extract Variables:** $a = 3, b = 4, f(n) = n \log n$
2. **Calculate Watershed:** $n^{\log_b a} = n^{\log_4 3} \approx n^{0.793}$
3. **Compare:** We compare $f(n) = n^1 \log n$ against $n^{0.793}$. $f(n)$ is polynomially larger (the exponent $1$ is strictly greater than $0.793$, so $\epsilon \approx 0.2$). The root dominates.
4. **Regularity Check:** $3(\frac{n}{4} \log \frac{n}{4}) \le \frac{3}{4} n \log n$, which holds for $c = \frac{3}{4} < 1$.
5. **Answer:** **$T(n) = \Theta(n \log n)$**

### Example 5: The Exam Trap (Master Theorem FAILS)
**Recurrence:** $T(n) = 2T(n/2) + \frac{n}{\log n}$
1. **Extract Variables:** $a = 2, b = 2, f(n) = \frac{n}{\log n}$
2. **Calculate Watershed:** $n^{\log_b a} = n^{\log_2 2} = n$
3. **Compare:** We compare $f(n) = \frac{n}{\log n}$ against $n$. 
   - Is $f(n)$ polynomially smaller than $n$? No. It is asymptotically smaller, but only by a logarithmic factor ($\frac{1}{\log n}$), not a polynomial factor ($n^{-\epsilon}$). There is no $\epsilon > 0$ where $n^{1-\epsilon} \ge \frac{n}{\log n}$.
   - Is it equal? No.
4. **Conclusion:** **The Master Theorem does NOT apply.** 
   - *(Note: To solve this, you would use a recursion tree or the Akra-Bazzi method, which would yield $T(n) = \Theta(n \log \log n)$).* Professors love putting this exact recurrence on exams to check if you actually test for $\epsilon$!
