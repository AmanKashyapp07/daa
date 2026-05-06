/*
 * ============================================================================
 *  INTERVAL SCHEDULING: EXAM PROOFS & APPLICATIONS
 * ============================================================================
 *  This file covers the 3 most heavily tested Interval/Scheduling problems.
 *  For exams, you must know BOTH the Greedy Strategy AND the Proof of Correctness.
 *
 * ─────────────────────────────────────────────────────────────────────────────
 *  APPLICATION 1: MAXIMUM COMPATIBLE INTERVALS (Standard Interval Scheduling)
 * ─────────────────────────────────────────────────────────────────────────────
 *  PROBLEM: Given N intervals, find the maximum number of mutually compatible intervals.
 *  GREEDY STRATEGY: Sort by Earliest Finish Time.
 *  
 *  PROOF OF CORRECTNESS (Greedy Stays Ahead):
 *  Let Greedy = {g1, g2, ..., gk} and Optimal = {o1, o2, ..., om}.
 *  Assume for contradiction that m > k (Optimal is better).
 *  We prove by induction that for all r <= k, finish(gr) <= finish(or).
 *  - Base Case (r=1): g1 is picked by Earliest Finish Time, so finish(g1) <= finish(o1).
 *  - Inductive Step: Assume finish(g_{r-1}) <= finish(o_{r-1}). 
 *    Since o_r is compatible with o_{r-1}, its start time >= finish(o_{r-1}) >= finish(g_{r-1}).
 *    Thus, o_r is also a valid choice for the greedy algorithm at step r.
 *    Since Greedy always picks the earliest finish time among valid choices, 
 *    finish(g_r) <= finish(o_r).
 *  - Conclusion: At step k, finish(g_k) <= finish(o_k). If Optimal has another 
 *    interval o_{k+1}, it starts after finish(o_k) >= finish(g_k). Thus, o_{k+1} 
 *    is compatible with g_k, meaning Greedy would not have stopped. Contradiction! 
 *    Therefore, k = m, and Greedy is optimal.
 *
 * ─────────────────────────────────────────────────────────────────────────────
 *  APPLICATION 2: INTERVAL PARTITIONING (Minimum Classrooms Problem)
 * ─────────────────────────────────────────────────────────────────────────────
 *  PROBLEM: Given N lectures, find the MINIMUM number of classrooms needed 
 *  to schedule all lectures so that no two overlap in the same room.
 *  
 *  GREEDY STRATEGY: Sort by Earliest Start Time. 
 *  Assign each lecture to an available room (using a Min-Heap of room finish times). 
 *  If no room is available, allocate a new one.
 *
 *  PROOF OF CORRECTNESS (Structural Lower Bound / Depth):
 *  - Let 'Depth' (d) be the maximum number of intervals that overlap at any single 
 *    point in time. Clearly, ANY valid schedule requires AT LEAST 'd' classrooms.
 *  - Suppose the Greedy algorithm allocates 'd_greedy' rooms. We must show d_greedy = d.
 *  - The algorithm only allocates a new room (room k) when an interval 'i' overlaps 
 *    with all (k-1) currently active rooms.
 *  - Because we sorted by start time, all (k-1) intervals currently in those rooms 
 *    started BEFORE or EXACTLY AT the start of 'i', and haven't finished yet.
 *  - Therefore, at the start time of interval 'i', there are exactly 'k' mutually 
 *    overlapping intervals. 
 *  - Thus, the graph has depth >= k. This means the number of rooms allocated 
 *    never exceeds the maximum depth of the intervals. Hence, Greedy is optimal.
 *
 * ─────────────────────────────────────────────────────────────────────────────
 *  APPLICATION 3: SCHEDULING TO MINIMIZE MAXIMUM LATENESS
 * ─────────────────────────────────────────────────────────────────────────────
 *  PROBLEM: Given N jobs with a processing time t_i and a deadline d_i. 
 *  Schedule all jobs sequentially starting at time 0 to minimize max(0, finish_i - d_i).
 *  
 *  GREEDY STRATEGY: Earliest Deadline First (EDF). Sort by deadlines.
 *
 *  PROOF OF CORRECTNESS (Exchange Argument):
 *  - An "inversion" in a schedule is a pair of jobs (i, j) where i is scheduled 
 *    before j, but deadline(i) > deadline(j).
 *  - The Greedy schedule has exactly 0 inversions.
 *  - Suppose there exists an Optimal schedule 'O' with inversions. There must 
 *    be an adjacent inversion (job i right before job j, but d_i > d_j).
 *  - If we swap job i and job j in 'O', the new schedule 'O_swapped' has one less inversion.
 *  - Analysis of the swap:
 *    * Jobs before j and after i are unaffected.
 *    * Job i now finishes later, but its new finish time is exactly the old finish time of j.
 *      Since d_i > d_j, the lateness of i in the new schedule is <= lateness of j in the old schedule.
 *    * Job j now finishes earlier, so its lateness decreases.
 *  - Therefore, swapping an inversion never increases the maximum lateness.
 *  - By repeatedly swapping all inversions, we transform 'O' into the Greedy 
 *    schedule without increasing maximum lateness. Thus, Greedy is optimal.
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
//  DATA STRUCTURES
// ─────────────────────────────────────────────────────────────────────────────
struct Lecture {
    int start;
    int finish;
    bool operator<(const Lecture& other) const {
        return start < other.start; // Sort by START time for partitioning
    }
};

struct Job {
    int duration;
    int deadline;
    bool operator<(const Job& other) const {
        return deadline < other.deadline; // Sort by DEADLINE for lateness
    }
};

// ─────────────────────────────────────────────────────────────────────────────
//  ALGORITHM: INTERVAL PARTITIONING (Minimum Classrooms)
// ─────────────────────────────────────────────────────────────────────────────
int minimumClassrooms(vector<Lecture>& lectures) {
    if (lectures.empty()) return 0;

    // 1. Sort by Start Time
    sort(lectures.begin(), lectures.end());

    // 2. Min-Heap to keep track of the earliest finishing room
    // The heap stores the finish times of all currently allocated rooms.
    priority_queue<int, vector<int>, greater<int>> minHeap;

    minHeap.push(lectures[0].finish);

    for (int i = 1; i < lectures.size(); i++) {
        // If the earliest finishing room is free before this lecture starts, reuse it.
        if (minHeap.top() <= lectures[i].start) {
            minHeap.pop(); 
        }
        // Regardless of reuse or new room, we push the new finish time.
        // If we popped, the size stays the same (reused). If we didn't, size increases (new room).
        minHeap.push(lectures[i].finish);
    }

    // The number of rooms allocated is the size of the heap
    return minHeap.size();
}

// ─────────────────────────────────────────────────────────────────────────────
//  ALGORITHM: MINIMIZING MAXIMUM LATENESS
// ─────────────────────────────────────────────────────────────────────────────
int minimizeLateness(vector<Job>& jobs) {
    // 1. Sort by Deadline (Earliest Deadline First)
    sort(jobs.begin(), jobs.end());

    int current_time = 0;
    int max_lateness = 0;

    cout << "\nJob Schedule:\n";
    for (int i = 0; i < jobs.size(); i++) {
        int start_time = current_time;
        current_time += jobs[i].duration; // finish time
        int lateness = max(0, current_time - jobs[i].deadline);
        
        max_lateness = max(max_lateness, lateness);

        cout << "Job " << i+1 << ": Start=" << start_time 
             << ", Finish=" << current_time 
             << ", Deadline=" << jobs[i].deadline 
             << ", Lateness=" << lateness << "\n";
    }

    return max_lateness;
}

// ─────────────────────────────────────────────────────────────────────────────
//  DRIVER
// ─────────────────────────────────────────────────────────────────────────────
int main() {
    cout << "=== APPLICATION 2: INTERVAL PARTITIONING ===\n";
    vector<Lecture> lectures = {
        {0, 30}, {5, 10}, {15, 20}, {10, 25}, {25, 30}
    };
    // Expected Depth/Classrooms = 3 (At time 16, [0,30], [10,25], [15,20] overlap)
    int rooms = minimumClassrooms(lectures);
    cout << "Minimum classrooms required: " << rooms << "\n";

    cout << "\n=== APPLICATION 3: MINIMIZING LATENESS ===\n";
    vector<Job> jobs = {
        {3, 6},   // Job 1: duration 3, deadline 6
        {2, 8},   // Job 2: duration 2, deadline 8
        {1, 9},   // Job 3: duration 1, deadline 9
        {4, 9},   // Job 4: duration 4, deadline 9
        {3, 14},  // Job 5: duration 3, deadline 14
        {2, 15}   // Job 6: duration 2, deadline 15
    };
    int maxLateness = minimizeLateness(jobs);
    cout << "Maximum Lateness across all jobs: " << maxLateness << "\n";

    return 0;
}
