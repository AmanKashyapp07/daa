/*
 * Problem C: Activity Selection Problem (Greedy Approach)
 *
 * Logic:
 * The greedy choice is to always select the next possible activity that finishes 
 * earliest. This leaves the maximum possible time for remaining activities.
 * 1. Combine the start and finish times into a single structure/array.
 * 2. Sort the activities based on their finish times in ascending order.
 * 3. Select the first activity from the sorted list (it finishes first).
 * 4. For the remaining activities, select an activity if its start time is greater
 *    than or equal to the finish time of the previously selected activity.
 *
 * Time Complexity: O(N log N) to sort the activities.
 * Space Complexity: O(N) to store the combined activities.
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to represent an Activity
struct Activity {
    int id;
    int start;
    int finish;
};

// Comparator function to sort activities based on their finish times
bool compareActivities(const Activity& a, const Activity& b) {
    return a.finish < b.finish;
}

void printMaxActivities(const vector<int>& start, const vector<int>& finish) {
    int n = start.size();
    vector<Activity> activities(n);

    // Populate the activities
    for (int i = 0; i < n; i++) {
        activities[i].id = i + 1; // 1-based ID for tracking
        activities[i].start = start[i];
        activities[i].finish = finish[i];
    }

    // Sort activities based on finish time
    sort(activities.begin(), activities.end(), compareActivities);

    cout << "Selected Activities:\n";
    
    // The first activity is always selected greedily
    int last_selected_idx = 0;
    cout << "Activity " << activities[last_selected_idx].id 
         << " (Start: " << activities[last_selected_idx].start 
         << ", Finish: " << activities[last_selected_idx].finish << ")\n";

    int count = 1;

    // Iterate through the remaining sorted activities
    for (int i = 1; i < n; i++) {
        // If the start time of this activity is >= the finish time of 
        // the previously selected activity, then it's non-overlapping and we select it.
        if (activities[i].start >= activities[last_selected_idx].finish) { 
            cout << "Activity " << activities[i].id 
                 << " (Start: " << activities[i].start 
                 << ", Finish: " << activities[i].finish << ")\n";
            last_selected_idx = i;
            count++;
        }
    }

    cout << "\nResult: Maximum number of activities that can be performed: " << count << "\n";
}

int main() {
    cout << "--- Activity Selection Problem ---\n\n";
    
    // An example test case
    vector<int> start  = {1, 3, 0, 5, 8, 5};
    vector<int> finish = {2, 4, 6, 7, 9, 9};

    cout << "Start times:  "; for (int s : start) cout << s << " "; cout << "\n";
    cout << "Finish times: "; for (int f : finish) cout << f << " "; cout << "\n\n";

    printMaxActivities(start, finish);

    return 0;
}
