# Greedy Algorithms - End Semester Master Summary

This document serves as an exam-aligned summary of the "Greedy Algorithms" lecture. It covers fundamental principles, data compression (Huffman Coding), Knapsack distinctions, and structured correctness proofs.

---

## 1. Fundamentals of Greedy Algorithms
**Goal:** Make the locally optimal choice at each individual step with the hope of finding a global optimum.
- **"Stingy" Nature:** A greedy algorithm only takes what is strictly necessary at the moment. It rarely looks backward to reconsider previous choices.
- **Two Parts of Correctness:**
  1. *Validity:* If the algorithm returns a solution, is it legally valid?
  2. *Optimality / Existence:* Does the greedy step artificially eliminate valid optimal solutions?

---

## 2. Huffman Coding (Data Compression)
**Goal:** Pick a binary character code that minimizes the total number of bits required to represent a given file based on character frequencies.

**Key Concepts:**
- **Fixed vs. Variable Length:** Instead of using fixed bits (e.g., 2 bits for 4 characters), variable length assigns shorter codes to highly frequent characters.
- **Prefix Codes:** A code where *no codeword is a prefix of any other codeword*. This ensures the encoded binary string is unambiguously decodable without needing spaces or delimiters.
- **Prefix Tree:** Represented as a binary tree where traversing left is `0` and right is `1`. Leaf nodes represent the characters.

### Cost Function
The cost (total bits) of a file is defined mathematically in two equivalent ways:
1. $Cost = \sum (\text{depth of character} \times \text{frequency of character})$
2. $Cost = \text{Sum of the values of all internal nodes} + \text{leaf nodes}$ (Since traversing down inherently reads one bit per non-root node).

### The Algorithm (Min-Heap)
1. Insert all characters and their frequencies into a Min-Heap.
2. Extract the two nodes with the lowest frequencies.
3. Create a new internal node combining their frequencies.
4. Insert this new node back into the Min-Heap.
5. Repeat until only 1 node (the root) remains.

**Complexity:** $O(n \log n)$
- `MakeHeap` takes $O(n)$.
- $2(n-1)$ calls to `ExtractMin` takes $O(n \log n)$.
- $n-1$ calls to `Insert` takes $O(n \log n)$.

### 🧠 Correctness Proof & Intuition (Huffman Optimality)
- **Claim:** Merging the two characters with the absolute lowest frequencies optimally minimizes tree depth costs.
- **Intuition to Remember (The Heavy Weights Float):** Imagine characters are physical weights tied to branches of a tree. The heavier the weight (frequency), the shorter the branch (depth) must be so the tree doesn't break. The two lightest weights can afford to be pushed to the very bottom.
- **Proof Logic (Contradiction / Exchange Argument):** Suppose an optimal prefix tree exists where the two least frequent symbols ($f_1$ and $f_2$) are NOT siblings at the absolute maximum depth. Let $f_i$ be some character at the maximum depth where $f_i > f_1$. If we physically swap $f_1$ and $f_i$ in the tree, the highly frequent $f_i$ moves higher (shallower), and the rare $f_1$ moves lower. Because $f_i$ appears more often, this swap strictly *decreases* the total cost. Since we supposedly started with an "optimal" tree but managed to make it better, we have a contradiction! Therefore, the optimal tree *must* group the two lowest frequencies at the bottom.

---

## 3. The Knapsack Distinction (Greedy Limits)
**1. Fractional Knapsack:**
- **Problem:** You can take fractional portions of items (e.g., sand, liquids).
- **Greedy Solution:** Sort items descending by their "Value per Weight" ratio ($\frac{v_i}{w_i}$). Take as much as possible of the highest ratio item, then move to the next.
- **Status:** **Optimal.** Greedy perfectly solves this because you never waste space.

**2. 0-1 Knapsack:**
- **Problem:** You must take the entire item or leave it completely (e.g., ingots, TVs).
- **Greedy Solution:** Sorting by value/weight ratio fails!
- **Status:** **Non-Optimal.** If you greedily take the highest ratio item, it might leave an awkward gap in the knapsack that is too small for other items, wasting capacity. You might have been better off taking two slightly worse items that perfectly filled the bag. 0-1 Knapsack requires **Dynamic Programming**.

---

## 4. Other Non-Optimal Greedy Algorithms
It's important to remember that Greedy algorithms do *not* always yield the mathematically optimal solution. In many hard problems, Greedy provides a "good enough" heuristic but fails the optimality proof.
Examples include:
- **Set Cover**
- **Clustering**
- **Hill-Climbing Algorithms**
- **Certain Relaxation Techniques**
