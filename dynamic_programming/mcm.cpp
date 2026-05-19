/*
 * ============================================================================
 *  DP PATTERN 5: MATRIX CHAIN MULTIPLICATION (MCM) & INTERVAL DP
 * ============================================================================
 *  This pattern deals with interval structures, where we pick a splitting 
 *  point `k` between `i` and `j` and evaluate cost based on left and right parts.
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
//  1. MATRIX CHAIN MULTIPLICATION (MCM)
// ─────────────────────────────────────────────────────────────────────────────
int mcmMemo(const vector<int>& p, int i, int j, vector<vector<int>>& memo) {
    if (i >= j) return 0;
    if (memo[i][j] != -1) return memo[i][j];

    int min_cost = 9999999;
    for (int k = i; k <= j - 1; k++) {
        int cost = mcmMemo(p, i, k, memo) + 
                   mcmMemo(p, k + 1, j, memo) + 
                   (p[i - 1] * p[k] * p[j]);
        min_cost = min(min_cost, cost);
    }
    return memo[i][j] = min_cost;
}


// ─────────────────────────────────────────────────────────────────────────────
//  3. PALINDROME PARTITIONING
// ─────────────────────────────────────────────────────────────────────────────
bool isPalindrome(const string& s, int i, int j) {
    while (i < j) {
        if (s[i] != s[j]) return false;
        i++; j--;
    }
    return true;
}

int palindromePartitionMemo(const string& s, int i, int j, vector<vector<int>>& memo) {
    if (i >= j || isPalindrome(s, i, j)) return 0;
    if (memo[i][j] != -1) return memo[i][j];

    int min_cuts = 9999999;
    for (int k = i; k <= j - 1; k++) {
        // Optimization: check if left prefix is palindrome before recursively calling right
        if(isPalindrome(s, i, k)) {
            int cuts = 1 + palindromePartitionMemo(s, k + 1, j, memo);
            min_cuts = min(min_cuts, cuts);
        }
    }
    return memo[i][j] = min_cuts;
}

// ─────────────────────────────────────────────────────────────────────────────
//  4. BOOLEAN PARENTHESIZATION
// ─────────────────────────────────────────────────────────────────────────────
int boolParenthesizationMemo(const string& s, int i, int j, bool isTrue, vector<vector<vector<int>>>& memo) {
    if (i > j) return 0;
    if (i == j) {
        if (isTrue) return s[i] == 'T';
        else return s[i] == 'F';
    }

    if (memo[i][j][isTrue] != -1) return memo[i][j][isTrue];

    int ways = 0;
    // Operators are at k = i+1, i+3, ...
    for (int k = i + 1; k <= j - 1; k += 2) {
        int lT = boolParenthesizationMemo(s, i, k - 1, true, memo);
        int lF = boolParenthesizationMemo(s, i, k - 1, false, memo);
        int rT = boolParenthesizationMemo(s, k + 1, j, true, memo);
        int rF = boolParenthesizationMemo(s, k + 1, j, false, memo);

        if (s[k] == '&') {
            if (isTrue) ways += (lT * rT);
            else ways += (lT * rF) + (lF * rT) + (lF * rF);
        } 
        else if (s[k] == '|') {
            if (isTrue) ways += (lT * rT) + (lT * rF) + (lF * rT);
            else ways += (lF * rF);
        } 
        else if (s[k] == '^') {
            if (isTrue) ways += (lT * rF) + (lF * rT);
            else ways += (lT * rT) + (lF * rF);
        }
    }
    return memo[i][j][isTrue] = ways;
}

// ─────────────────────────────────────────────────────────────────────────────
//  DRIVER
// ─────────────────────────────────────────────────────────────────────────────
int main() {
    cout << "=== INTERVAL DP / MCM VARIATIONS (Recursion + Memoization) ===\n\n";

    vector<int> p = {40, 20, 30, 10, 30};
    int n = p.size() - 1;
    vector<vector<int>> memo1(n + 1, vector<int>(n + 1, -1));
    cout << "1. MCM Min Multiplications: " << mcmMemo(p, 1, n, memo1) << "\n";

    vector<int> freq = {34, 8, 50};
    vector<vector<int>> memo2(freq.size(), vector<int>(freq.size(), -1));
    cout << "2. Optimal BST Cost: " << obstMemo(freq, 0, freq.size() - 1, memo2) << "\n";

    string str = "ababbbabbababa";
    vector<vector<int>> memo3(str.length(), vector<int>(str.length(), -1));
    cout << "3. Min Palindrome Cuts: " << palindromePartitionMemo(str, 0, str.length() - 1, memo3) << "\n";

    string bool_expr = "T|T&F^T";
    int blen = bool_expr.length();
    vector<vector<vector<int>>> memo4(blen, vector<vector<int>>(blen, vector<int>(2, -1)));
    cout << "4. Boolean Parenthesization (True Ways): " << boolParenthesizationMemo(bool_expr, 0, blen - 1, true, memo4) << "\n";

    return 0;
}
