/*
 * ============================================================================
 *  SUBSET SUM (NP-Complete Problem)
 * ============================================================================
 *  PROBLEM:
 *  - Given a set of non-negative integers and a target sum W.
 *  - Is there a subset of the given set whose sum is exactly W?
 *
 *  WHY IS IT NP-COMPLETE?
 *  - It is a special case of the Knapsack Problem.
 *  - We can verify a solution (the subset) in polynomial time by just 
 *    summing it up. So it is in NP.
 *  - We can reduce 3-SAT to Subset Sum, proving it is NP-Hard.
 *
 *  APPROACHES:
 *  1. Backtracking / Recursion:
 *     - Time: O(2^N)
 *     - Tests all possible subsets. This is the true algorithmic complexity.
 *
 *  2. Dynamic Programming (Pseudo-Polynomial Time):
 *     - Time: O(N * W)
 *     - Space: O(W)
 *     - Wait, if it's O(N*W), isn't that polynomial? NO! W is the VALUE of the 
 *       input, not the SIZE of the input. The size of W in binary is log(W) bits. 
 *       Therefore, O(W) is actually O(2^(log W)), which is exponential relative 
 *       to the input size. This is called a "Pseudo-Polynomial" algorithm.
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <deque>
#include <limits>
#include <climits>
#include <cstring>
#include <numeric>

using namespace std;

// ─────────────────────────────────────────────────────────────────────────────
//  1. SUBSET SUM - BACKTRACKING (O(2^N))
// ─────────────────────────────────────────────────────────────────────────────
bool isSubsetSumBacktracking(const vector<int>& arr, int n, int target) {
    // Base Cases
    if (target == 0) return true;
    if (n == 0) return false;

    // If last element is greater than target, ignore it
    if (arr[n - 1] > target) {
        return isSubsetSumBacktracking(arr, n - 1, target);
    }

    // Check if sum can be obtained by either:
    // (a) including the last element
    // (b) excluding the last element
    return isSubsetSumBacktracking(arr, n - 1, target - arr[n - 1]) ||
           isSubsetSumBacktracking(arr, n - 1, target);
}

// ─────────────────────────────────────────────────────────────────────────────
//  2. SUBSET SUM - DYNAMIC PROGRAMMING (O(N * W) Pseudo-Polynomial)
// ─────────────────────────────────────────────────────────────────────────────
bool isSubsetSumDP(const vector<int>& arr, int target) {
    int n = arr.size();
    // dp[i] will be true if a subset with sum i exists
    vector<bool> dp(target + 1, false);
    
    // Sum 0 is always achievable with an empty subset
    dp[0] = true;

    for (int i = 0; i < n; i++) {
        // Iterate backwards to avoid using the same element multiple times
        for (int j = target; j >= arr[i]; j--) {
            if (dp[j - arr[i]]) {
                dp[j] = true;
            }
        }
    }

    return dp[target];
}

// ─────────────────────────────────────────────────────────────────────────────
//  DRIVER
// ─────────────────────────────────────────────────────────────────────────────
int main() {
    vector<int> arr = {3, 34, 4, 12, 5, 2};
    int target = 9;

    cout << "=== SUBSET SUM PROBLEM ===\n";
    cout << "Set: {3, 34, 4, 12, 5, 2}, Target: " << target << "\n\n";

    cout << "1. Backtracking result: ";
    if (isSubsetSumBacktracking(arr, arr.size(), target))
        cout << "Found a subset with given sum\n";
    else
        cout << "No subset with given sum\n";

    cout << "2. Dynamic Programming result: ";
    if (isSubsetSumDP(arr, target))
        cout << "Found a subset with given sum\n";
    else
        cout << "No subset with given sum\n";

    return 0;
}
