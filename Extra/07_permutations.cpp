/*
 * String/Array Permutations
 *
 * Description:
 * Generate all possible permutations of a given string using backtracking.
 *
 * Time Complexity: O(N * N!) - N! permutations, takes O(N) to print/store each.
 * Space Complexity: O(N) - Recursion stack depth.
 */
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Permutations {
private:
    vector<string> results;

    void permute(string& str, int left, int right) {
        if (left == right) {
            results.push_back(str);
            return;
        }

        for (int i = left; i <= right; i++) {
            // SWAP to place element
            swap(str[left], str[i]);

            // RECURSE
            permute(str, left + 1, right);

            // BACKTRACK (restore original string structure)
            swap(str[left], str[i]);
        }
    }

public:
    void generate(string str) {
        results.clear();
        permute(str, 0, str.length() - 1);
        
        cout << "Total Permutations for '" << str << "': " << results.size() << "\n";
        for (const string& p : results) {
            cout << p << "\n";
        }
    }
};

int main() {
    cout << "--- Permutations (Backtracking) ---\n";
    Permutations solver;
    solver.generate("ABC");
    return 0;
}
