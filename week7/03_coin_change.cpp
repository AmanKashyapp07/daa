/*
 * ============================================================================
 *  COIN CHANGE PROBLEM & DP OPTIMIZATION
 * ============================================================================
 *  This file covers TWO variations of the coin change problem. Both are 
 *  instances of the Unbounded Knapsack problem (since we have infinite supply 
 *  of coins).
 *
 *  VARIATION 1: MINIMUM COINS
 *  - Find the minimum number of coins needed to make a target amount.
 *  - DP State: dp[i] = min coins to make amount i.
 *  - Recurrence: dp[i] = min(dp[i], 1 + dp[i - coin_value])
 *
 *  VARIATION 2: NUMBER OF WAYS
 *  - Find the total number of distinct ways to make a target amount.
 *  - DP State: dp[i] = number of ways to make amount i.
 *  - Recurrence: dp[i] = dp[i] + dp[i - coin_value]
 *
 *  TIME COMPLEXITY:  O(N * W) where N is number of coins, W is target sum
 *  SPACE COMPLEXITY: O(W) (Both are naturally space-optimized to 1D arrays)
 *
 *  EXAM TIP:
 *  - Note the outer loop! 
 *    If outer loop is over Coins and inner loop is over Amounts -> Computes 
 *    COMBINATIONS (order doesn't matter, e.g. {1,2} is same as {2,1}).
 *    If outer loop is over Amounts and inner loop is over Coins -> Computes 
 *    PERMUTATIONS (order matters, e.g. {1,2} and {2,1} are distinct).
 *    Usually, standard Coin Change asks for Combinations.
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
//  VARIATION 1: MINIMUM COINS TO MAKE AMOUNT
// ─────────────────────────────────────────────────────────────────────────────
int minCoins(const vector<int>& coins, int amount) {
    // Initialize dp array with infinity (using amount+1 as infinity)
    vector<int> dp(amount + 1, amount + 1);
    
    // Base case: 0 coins needed for amount 0
    dp[0] = 0;

    // Iterating over amounts (outer) and coins (inner)
    for (int i = 1; i <= amount; ++i) {
        for (int coin : coins) {
            if (coin <= i) {
                dp[i] = min(dp[i], dp[i - coin] + 1);
            }
        }
    }

    return dp[amount] > amount ? -1 : dp[amount];
}

// ─────────────────────────────────────────────────────────────────────────────
//  VARIATION 2: TOTAL NUMBER OF WAYS TO MAKE AMOUNT
// ─────────────────────────────────────────────────────────────────────────────
int waysToMakeAmount(const vector<int>& coins, int amount) {
    vector<int> dp(amount + 1, 0);
    
    // Base case: 1 way to make amount 0 (using no coins)
    dp[0] = 1;

    // Outer loop over COINS to count combinations (not permutations)
    for (int coin : coins) {
        // Inner loop over amounts
        for (int i = coin; i <= amount; ++i) {
            dp[i] += dp[i - coin];
        }
    }

    return dp[amount];
}

// ─────────────────────────────────────────────────────────────────────────────
//  DRIVER
// ─────────────────────────────────────────────────────────────────────────────
int main() {
    cout << "=== COIN CHANGE PROBLEM ===\n";
    vector<int> coins = {1, 2, 5};
    int amount = 11;

    cout << "Available Coins: ";
    for (int c : coins) cout << c << " ";
    cout << "\nTarget Amount: " << amount << "\n\n";

    cout << "1. Minimum Coins Required: " << minCoins(coins, amount) << "\n";
    // For 11: 5 + 5 + 1 = 3 coins

    cout << "2. Number of Ways to Make Amount: " << waysToMakeAmount(coins, amount) << "\n";

    return 0;
}
