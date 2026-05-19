/*
 * Problem A: 0/1 Knapsack Problem (Dynamic Programming)
 *
 * Logic:
 * We use a 2D DP table where dp[i][w] represents the maximum value that can be
 * obtained using the first i items with a total knapsack capacity of w.
 * For each item, we have two choices:
 * 1. Include the item (if weight <= w): dp[i-1][w - weight[i-1]] + value[i-1]
 * 2. Exclude the item: dp[i-1][w]
 * We take the maximum of these two choices.
 * 
 * Time Complexity: O(N * W), where N is number of items and W is capacity.
 * Space Complexity: O(N * W) for the 2D DP array. (Can be optimized to O(W)).
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int zeroOneKnapsack(int W, const vector<int>& weights, const vector<int>& values, int n) {
    // DP table initialized to 0
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    // Build the table in bottom-up manner
    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= W; w++) {
            if (weights[i - 1] <= w) {
                dp[i][w] = max(values[i - 1] + dp[i - 1][w - weights[i - 1]], dp[i - 1][w]);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    return dp[n][W];
}

int main() {
    cout << "--- 0/1 Knapsack Problem ---\n\n";
    
    // Example from the problem description
    vector<int> weights = {1, 2, 3};
    vector<int> values = {6, 10, 12};
    int W = 5;
    int n = weights.size();

    cout << "Weights: "; for (int w : weights) cout << w << " "; cout << "\n";
    cout << "Values:  "; for (int v : values) cout << v << " "; cout << "\n";
    cout << "Knapsack Capacity: " << W << "\n\n";

    int max_value = zeroOneKnapsack(W, weights, values, n);
    cout << "Result: Maximum value in Knapsack = " << max_value << "\n";

    return 0;
}
