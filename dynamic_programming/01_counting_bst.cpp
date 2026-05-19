/*
 * Counting Binary Search Trees (Catalan Numbers)
 *
 * Description:
 * Given an integer N, find the total number of structurally unique Binary Search Trees (BSTs)
 * that can be formed using N distinct nodes (e.g., values from 1 to N).
 * 
 * Logic (Dynamic Programming):
 * 1. For a given number of nodes 'i', we can dynamically choose any node 'j' (from 1 to i) to be the root.
 * 2. If 'j' is the root, there will be exactly (j-1) nodes restricted to the left subtree and (i-j) nodes 
 *    restricted to the right subtree.
 * 3. The total number of unique BSTs with 'j' as root is simply the product of the number of unique BSTs 
 *    possible in its left and right subtrees: DP[j-1] * DP[i-j].
 * 4. Therefore, total BSTs for 'i' nodes = Sum(DP[j-1] * DP[i-j]) for all j from 1 to i.
 * 5. This sequence perfectly models the recursive definition of Catalan numbers.
 *
 * Time Complexity: O(N^2) - Nested loop evaluating combinations for each state up to N.
 * Space Complexity: O(N) - 1D array to store the computed DP states.
 */

#include <iostream>
#include <vector>

using namespace std;

class CountBST {
public:
    int countUniqueBSTs(int n) {
        if (n <= 1) return 1;

        // DP array to store the number of unique BSTs for each node count
        vector<int> dp(n + 1, 0);

        // Base cases
        dp[0] = 1; // Empty tree counts as 1 valid structural arrangement
        dp[1] = 1; // Single node tree counts as 1 valid structural arrangement

        // Build the DP table bottom-up
        for (int i = 2; i <= n; i++) {
            // Treat each node 'j' from 1 to i as the explicit root
            for (int j = 1; j <= i; j++) {
                // dp[j-1] maps structural permutations of the left subtree
                // dp[i-j] maps structural permutations of the right subtree
                dp[i] += dp[j - 1] * dp[i - j];
            }
        }

        return dp[n];
    }
};

int main() {
    cout << "--- Counting Unique Binary Search Trees (DP) ---\n";
    CountBST solver;
    
    int n;
    cout << "Enter the number of nodes (N): ";
    
    // Read user input. Defaults to 5 if non-interactive environment
    if (!(cin >> n)) {
        n = 5; 
        cout << n << " (Auto-assigned)\n";
    }

    cout << "Total structurally unique BSTs for N = " << n << " is: " 
         << solver.countUniqueBSTs(n) << "\n";

    return 0;
}
