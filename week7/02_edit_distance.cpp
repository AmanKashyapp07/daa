#include <iostream>
#include <vector>
#include <string>

using namespace std;

int solve(int i, int j, string &s1, string &s2, vector<vector<int>> &dp) {
    if (i == s1.size()) return s2.size() - j;
    if (j == s2.size()) return s1.size() - i;

    if (dp[i][j] != -1) return dp[i][j];

    if (s1[i] == s2[j]) {
        return dp[i][j] = solve(i + 1, j + 1, s1, s2, dp);
    }

    int insertOp = solve(i, j + 1, s1, s2, dp);
    int deleteOp = solve(i + 1, j, s1, s2, dp);
    int replaceOp = solve(i + 1, j + 1, s1, s2, dp);

    return dp[i][j] = 1 + min(insertOp, min(deleteOp, replaceOp));
}

int editDistance(string s1, string s2) {
    int n = s1.size();
    int m = s2.size();

    vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));

    return solve(0, 0, s1, s2, dp);
}

int main() {
    string s1 = "intention";
    string s2 = "execution";

    cout << editDistance(s1, s2) << "\n";

    return 0;
}