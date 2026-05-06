/*
 * ============================================================================
 *  MONTE CARLO AND LAS VEGAS ALGORITHMS
 * ============================================================================
 *  CONCEPTS:
 *  Randomized algorithms are generally classified into two types based on 
 *  where the randomness affects the algorithm: Time vs Correctness.
 *
 *  1. LAS VEGAS ALGORITHMS:
 *     - Correctness: ALWAYS produces the correct result (or informs of failure).
 *     - Execution Time: Random. The time taken depends on random choices.
 *     - Example: Randomized QuickSort. It will always sort the array correctly, 
 *       but its time complexity is O(N log N) expected, and O(N^2) in the 
 *       worst (highly unlucky) case.
 *
 *  2. MONTE CARLO ALGORITHMS:
 *     - Correctness: Output MAY BE incorrect with a certain probability.
 *     - Execution Time: Deterministic (always takes a fixed amount of time).
 *     - Amplification: We can run a Monte Carlo algorithm multiple times to 
 *       decrease the probability of failure to an infinitesimally small number.
 *     - Example: Karger's Min-Cut algorithm, Miller-Rabin Primality Test, 
 *       or estimating Pi using random points.
 *
 *  EXAM TIP:
 *  - "Las Vegas = Always Right, Time Gambles"
 *  - "Monte Carlo = Time Fixed, Correctness Gambles"
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
#include <cstdlib>
#include <ctime>

using namespace std;

// ─────────────────────────────────────────────────────────────────────────────
//  LAS VEGAS EXAMPLE: Randomized Search
// ─────────────────────────────────────────────────────────────────────────────
// Problem: Find the index of a target element in an array where we know the 
// target exists. 
// Las Vegas approach: Keep guessing random indices until we find it.
// Time: Expected O(N), Worst-case Infinite (if we are extremely unlucky).
// Correctness: Always correct (returns the valid index).
int lasVegasSearch(const vector<int>& arr, int target) {
    int N = arr.size();
    int attempts = 0;
    while (true) {
        attempts++;
        int guess_idx = rand() % N;
        if (arr[guess_idx] == target) {
            cout << "Las Vegas found target " << target << " at index " << guess_idx 
                 << " in " << attempts << " attempts.\n";
            return guess_idx;
        }
    }
}

// ─────────────────────────────────────────────────────────────────────────────
//  MONTE CARLO EXAMPLE: Estimating Pi
// ─────────────────────────────────────────────────────────────────────────────
// Problem: Estimate the value of Pi.
// Monte Carlo approach: Generate random points in a 1x1 square. The ratio of 
// points that fall inside the inscribed quarter-circle to the total points 
// approximates Pi / 4.
// Time: Fixed O(iterations).
// Correctness: Approximate. More iterations = higher probability of being close.
double monteCarloPiEstimation(int iterations) {
    int points_inside_circle = 0;

    for (int i = 0; i < iterations; ++i) {
        // Generate random x and y between 0.0 and 1.0
        double x = (double)rand() / RAND_MAX;
        double y = (double)rand() / RAND_MAX;

        // Check if point is inside the quarter-circle (x^2 + y^2 <= 1)
        if (x * x + y * y <= 1.0) {
            points_inside_circle++;
        }
    }

    // Ratio = Area of quarter circle / Area of square = (Pi * r^2 / 4) / r^2 = Pi / 4
    double pi_estimate = 4.0 * points_inside_circle / iterations;
    return pi_estimate;
}

// ─────────────────────────────────────────────────────────────────────────────
//  DRIVER
// ─────────────────────────────────────────────────────────────────────────────
int main() {
    srand(time(0));

    cout << "=== LAS VEGAS ALGORITHM (Random Search) ===\n";
    vector<int> arr = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    int target = 70;
    lasVegasSearch(arr, target);

    cout << "\n=== MONTE CARLO ALGORITHM (Estimating Pi) ===\n";
    int iters_small = 1000;
    int iters_large = 1000000;
    
    cout << "Estimate with " << iters_small << " iterations: " 
         << monteCarloPiEstimation(iters_small) << "\n";
    cout << "Estimate with " << iters_large << " iterations: " 
         << monteCarloPiEstimation(iters_large) << "\n";
    cout << "Actual Pi is roughly: 3.14159265...\n";

    return 0;
}
