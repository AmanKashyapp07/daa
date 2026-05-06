/*
 * ============================================================================
 *  DP PATTERN 4: GRIDS & LIS
 * ============================================================================
 *  This file covers Grid traversal problems (Unique Paths, Path Sum) and 
 *  Longest Increasing Subsequence, which is a state-based array problem.
 *  
 *  APPROACH: Recursion + Memoization (Top-Down)
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// ─────────────────────────────────────────────────────────────────────────────
//  1. LONGEST INCREASING SUBSEQUENCE (LIS)
// ─────────────────────────────────────────────────────────────────────────────
int lisMemoHelper(const vector<int>& arr, int curr_idx, int prev_idx, vector<vector<int>>& memo) {
    if (curr_idx == arr.size()) return 0;
    
    // Shift prev_idx by 1 since it starts at -1
    if (memo[curr_idx][prev_idx + 1] != -1) return memo[curr_idx][prev_idx + 1];

    int exclude = lisMemoHelper(arr, curr_idx + 1, prev_idx, memo);
    int include = 0;
    
    if (prev_idx == -1 || arr[curr_idx] > arr[prev_idx]) {
        include = 1 + lisMemoHelper(arr, curr_idx + 1, curr_idx, memo);
    }

    return memo[curr_idx][prev_idx + 1] = max(include, exclude);
}
int lisTab(const vector<int>& arr) {
    int n = arr.size();
    vector<int> dp(n, 1); // dp[i] will hold the length of the longest increasing subsequence ending at index i

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[i] > arr[j]) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
    }
    return *max_element(dp.begin(), dp.end());
}
// ─────────────────────────────────────────────────────────────────────────────
//  2. UNIQUE PATHS
// ─────────────────────────────────────────────────────────────────────────────
// Find total ways to go from (0,0) to (m-1, n-1)
int uniquePathsMemo(int m, int n, int i, int j, vector<vector<int>>& memo) {
    if (i == m - 1 && j == n - 1) return 1;
    if (i >= m || j >= n) return 0;
    
    if (memo[i][j] != -1) return memo[i][j];

    return memo[i][j] = uniquePathsMemo(m, n, i + 1, j, memo) + 
                        uniquePathsMemo(m, n, i, j + 1, memo);
}
int uniquePathsTab(int m, int n) {
    vector<vector<int>> dp(m, vector<int>(n, 0));

    for (int i = 0; i < m; i++) dp[i][0] = 1; // Only one way to reach any cell in the first column
    for (int j = 0; j < n; j++) dp[0][j] = 1; // Only one way to reach any cell in the first row

    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            dp[i][j] = dp[i - 1][j] + dp[i][j - 1]; // Ways from top + ways from left
        }
    }
    return dp[m - 1][n - 1];
}

// ─────────────────────────────────────────────────────────────────────────────
//  3. MINIMUM PATH SUM
// ─────────────────────────────────────────────────────────────────────────────
int minPathSumMemo(const vector<vector<int>>& grid, int i, int j, vector<vector<int>>& memo) {
    int m = grid.size();
    int n = grid[0].size();

    // Reached destination
    if (i == m - 1 && j == n - 1) return grid[i][j];
    
    // Out of bounds
    if (i >= m || j >= n) return 9999999; 

    if (memo[i][j] != -1) return memo[i][j];

    int right = minPathSumMemo(grid, i, j + 1, memo);
    int down = minPathSumMemo(grid, i + 1, j, memo);

    return memo[i][j] = grid[i][j] + min(right, down);
}

// ─────────────────────────────────────────────────────────────────────────────
//  4. MAXIMUM PATH IN GRID
// ─────────────────────────────────────────────────────────────────────────────
// Similar to min path sum, but we take max(). Assuming positive numbers.
int maxPathSumMemo(const vector<vector<int>>& grid, int i, int j, vector<vector<int>>& memo) {
    int m = grid.size();
    int n = grid[0].size();

    if (i == m - 1 && j == n - 1) return grid[i][j];
    if (i >= m || j >= n) return -9999999; 

    if (memo[i][j] != -1) return memo[i][j];

    int right = maxPathSumMemo(grid, i, j + 1, memo);
    int down = maxPathSumMemo(grid, i + 1, j, memo);

    return memo[i][j] = grid[i][j] + max(right, down);
}

// ─────────────────────────────────────────────────────────────────────────────
//  DRIVER
// ─────────────────────────────────────────────────────────────────────────────
int main() {
    cout << "=== GRIDS & LIS (Recursion + Memoization) ===\n\n";

    vector<int> arr = {10, 22, 9, 33, 21, 50, 41, 60, 80};
    vector<vector<int>> memo1(arr.size(), vector<int>(arr.size() + 1, -1));
    cout << "1. LIS Length: " << lisMemoHelper(arr, 0, -1, memo1) << "\n";

    int m = 3, n = 7;
    vector<vector<int>> memo2(m, vector<int>(n, -1));
    cout << "2. Unique Paths (3x7 grid): " << uniquePathsMemo(m, n, 0, 0, memo2) << "\n";

    vector<vector<int>> grid = {
        {1, 3, 1},
        {1, 5, 1},
        {4, 2, 1}
    };
    vector<vector<int>> memo3(grid.size(), vector<int>(grid[0].size(), -1));
    cout << "3. Minimum Path Sum: " << minPathSumMemo(grid, 0, 0, memo3) << "\n";

    vector<vector<int>> memo4(grid.size(), vector<int>(grid[0].size(), -1));
    cout << "4. Maximum Path Sum: " << maxPathSumMemo(grid, 0, 0, memo4) << "\n";

    return 0;
}
