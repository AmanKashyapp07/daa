/*
 * Solutions for Questions 7 & 8 from report3.md
 * Using Recursion + Memoization (Top-Down Dynamic Programming)
 *
 * Question 7: Optimal Strategy for a Game (Coins in a row)
 * Question 8: Two-Person Traversal of a Sequence of Cities
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// ==========================================
// QUESTION 7: Optimal Strategy for a Game (Coins in a row)
// ==========================================
int coinGameMemo(int i, int j, const vector<int>& v, vector<vector<int>>& memo) {
    // Base cases
    if (i > j) return 0;
    if (i == j) return v[i];
    if (i + 1 == j) return max(v[i], v[j]);

    // Return memoized result if already computed
    if (memo[i][j] != -1) return memo[i][j];

    // Choice 1: Player takes left coin v[i]
    // Opponent takes optimally, leaving Player with the worst of the next remaining states
    int takeLeft = v[i] + min(coinGameMemo(i + 2, j, v, memo), 
                              coinGameMemo(i + 1, j - 1, v, memo));

    // Choice 2: Player takes right coin v[j]
    // Opponent takes optimally, leaving Player with the worst of the next remaining states
    int takeRight = v[j] + min(coinGameMemo(i + 1, j - 1, v, memo), 
                               coinGameMemo(i, j - 2, v, memo));

    // Memoize and return the best choice
    return memo[i][j] = max(takeLeft, takeRight);
}

int solveCoinGame(const vector<int>& v) {
    int n = v.size();
    vector<vector<int>> memo(n, vector<int>(n, -1));
    return coinGameMemo(0, n - 1, v, memo);
}

// ==========================================
// QUESTION 8: Two-Person Traversal of a Sequence of Cities
// ==========================================
int cityTraversalMemo(int i, int j, const vector<vector<int>>& dist, int n, vector<vector<int>>& memo) {
    int nextCity = max(i, j) + 1;

    // Base Case: All cities visited
    if (nextCity > n) return 0;

    // Return memoized result if already computed
    if (memo[i][j] != -1) return memo[i][j];

    // Option 1: Assign nextCity to the person currently at city i
    int cost1 = dist[i][nextCity] + cityTraversalMemo(nextCity, j, dist, n, memo);

    // Option 2: Assign nextCity to the person currently at city j
    int cost2 = dist[j][nextCity] + cityTraversalMemo(i, nextCity, dist, n, memo);

    // Memoize and return the minimum cost
    return memo[i][j] = min(cost1, cost2);
}

int solveCityTraversal(const vector<vector<int>>& dist, int n) {
    // memo[i][j] initialized to -1
    vector<vector<int>> memo(n + 1, vector<int>(n + 1, -1));
    return cityTraversalMemo(0, 0, dist, n, memo);
}

int main() {
    // ------------------------------------------
    // Test Case for Question 7: Coins in a Row
    // ------------------------------------------
    cout << "--- Question 7: Optimal Strategy for a Game (Coins in a Row) ---\n";
    vector<int> coins = {8, 15, 3, 7};
    cout << "Coins: ";
    for (int coin : coins) cout << coin << " ";
    cout << "\n";
    cout << "Maximum guaranteed value: " << solveCoinGame(coins) << "\n\n";

    // ------------------------------------------
    // Test Case for Question 8: Two-Person City Traversal
    // ------------------------------------------
    cout << "--- Question 8: Two-Person Traversal of a Sequence of Cities ---\n";
    int n = 4; // 4 cities to visit (1, 2, 3, 4)
    
    // Distance matrix of size (n+1) x (n+1)
    // City 0 is the virtual starting node. dist[0][x] = 0 means starting at city x has 0 travel cost.
    vector<vector<int>> dist = {
        {0, 0, 0, 0, 0},     // Virtual node 0
        {0, 0, 10, 15, 20},  // City 1
        {0, 10, 0, 35, 25},  // City 2
        {0, 15, 35, 0, 30},  // City 3
        {0, 20, 25, 30, 0}   // City 4
    };

    cout << "Minimum traversal distance: " << solveCityTraversal(dist, n) << "\n";

    return 0;
}
