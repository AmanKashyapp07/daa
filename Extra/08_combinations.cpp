/*
 * Combinations (nCr)
 *
 * Description:
 * Given two integers n and k, return all possible combinations of k numbers out of the range [1, n].
 *
 * Time Complexity: O(k * C(n, k))
 * Space Complexity: O(k) for recursion stack and temporary subset array.
 */
#include <iostream>
#include <vector>

using namespace std;

class Combinations {
private:
    vector<vector<int>> results;

    void combineUtil(int n, int k, int start, vector<int>& current) {
        // Base case: If combination is of size k, we found a valid combination
        if (current.size() == k) {
            results.push_back(current);
            return;
        }

        // Try numbers from 'start' to 'n'
        for (int i = start; i <= n; i++) {
            current.push_back(i); // ASSIGN
            
            // RECURSE with i+1 to avoid duplicates/permutations and maintain strictly increasing order
            combineUtil(n, k, i + 1, current); 
            
            current.pop_back(); // BACKTRACK
        }
    }

public:
    void generate(int n, int k) {
        results.clear();
        vector<int> current;
        combineUtil(n, k, 1, current);

        cout << "Combinations of " << n << " choose " << k << ":\n";
        for (const auto& comb : results) {
            cout << "[ ";
            for (int x : comb) cout << x << " ";
            cout << "]\n";
        }
    }
};

int main() {
    cout << "--- Combinations nCr (Backtracking) ---\n";
    Combinations solver;
    solver.generate(4, 2); // '4 Choose 2' mathematically 
    return 0;
}
