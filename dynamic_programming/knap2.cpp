/*
 * ============================================================================
 *  DP PATTERN 2: UNBOUNDED KNAPSACK & ITS VARIATIONS
 * ============================================================================
 *  This file covers problems derived from the Unbounded Knapsack pattern.
 *  The key difference from 0/1 Knapsack is that an item can be chosen an 
 *  INFINITE number of times. When we include an item, we DO NOT decrement 'n'.
 *  
 *  APPROACH: Recursion + Memoization (Top-Down)
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// ─────────────────────────────────────────────────────────────────────────────
//  1. UNBOUNDED KNAPSACK
// ─────────────────────────────────────────────────────────────────────────────
int unboundedKnapsackMemo(const vector<int>& wt, const vector<int>& val, int W, int n, vector<vector<int>>& memo) {
    if (n == 0 || W == 0) return 0;
    if (memo[n][W] != -1) return memo[n][W];

    if (wt[n - 1] <= W) {
        // Notice 'n' is passed instead of 'n-1' when including the item
        return memo[n][W] = max(
            val[n - 1] + unboundedKnapsackMemo(wt, val, W - wt[n - 1], n, memo), // Include
            unboundedKnapsackMemo(wt, val, W, n - 1, memo)                       // Exclude
        );
    } else {
        return memo[n][W] = unboundedKnapsackMemo(wt, val, W, n - 1, memo);      // Exclude
    }
}
int unboundedKnapsackTab(const vector<int>& wt, const vector<int>& val, int W) {
    int n = wt.size();
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= W; w++) {
            if (wt[i - 1] <= w) {
                dp[i][w] = max(val[i - 1] + dp[i][w - wt[i - 1]], // Include
                               dp[i - 1][w]);                       // Exclude
            } else {
                dp[i][w] = dp[i - 1][w]; // Exclude
            }
        }
    }
    return dp[n][W];
}
// ─────────────────────────────────────────────────────────────────────────────
//  2. COIN CHANGE (Minimum Coins)
// ─────────────────────────────────────────────────────────────────────────────
int minCoinsMemo(const vector<int>& coins, int amount, int n, vector<vector<int>>& memo) {
    if (amount == 0) return 0;
    if (n == 0) return 9999999; // Represents infinity
    
    if (memo[n][amount] != -1) return memo[n][amount];

    if (coins[n - 1] <= amount) {
        int include = 1 + minCoinsMemo(coins, amount - coins[n - 1], n, memo);
        int exclude = minCoinsMemo(coins, amount, n - 1, memo);
        return memo[n][amount] = min(include, exclude);
    } else {
        return memo[n][amount] = minCoinsMemo(coins, amount, n - 1, memo);
    }
}
int minCoinsTab(const vector<int>& coins, int amount) {
    int n = coins.size();
    vector<vector<int>> dp(n + 1, vector<int>(amount + 1, 9999999));

    for (int i = 0; i <= n; i++) {
        dp[i][0] = 0;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= amount; j++) {
            if (coins[i - 1] <= j) {
                dp[i][j] = min(1 + dp[i][j - coins[i - 1]], dp[i - 1][j]);
            } else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }
    return dp[n][amount] >= 9999999 ? -1 : dp[n][amount];
}

// ─────────────────────────────────────────────────────────────────────────────
//  3. COIN CHANGE (Number of Ways)
// ─────────────────────────────────────────────────────────────────────────────
int coinWaysMemo(const vector<int>& coins, int amount, int n, vector<vector<int>>& memo) {
    if (amount == 0) return 1;
    if (n == 0) return 0;
    
    if (memo[n][amount] != -1) return memo[n][amount];

    if (coins[n - 1] <= amount) {
        return memo[n][amount] = coinWaysMemo(coins, amount - coins[n - 1], n, memo) + 
                                 coinWaysMemo(coins, amount, n - 1, memo);
    } else {
        return memo[n][amount] = coinWaysMemo(coins, amount, n - 1, memo);
    }
}
int coinWaysTab(const vector<int>& coins, int amount) {
    int n = coins.size();
    vector<vector<int>> dp(n + 1, vector<int>(amount + 1, 0));
    dp[0][0] = 1;

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= amount; j++) {
            if (coins[i - 1] <= j) {
                dp[i][j] = dp[i - 1][j] + dp[i][j - coins[i - 1]];
            } else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }
    return dp[n][amount];
}

// ─────────────────────────────────────────────────────────────────────────────
//  4. ROD CUTTING
// ─────────────────────────────────────────────────────────────────────────────
// Given a rod of length N, and prices for lengths 1 to N, find max revenue.
// This is exactly Unbounded Knapsack where wt[] = {1,2,3...N} and W = N.
int rodCuttingMemo(const vector<int>& price, int length, int n, vector<vector<int>>& memo) {
    if (n == 0 || length == 0) return 0;
    if (memo[n][length] != -1) return memo[n][length];

    int piece_len = n; // piece lengths are 1, 2, ..., N
    if (piece_len <= length) {
        return memo[n][length] = max(
            price[n - 1] + rodCuttingMemo(price, length - piece_len, n, memo), // Include
            rodCuttingMemo(price, length, n - 1, memo)                         // Exclude
        );
    } else {
        return memo[n][length] = rodCuttingMemo(price, length, n - 1, memo);
    }
}
int rodCuttingTab(const vector<int>& price, int length) {
    int n = price.size();
    vector<vector<int>> dp(n + 1, vector<int>(length + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= length; j++) {
            if (i <= j) {
                dp[i][j] = max(price[i - 1] + dp[i][j - i], dp[i - 1][j]);
            } else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }
    return dp[n][length];
}

// ─────────────────────────────────────────────────────────────────────────────
//  DRIVER
// ─────────────────────────────────────────────────────────────────────────────
int main() {
    cout << "=== UNBOUNDED KNAPSACK VARIATIONS (Recursion + Memoization) ===\n\n";

    vector<int> val = {10, 40, 50, 70};
    vector<int> wt = {1, 3, 4, 5};
    int W = 8;
    vector<vector<int>> memo1(wt.size() + 1, vector<int>(W + 1, -1));
    cout << "1. Unbounded Knapsack Max Value: " << unboundedKnapsackMemo(wt, val, W, wt.size(), memo1) << "\n";

    vector<int> coins = {1, 2, 5};
    int amount = 11;
    vector<vector<int>> memo2(coins.size() + 1, vector<int>(amount + 1, -1));
    int min_c = minCoinsMemo(coins, amount, coins.size(), memo2);
    cout << "2. Coin Change (Min Coins): " << (min_c >= 9999999 ? -1 : min_c) << "\n";

    vector<vector<int>> memo3(coins.size() + 1, vector<int>(amount + 1, -1));
    cout << "3. Coin Change (Ways to make 11): " << coinWaysMemo(coins, amount, coins.size(), memo3) << "\n";

    vector<int> price = {1, 5, 8, 9, 10, 17, 17, 20};
    int N = price.size();
    vector<vector<int>> memo4(N + 1, vector<int>(N + 1, -1));
    cout << "4. Rod Cutting Max Revenue: " << rodCuttingMemo(price, N, N, memo4) << "\n";

    return 0;
}
