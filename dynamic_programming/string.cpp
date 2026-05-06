/*
 * ============================================================================
 *  DP PATTERN 6: STRING/MISC DP (Word Break, Egg Dropping)
 * ============================================================================
 *  APPROACH: Recursion + Memoization (Top-Down)
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_set>

using namespace std;

// ─────────────────────────────────────────────────────────────────────────────
//  1. WORD BREAK PROBLEM
// ─────────────────────────────────────────────────────────────────────────────
// problem statement : Given a string s and a dictionary of words dict, determine if s can be segmented into a space-separated sequence of one or more 
// dictionary words. For example, if s = "leetcode" and dict = ["leet", "code"], then the output should be true because "leetcode" can be segmented as "leet code". If s = "applepenapple" and dict = ["apple", "pen"], then the output should be true because "applepenapple" can be segmented as "apple pen apple". 
// If s = "catsandog" and dict = ["cats", "dog", "sand", "and", "cat"], then the output should be false because there is no way to segment "catsandog" into a sequence of dictionary words.
bool wordBreakMemo(const string& s, int start, const unordered_set<string>& dict, vector<int>& memo) {
    if (start == s.length()) return true;
    if (memo[start] != -1) return memo[start];

    // Try all possible prefixes
    for (int end = start + 1; end <= s.length(); end++) {
        string prefix = s.substr(start, end - start);
        if (dict.find(prefix) != dict.end()) { // If prefix is in dictionary, recursively check for the remaining suffix
            if (wordBreakMemo(s, end, dict, memo)) { // If suffix can also be segmented, we found a valid segmentation
                return memo[start] = 1; // Mark this index as true in memo and return
            }
        }
    }
    return memo[start] = 0;
}

// ─────────────────────────────────────────────────────────────────────────────
//  2. EGG DROPPING PROBLEM (Min-Max DP)
// ─────────────────────────────────────────────────────────────────────────────
// problem statement : You are given K eggs, and you have access to a building with N floors from 1 to N. Each egg is identical in function, and if an egg breaks when dropped from a certain floor, it will break if dropped from any higher floor. If an egg doesn't break when dropped from a certain floor, it will not break if dropped from any lower floor. Your task is to determine the minimum number of drops required to find the critical floor F, where 0 <= F <= N, such that any egg dropped from a floor higher than F will break, and any egg dropped from a floor at or below F will not break.

int eggDropMemo(int eggs, int floors, vector<vector<int>>& memo) {
    if (floors == 0 || floors == 1) return floors;
    if (eggs == 1) return floors;

    if (memo[eggs][floors] != -1) return memo[eggs][floors];

    int min_trials = 9999999;

    for (int x = 1; x <= floors; x++) {
        int breaks = eggDropMemo(eggs - 1, x - 1, memo); // If egg breaks, we have one less egg and we need to check the floors below x
        int survives = eggDropMemo(eggs, floors - x, memo); // If egg survives, we still have the same number of eggs and we need to check the floors above x
        
        int res = 1 + max(breaks, survives); // 
        min_trials = min(min_trials, res);
    }

    return memo[eggs][floors] = min_trials;
}

// ─────────────────────────────────────────────────────────────────────────────
//  DRIVER
// ─────────────────────────────────────────────────────────────────────────────
int main() {
    cout << "=== MISC DP (Recursion + Memoization) ===\n\n";

    unordered_set<string> dict = {"i", "like", "sam", "sung", "samsung", "mobile", "ice", "cream", "icecream", "man", "go", "mango"};
    string s = "ilikesamsung";
    vector<int> memo1(s.length(), -1);
    cout << "1. Word Break ('" << s << "'): " << (wordBreakMemo(s, 0, dict, memo1) ? "True" : "False") << "\n";

    int eggs = 2;
    int floors = 36;
    vector<vector<int>> memo2(eggs + 1, vector<int>(floors + 1, -1));
    cout << "2. Egg Dropping (Eggs=" << eggs << ", Floors=" << floors << "): " << eggDropMemo(eggs, floors, memo2) << " trials\n";

    return 0;
}
