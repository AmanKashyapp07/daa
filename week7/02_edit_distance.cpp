/*
 * ============================================================================
 *  EDIT DISTANCE (Sequence Alignment)
 * ============================================================================
 *  PROBLEM:
 *  - Given two strings str1 and str2 and below operations that can be performed 
 *    on str1. Find minimum number of edits (operations) required to convert 
 *    'str1' into 'str2'.
 *  - Operations: Insert, Remove, Replace.
 *
 *  LOGIC:
 *  - Process characters from right to left (or left to right).
 *  - If last characters match, nothing to do: cost = 0 + cost of remaining.
 *  - If they don't match, we try all 3 operations and take the minimum cost:
 *    1. Insert:  EditDistance(i, j-1)
 *    2. Remove:  EditDistance(i-1, j)
 *    3. Replace: EditDistance(i-1, j-1)
 *
 *  SPACE OPTIMIZATION:
 *  - Just like LCS, to compute the current row `i`, we only need the previous 
 *    row `i-1`.
 *  - We can reduce O(M*N) space to O(N).
 *
 *  TIME COMPLEXITY:  O(M * N)
 *  SPACE COMPLEXITY: O(N) (using Space Optimization)
 *
 *  EXAM TIP:
 *  - Edit distance is heavily used in spell checkers, DNA sequence alignment 
 *    (Needleman-Wunsch algorithm), and natural language processing.
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
//  EDIT DISTANCE (Space-Optimized O(N))
// ─────────────────────────────────────────────────────────────────────────────
int editDistanceSpaceOptimized(string str1, string str2) {
    int m = str1.length();
    int n = str2.length();

    // Create a DP array to memoize result of previous computations
    vector<int> dp(n + 1, 0);

    // Initialize by converting empty str1 to str2 (requires 'j' insertions)
    for (int j = 0; j <= n; j++) {
        dp[j] = j;
    }

    for (int i = 1; i <= m; i++) {
        int prev = dp[0]; // Stores the value of dp[i-1][j-1]
        
        // Converting str1 of length 'i' to empty str2 requires 'i' deletions
        dp[0] = i; 

        for (int j = 1; j <= n; j++) {
            int temp = dp[j]; // Back up dp[i-1][j]

            if (str1[i - 1] == str2[j - 1]) {
                dp[j] = prev; // Characters match, no operation needed
            } else {
                dp[j] = 1 + min({
                    dp[j],      // Remove (dp[i-1][j])
                    dp[j - 1],  // Insert (dp[i][j-1])
                    prev        // Replace (dp[i-1][j-1])
                });
            }
            prev = temp; // Restore backup for next iteration
        }
    }

    return dp[n];
}

// ─────────────────────────────────────────────────────────────────────────────
//  DRIVER
// ─────────────────────────────────────────────────────────────────────────────
int main() {
    cout << "=== EDIT DISTANCE (Sequence Alignment) ===\n";
    string str1 = "intention";
    string str2 = "execution";

    cout << "String 1: " << str1 << "\n";
    cout << "String 2: " << str2 << "\n\n";

    cout << "Minimum Edits Required: " << editDistanceSpaceOptimized(str1, str2) << "\n";
    
    // Example trace for intention -> execution:
    // 1. intention -> inenion (remove 't')
    // 2. inenion -> exenion (replace 'i' with 'e', 'n' with 'x')
    // 3. exenion -> execution (insert 'c', 'u', replace 'n' with 't')
    // Wait, the optimal trace is 5 operations: 
    // i -> e, n -> x, t -> e (not needed since we have e), etc.
    // Minimum edits for this pair is exactly 5.

    return 0;
}
