/*
 * ============================================================================
 *  DP PATTERN 1: 0/1 KNAPSACK & ITS VARIATIONS
 * ============================================================================
 *  This file covers problems that are derived from the 0/1 Knapsack pattern.
 *  In these problems, we have an array of items and a target capacity/sum.
 *  For each item, we have TWO choices: Include it (if valid) or Exclude it.
 *  
 *  APPROACH: Recursion + Memoization (Top-Down)
 * ============================================================================
 */
// trick for conevrting memo to tab: the recursive calls in memoization will be in the form of dp[i-1][j] or dp[i][j-wt[i-1]] where i and j are the parameters of the recursive function. We can use these parameters to fill the dp table iteratively in a bottom-up manner.
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

// ─────────────────────────────────────────────────────────────────────────────
//  1. 0/1 KNAPSACK
// ─────────────────────────────────────────────────────────────────────────────
int knapsackMemo(const vector<int>& wt, const vector<int>& val, int W, int n, vector<vector<int>>& memo) {
    if (n == 0 || W == 0) return 0;
    if (memo[n][W] != -1) return memo[n][W];

    if (wt[n - 1] <= W) {
        return memo[n][W] = max(
            val[n - 1] + knapsackMemo(wt, val, W - wt[n - 1], n - 1, memo), // Include
            knapsackMemo(wt, val, W, n - 1, memo)                           // Exclude
        );
    } else {
        return memo[n][W] = knapsackMemo(wt, val, W, n - 1, memo);          // Exclude
    }
}
int knapsackTab(const vector<int>& wt, const vector<int>& val, int W) {
    int n = wt.size();
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= W; w++) {
            if (wt[i - 1] <= w) {
                dp[i][w] = max(val[i - 1] + dp[i - 1][w - wt[i - 1]], // Include
                               dp[i - 1][w]);                       // Exclude
            } else {
                dp[i][w] = dp[i - 1][w]; // Exclude
            }
        }
    }
    return dp[n][W];
}   

// ─────────────────────────────────────────────────────────────────────────────
//  2. SUBSET SUM
// ─────────────────────────────────────────────────────────────────────────────
bool subsetSumMemo(const vector<int>& arr, int sum, int n, vector<vector<int>>& memo) {
    if (sum == 0) return true;
    if (n == 0) return false;
    if (memo[n][sum] != -1) return memo[n][sum];

    if (arr[n - 1] <= sum) {
        return memo[n][sum] = subsetSumMemo(arr, sum - arr[n - 1], n - 1, memo) || 
                              subsetSumMemo(arr, sum, n - 1, memo);
    } else {
        return memo[n][sum] = subsetSumMemo(arr, sum, n - 1, memo);
    }
}
bool subsetSumTab(const vector<int>& arr, int sum) {
    int n = arr.size();
    vector<vector<bool>> dp(n + 1, vector<bool>(sum + 1, false));

    for (int i = 0; i <= n; i++) dp[i][0] = true; // Sum 0 can always be achieved with empty subset

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= sum; j++) {
            if (arr[i - 1] <= j) {
                dp[i][j] = dp[i - 1][j - arr[i - 1]] || dp[i - 1][j];
            } else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }
    return dp[n][sum];
}
// ─────────────────────────────────────────────────────────────────────────────
//  3. PARTITION EQUAL SUBSET SUM
// ─────────────────────────────────────────────────────────────────────────────
bool equalPartition(const vector<int>& arr) {
    int sum = accumulate(arr.begin(), arr.end(), 0);
    if (sum % 2 != 0) return false; // Odd sum cannot be partitioned equally

    int target = sum / 2;
    int n = arr.size();
    vector<vector<int>> memo(n + 1, vector<int>(target + 1, -1));
    return subsetSumMemo(arr, target, n, memo);
}
bool equalPartitionTab(const vector<int>& arr) {
    int sum = accumulate(arr.begin(), arr.end(), 0);
    if (sum % 2 != 0) return false; // Odd sum cannot be partitioned equally

    int target = sum / 2;
    return subsetSumTab(arr, target);
}
// ─────────────────────────────────────────────────────────────────────────────
//  4. COUNT SUBSETS WITH GIVEN SUM
// ─────────────────────────────────────────────────────────────────────────────
int countSubsetsMemo(const vector<int>& arr, int sum, int n, vector<vector<int>>& memo) {
    if (sum == 0) return 1;
    if (n == 0) return 0;
    if (memo[n][sum] != -1) return memo[n][sum];

    if (arr[n - 1] <= sum) {
        return memo[n][sum] = countSubsetsMemo(arr, sum - arr[n - 1], n - 1, memo) + 
                              countSubsetsMemo(arr, sum, n - 1, memo);
    } else {
        return memo[n][sum] = countSubsetsMemo(arr, sum, n - 1, memo);
    }
}
int countSubsetsTab(const vector<int>& arr, int sum) {
    int n = arr.size();
    vector<vector<int>> dp(n + 1, vector<int>(sum + 1, 0));

    for (int i = 0; i <= n; i++) dp[i][0] = 1; // There's one subset (empty set) for sum 0

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= sum; j++) {
            if (arr[i - 1] <= j) {
                dp[i][j] = dp[i - 1][j - arr[i - 1]] + dp[i - 1][j];
            } else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }
    return dp[n][sum];
}
// ─────────────────────────────────────────────────────────────────────────────
//  DRIVER
// ─────────────────────────────────────────────────────────────────────────────
int main() {
    cout << "=== 0/1 KNAPSACK VARIATIONS (Recursion + Memoization) ===\n\n";

    vector<int> val = {60, 100, 120};
    vector<int> wt = {10, 20, 30};
    int W = 50;
    vector<vector<int>> memo1(wt.size() + 1, vector<int>(W + 1, -1));
    cout << "1. 0/1 Knapsack Max Value: " << knapsackMemo(wt, val, W, wt.size(), memo1) << "\n";

    vector<int> arr = {2, 3, 7, 8, 10};
    int sum = 11;
    vector<vector<int>> memo2(arr.size() + 1, vector<int>(sum + 1, -1));
    cout << "2. Subset Sum exists for 11: " << (subsetSumMemo(arr, sum, arr.size(), memo2) ? "Yes" : "No") << "\n";

    vector<int> arr2 = {1, 5, 11, 5};
    cout << "3. Partition Equal Subset Sum: " << (equalPartition(arr2) ? "Yes" : "No") << "\n";

    vector<int> arr3 = {2, 3, 5, 6, 8, 10};
    int target = 10;
    vector<vector<int>> memo3(arr3.size() + 1, vector<int>(target + 1, -1));
    cout << "4. Count Subsets with Sum 10: " << countSubsetsMemo(arr3, target, arr3.size(), memo3) << "\n";

    return 0;
}
