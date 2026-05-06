/*
 * ============================================================================
 *  DP PATTERN 3: LONGEST COMMON SUBSEQUENCE (LCS) & VARIATIONS
 * ============================================================================
 *  This file covers problems that involve matching/comparing two strings or 
 *  sequences. The core logic relies on checking if characters match, and if 
 *  not, branching to check subsets of the strings.
 *  
 *  APPROACH: Recursion + Memoization (Top-Down)
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

// ─────────────────────────────────────────────────────────────────────────────
//  1. LONGEST COMMON SUBSEQUENCE (LCS)
// ─────────────────────────────────────────────────────────────────────────────
int lcsMemo(const string& X, const string& Y, int m, int n, vector<vector<int>>& memo) {
    if (m == 0 || n == 0) return 0;
    if (memo[m][n] != -1) return memo[m][n];

    if (X[m - 1] == Y[n - 1]) {
        return memo[m][n] = 1 + lcsMemo(X, Y, m - 1, n - 1, memo);
    } else {
        return memo[m][n] = max(lcsMemo(X, Y, m, n - 1, memo), 
                                lcsMemo(X, Y, m - 1, n, memo));
    }
}
int lcsTab(const string& X, const string& Y) {
    int m = X.length();
    int n = Y.length();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (X[i - 1] == Y[j - 1]) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            } else {
                dp[i][j] = max(dp[i][j - 1], dp[i - 1][j]);
            }
        }
    }
    return dp[m][n];
}   
// ─────────────────────────────────────────────────────────────────────────────
//  2. LONGEST PALINDROMIC SUBSEQUENCE (LPS)
// ─────────────────────────────────────────────────────────────────────────────
// LPS is just LCS of a string 'X' and its reverse
// Proof : If we have a longest palindromic subsequence 'P' in 'X', then 'P' will also be a subsequence of the reverse of 'X' (let's call it 'Y'), 
// and since 'P' is a palindrome, it will read the same forwards and backwards. Therefore, 'P' will be a common subsequence of both 'X' and 'Y'. Now, if there were a longer common subsequence than 'P', it 
//would also have to be a palindrome (since it would be a common subsequence of 'X' and its reverse), which contradicts the assumption that 'P' is the 
//longest palindromic subsequence. Hence, the length of the longest palindromic subsequence in 'X' is equal to the length of the longest common subsequence between 'X' and its reverse.
int lpsMemo(string X) {
    string Y = X;
    reverse(Y.begin(), Y.end());
    int m = X.length();
    vector<vector<int>> memo(m + 1, vector<int>(m + 1, -1));
    return lcsMemo(X, Y, m, m, memo);
}

// ─────────────────────────────────────────────────────────────────────────────
//  3. EDIT DISTANCE
// ─────────────────────────────────────────────────────────────────────────────
int editDistanceMemo(const string& X, const string& Y, int m, int n, vector<vector<int>>& memo) {
    // Base cases
    if (m == 0) return n; // Insert all n characters
    if (n == 0) return m; // Remove all m characters
    if (memo[m][n] != -1) return memo[m][n];
    if (X[m - 1] == Y[n - 1]) {
        return memo[m][n] = editDistanceMemo(X, Y, m - 1, n - 1, memo);
    }

    // If last chars don't match, consider all 3 operations
    return memo[m][n] = 1 + min({
        editDistanceMemo(X, Y, m, n - 1, memo),     // Insert
        editDistanceMemo(X, Y, m - 1, n, memo),     // Remove
        editDistanceMemo(X, Y, m - 1, n - 1, memo)  // Replace
    });
}

// ─────────────────────────────────────────────────────────────────────────────
//  DRIVER
// ─────────────────────────────────────────────────────────────────────────────
int main() {
    cout << "=== LCS VARIATIONS (Recursion + Memoization) ===\n\n";

    string X = "AGGTAB";
    string Y = "GXTXAYB";
    int m = X.length();
    int n = Y.length();
    vector<vector<int>> memo1(m + 1, vector<int>(n + 1, -1));
    cout << "1. LCS Length: " << lcsMemo(X, Y, m, n, memo1) << "\n";

    string s = "GEEKSFORGEEKS";
    cout << "2. Longest Palindromic Subsequence Length: " << lpsMemo(s) << "\n";

    string s1 = "intention";
    string s2 = "execution";
    vector<vector<int>> memo2(s1.length() + 1, vector<int>(s2.length() + 1, -1));
    cout << "3. Edit Distance: " << editDistanceMemo(s1, s2, s1.length(), s2.length(), memo2) << "\n";

    return 0;
}
