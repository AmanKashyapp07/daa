/*
 * ============================================================================
 *  GREEDY ALGORITHMS: INTERVAL SCHEDULING
 * ============================================================================
 *  CONCEPTS:
 *  - Greedy algorithms build up a solution piece by piece, always choosing the 
 *    next piece that offers the most immediate benefit.
 *  - They don't look ahead or reconsider previous choices.
 *
 *  REQUIRED PROPERTIES FOR GREEDY TO BE OPTIMAL:
 *  1. Greedy-Choice Property: A global optimum can be arrived at by selecting 
 *     a local optimum.
 *  2. Optimal Substructure: An optimal solution to the problem contains an 
 *     optimal solution to subproblems.
 *
 *  PROOF TECHNIQUES FOR GREEDY:
 *  1. "Greedy Stays Ahead": Show that at every step, the greedy choice is at 
 *     least as good as any other choice.
 *  2. "Exchange Argument": Assume an optimal solution exists that is different 
 *     from the greedy one. Show that you can swap out pieces of the optimal 
 *     solution for the greedy choices without degrading the overall quality, 
 *     proving the greedy solution is also optimal.
 *
 *  INTERVAL SCHEDULING PROBLEM:
 *  - Problem: Given a set of tasks with start times and finish times, find the 
 *    maximum number of compatible (non-overlapping) tasks you can perform.
 *  - Greedy Choice: Always pick the compatible task that FINISHES EARLIEST.
 *    (This leaves the maximum possible free time for the rest of the tasks).
 *  - Time Complexity: O(N log N) for sorting, then O(N) to select. Total O(N log N).
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

// Structure to represent an activity/task
struct Activity {
    string name;
    int start;
    int finish;
};

// Comparator function to sort activities by finish time
bool compareFinishTime(const Activity& a, const Activity& b) {
    return a.finish < b.finish;
}

// ─────────────────────────────────────────────────────────────────────────────
//  INTERVAL SCHEDULING (Activity Selection)
// ─────────────────────────────────────────────────────────────────────────────
void intervalScheduling(vector<Activity>& activities) {
    // 1. Sort the activities according to their finish time
    sort(activities.begin(), activities.end(), compareFinishTime);

    cout << "Selected Activities:\n";

    // 2. The first activity is always selected
    int last_selected_finish = activities[0].finish;
    cout << activities[0].name << " [" << activities[0].start << " - " << activities[0].finish << "]\n";
    int count = 1;

    // 3. Iterate through the rest of the activities
    for (int i = 1; i < activities.size(); i++) {
        // If this activity starts after or exactly when the last selected 
        // activity finished, it is compatible.
        if (activities[i].start >= last_selected_finish) {
            cout << activities[i].name << " [" << activities[i].start << " - " << activities[i].finish << "]\n";
            last_selected_finish = activities[i].finish;
            count++;
        }
    }
    
    cout << "Total maximum activities scheduled: " << count << "\n";
}

// ─────────────────────────────────────────────────────────────────────────────
//  DRIVER
// ─────────────────────────────────────────────────────────────────────────────
int main() {
    cout << "=== INTERVAL SCHEDULING ===\n";
    
    vector<Activity> activities = {
        {"A1", 1, 4},
        {"A2", 3, 5},
        {"A3", 0, 6},
        {"A4", 5, 7},
        {"A5", 3, 9},
        {"A6", 5, 9},
        {"A7", 6, 10},
        {"A8", 8, 11},
        {"A9", 8, 12},
        {"A10", 2, 14},
        {"A11", 12, 16}
    };

    intervalScheduling(activities);

    return 0;
}
