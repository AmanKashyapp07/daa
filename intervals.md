# Master Cheat Sheet: Interval Scheduling Problems

Interval scheduling is one of the most frequently tested topics in DAA exams. Problems usually ask you to maximize the number of intervals, minimize resources used, cover a range, or maximize profit. 

Here are the 4 most commonly asked exam variants, the exact algorithms to solve them, and the intuitions you need to write out your proofs.

---

## 1. Activity Selection Problem (Unweighted Interval Scheduling)
**The Problem:** Given $N$ intervals (start time $S_i$, finish time $F_i$), select the **maximum number** of mutually compatible (non-overlapping) intervals.
*(Example: "Maximize the number of events a person can attend in a single day").*

**The Algorithm (Greedy):**
1. Sort the intervals by their **Finish Times ($F_i$)** in ascending order.
2. Select the first interval in the sorted list.
3. Iterate through the remaining intervals. If an interval's start time $S_i$ is $\ge$ the finish time of the last selected interval, select it.

**Complexity:** $O(N \log N)$ for sorting.

**🧠 Correctness Proof (Exchange Argument):**
- Let the greedy choice pick interval $A$ (which has the absolute earliest finish time).
- Assume the optimal solution $OPT$ does *not* include $A$, but instead starts with some other interval $B$.
- Because $A$ finishes strictly before $B$ ($F_A \le F_B$), if we remove $B$ from $OPT$ and substitute $A$ into its place, $A$ will *never* overlap with any subsequent intervals in $OPT$. 
- The size of the optimal solution remains identical. Thus, the greedy choice of picking the earliest finishing interval is universally safe.

---

## 2. Interval Partitioning (Minimum Classrooms / Meeting Rooms)
**The Problem:** Given $N$ intervals, find the **minimum number of identical resources** (e.g., classrooms, meeting rooms) needed to schedule all of them without any overlaps in the same room.

**The Algorithm (Sweep-Line / Max Overlap):**
1. Break every interval into two separate events: a `Start` event and an `End` event.
2. Sort all events by time. (If a `Start` and `End` happen at the exact same time, process `End` first).
3. Sweep through the timeline maintaining an `active_rooms` counter and a `max_rooms` tracker.
4. If you hit a `Start` event, `active_rooms++`. Update `max_rooms = max(max_rooms, active_rooms)`.
5. If you hit an `End` event, `active_rooms--`.
6. Return `max_rooms`.

**Alternative Algorithm (Min-Heap):**
1. Sort intervals by **Start Time ($S_i$)**.
2. Maintain a Min-Heap tracking the *end times* of currently active rooms.
3. For each interval, if its start time $\ge$ the top of the Min-Heap, it can reuse that room. Pop the heap and push the new end time.
4. Otherwise, it requires a new room. Push its end time to the heap.
5. The size of the Min-Heap at the end is the minimum rooms required.

**Complexity:** $O(N \log N)$ for sorting.

**🧠 Correctness Intuition:** 
The minimum number of rooms needed is mathematically exactly equal to the maximum "depth" of the intervals (the maximum number of intervals that overlap at any single point in time). You physically cannot schedule $k$ overlapping meetings with less than $k$ rooms.

---

## 3. Minimum Interval Cover
**The Problem:** Given a target timeframe $[A, B]$ and a set of $N$ candidate intervals, find the **minimum number of intervals** required to completely cover the target timeframe.
*(Example: "Place the minimum number of cell towers to cover a highway").*

**The Algorithm (Greedy Longest Reach):**
1. Sort the candidate intervals by their **Start Times ($S_i$)** ascending.
2. Initialize `current_end = A`.
3. Iterate through intervals. Among all intervals that start *before or exactly at* `current_end` ($S_i \le \text{current\_end}$), pick the one that reaches the furthest to the right (maximum $F_i$).
4. Update `current_end` to this new maximum $F_i$.
5. Repeat until `current_end \ge B`.

**Complexity:** $O(N \log N)$ for sorting.

**🧠 Correctness Proof (Exchange Argument):**
- Suppose the optimal solution $OPT$ covers the initial gap with an interval $X$ that reaches up to time $T_x$.
- The greedy algorithm chose interval $G$ that covers the initial gap but reaches further to time $T_g$ ($T_g \ge T_x$).
- If we swap $X$ for $G$ in $OPT$, $G$ seamlessly bridges the gap left by $X$ and extends even further. This swap cannot possibly invalidate any subsequent intervals in $OPT$.
- Thus, greedily maximizing the rightward reach at every step is universally safe and minimizes total intervals.

---

## 4. Weighted Interval Scheduling
**The Problem:** Given $N$ intervals, where each interval has a Start Time ($S_i$), Finish Time ($F_i$), and a **Weight / Profit ($W_i$)**, select a non-overlapping subset that maximizes the **total profit**.
*WARNING: Greedy algorithms fail entirely on this variant! You MUST use Dynamic Programming.*

**The Algorithm (Dynamic Programming + Binary Search):**
1. Sort intervals by their **Finish Times ($F_i$)** ascending.
2. Precompute a `p(i)` array: `p(i)` is the index of the latest previously scheduled interval that does *not* overlap with interval `i`. (Use Binary Search to find this in $O(\log N)$).
3. Let `DP[i]` be the maximum profit achievable using a subset of the first `i` intervals.
4. For each interval `i`, we have two choices:
   - **Exclude it:** Profit is `DP[i-1]`.
   - **Include it:** Profit is `W_i + DP[p(i)]` (Weight of $i$ + max profit achievable before $i$ started).
5. State Transition: `DP[i] = max(DP[i-1], W_i + DP[p(i)])`.
6. Return `DP[N]`.

**Complexity:** $O(N \log N)$ (Sorting takes $O(N \log N)$, finding $p(i)$ for all elements via binary search takes $O(N \log N)$, and the DP array evaluates in $O(N)$).

**🧠 Correctness Intuition:** 
Because intervals have wildly varying weights, picking the earliest finisher (like in unweighted) might mean selecting a low-value interval that blocks a massive, highly profitable interval right behind it. By using DP, we meticulously evaluate the "Include vs Exclude" branching paths perfectly bounding the maximum theoretical yield.
