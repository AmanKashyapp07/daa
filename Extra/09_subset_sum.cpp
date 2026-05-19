/*
 * Subset Sum Problem
 *
 * Description:
 * Given a set of non-negative integers, and a value sum, determine if there is a subset 
 * of the given set with sum equal to given sum. 
 * Note: This implementation finds ALL valid subsets utilizing explicit Include/Exclude binary trees.
 *
 * Time Complexity: O(2^N) - We explore an include/exclude binary branch for each element.
 * Space Complexity: O(N) - Recursion stack depth.
 */
#include <iostream>
#include <vector>

using namespace std;

class SubsetSum {
private:
    vector<vector<int>> validSubsets;

    void findSubsets(const vector<int>& set, int target, int currentSum, int index, vector<int>& subset) {
        // Base case: successfully found an exact sum matching the target
        if (currentSum == target) {
            validSubsets.push_back(subset);
            // We shouldn't return immediately if there are '0's in the array as adding 0 keeps the sum valid.
        }
        
        // Base case: bounds exceeded or array exhausted
        if (currentSum > target || index >= set.size()) {
            return;
        }

        // Path 1: INCLUDE the current element
        subset.push_back(set[index]);
        findSubsets(set, target, currentSum + set[index], index + 1, subset);
        
        // Path 2: EXCLUDE the current element (BACKTRACK)
        subset.pop_back();
        findSubsets(set, target, currentSum, index + 1, subset);
    }

public:
    void solve(const vector<int>& set, int target) {
        validSubsets.clear();
        vector<int> subset;
        findSubsets(set, target, 0, 0, subset);

        if (validSubsets.empty()) {
            cout << "No subset with sum " << target << " found.\n";
        } else {
            cout << "Subsets that sum to " << target << " (" << validSubsets.size() << " found):\n";
            for (const auto& sub : validSubsets) {
                cout << "{ ";
                for (int x : sub) cout << x << " ";
                cout << "}\n";
            }
        }
    }
};

int main() {
    cout << "--- Subset Sum Problem (Backtracking) ---\n";
    vector<int> set = {10, 7, 5, 18, 12, 20, 15};
    int target = 35;
    
    SubsetSum solver;
    solver.solve(set, target);
    
    return 0;
}
