/*
 * ============================================================================
 *  LONGEST COMMON SUBSEQUENCE (LCS)
 * ============================================================================
 *  PROBLEM:
 *  - Given two sequences, find the length of the longest subsequence present 
 *    in both of them.
 *  - A subsequence is a sequence that appears in the same relative order, but 
 *    not necessarily contiguous (unlike a substring).
 *
 *  LOGIC:
 *  - Let X[0..m-1] and Y[0..n-1] be the two sequences.
 *  - If last characters match (X[m-1] == Y[n-1]):
 *      LCS(X, Y) = 1 + LCS(X[0..m-2], Y[0..n-2])
 *  - If last characters do not match:
 *      LCS(X, Y) = max(LCS(X[0..m-2], Y[0..n-1]), LCS(X[0..m-1], Y[0..n-2]))
 *
 *  SPACE OPTIMIZATION:
 *  - Notice that to compute dp[i][j], we only need the current row dp[i] and 
 *    the previous row dp[i-1]. We don't need the entire M x N table.
 *  - We can reduce O(M*N) space to O(N) space using two 1D arrays or one 1D 
 *    array with a few temporary variables.
 *
 *  TIME COMPLEXITY:  O(M * N)
 *  SPACE COMPLEXITY: O(N) (Optimized), O(M * N) (Tabulation if printing is needed)
 *
 *  EXAM TIP:
 *  - Reconstructing the actual LCS string REQUIRES the full O(M*N) table 
 *    (or some advanced divide-and-conquer like Hirschberg's algorithm).
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
//  LCS LENGTH (Space-Optimized O(N))
// ─────────────────────────────────────────────────────────────────────────────
int lcsSpaceOptimized(string X, string Y) {
    int m = X.length(), n = Y.length();
    
    // dp[j] will store the LCS of X[0..i] and Y[0..j]
    vector<int> dp(n + 1, 0);

    for (int i = 1; i <= m; i++) {
        int prev = dp[0]; // Stores the value of dp[i-1][j-1]
        for (int j = 1; j <= n; j++) {
            int temp = dp[j]; // Back up dp[i-1][j] before overwriting

            if (X[i - 1] == Y[j - 1]) {
                dp[j] = prev + 1;
            } else {
                dp[j] = max(dp[j], dp[j - 1]);
            }
            prev = temp; // Restore backup for the next iteration's j-1
        }
    }
    return dp[n];
}

// ─────────────────────────────────────────────────────────────────────────────
//  PRINTING THE LCS (Requires full O(M*N) table)
// ─────────────────────────────────────────────────────────────────────────────
void printLCS(string X, string Y) {
    int m = X.length();
    int n = Y.length();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    // 1. Build the DP table
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (X[i - 1] == Y[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }

    // 2. Trace back to find the characters
    int index = dp[m][n];
    string lcs_str(index, ' '); 

    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            lcs_str[index - 1] = X[i - 1]; // Character belongs to LCS
            i--; j--; index--;
        } 
        else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--; // Move UP
        } 
        else {
            j--; // Move LEFT
        }
    }

    cout << "Length of LCS: " << dp[m][n] << "\n";
    cout << "LCS String: " << lcs_str << "\n";
}

// ─────────────────────────────────────────────────────────────────────────────
//  DRIVER
// ─────────────────────────────────────────────────────────────────────────────
int main() {
    cout << "=== LONGEST COMMON SUBSEQUENCE ===\n";
    string X = "AGGTAB";
    string Y = "GXTXAYB";
    
    cout << "String X: " << X << "\n";
    cout << "String Y: " << Y << "\n\n";

    cout << "Using Space Optimized DP: " << lcsSpaceOptimized(X, Y) << "\n";
    printLCS(X, Y);

    return 0;
}
