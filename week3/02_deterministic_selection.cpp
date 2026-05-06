/*
 * ============================================================================
 *  DETERMINISTIC SELECTION (Median of Medians)
 * ============================================================================
 *  PROBLEM:
 *  - Find the k-th smallest element in an unsorted array.
 *  - Randomized QuickSelect (from Week 11) is expected O(N) but worst-case O(N^2).
 *  - The Median of Medians algorithm guarantees worst-case O(N) time.
 *
 *  LOGIC:
 *  - Standard QuickSelect suffers if we pick a bad pivot (e.g., maximum element).
 *  - Median of Medians ensures we pick a "good" pivot that is guaranteed to 
 *    eliminate a constant fraction of elements (at least 30%).
 *  
 *  STEPS:
 *  1. Divide the array into groups of 5 elements.
 *  2. Find the median of each group by simply sorting it.
 *  3. Recursively find the median of these medians. This is our pivot.
 *  4. Partition the array around this pivot.
 *  5. Recursively call the algorithm on the correct partition.
 *
 *  TIME COMPLEXITY: O(N) guaranteed.
 *  SPACE COMPLEXITY: O(N) due to recursion stack and median array.
 *
 *  EXAM TIP:
 *  - Although it guarantees O(N), Median of Medians has a very large constant 
 *    factor and is slower than Randomized QuickSelect in practice.
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
//  DETERMINISTIC SELECTION IMPLEMENTATION
// ─────────────────────────────────────────────────────────────────────────────
// Helper function to find the median of a small array (size <= 5)
int findMedian(vector<int>& arr, int start, int end) {
    sort(arr.begin() + start, arr.begin() + end + 1);
    return arr[start + (end - start) / 2];
}

// Standard partition function but pivots around a SPECIFIC value 'x'
int partitionAroundValue(vector<int>& arr, int low, int high, int x) {
    // Find x in the array and swap it to the end
    for (int i = low; i <= high; i++) {
        if (arr[i] == x) {
            swap(arr[i], arr[high]);
            break;
        }
    }

    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Main Median of Medians function
int deterministicSelect(vector<int>& arr, int low, int high, int k) {
    if (low == high) return arr[low];

    int n = high - low + 1;

    // 1. Divide into groups of 5 and find medians
    vector<int> medians;
    for (int i = 0; i < n / 5; i++) {
        medians.push_back(findMedian(arr, low + i * 5, low + i * 5 + 4));
    }
    if (n % 5 != 0) {
        medians.push_back(findMedian(arr, low + n / 5 * 5, high));
    }

    // 2. Recursively find the median of medians
    int medOfMed = (medians.size() == 1) ? medians[0] : 
                   deterministicSelect(medians, 0, medians.size() - 1, medians.size() / 2 + 1);

    // 3. Partition array around the median of medians
    int pi = partitionAroundValue(arr, low, high, medOfMed);

    // 4. Recurse appropriately
    int left_count = pi - low + 1;
    if (k == left_count) {
        return arr[pi];
    } else if (k < left_count) {
        return deterministicSelect(arr, low, pi - 1, k);
    } else {
        return deterministicSelect(arr, pi + 1, high, k - left_count);
    }
}

// ─────────────────────────────────────────────────────────────────────────────
//  DRIVER
// ─────────────────────────────────────────────────────────────────────────────
int main() {
    cout << "=== DETERMINISTIC SELECTION (Median of Medians) ===\n";
    vector<int> arr = {12, 3, 5, 7, 4, 19, 26, 15, 2, 8, 20, 11};
    int k = 4; // Find 4th smallest element
    
    cout << "Array: ";
    for (int x : arr) cout << x << " ";
    cout << "\n";

    // Create a copy for sorting to verify
    vector<int> sorted_arr = arr;
    sort(sorted_arr.begin(), sorted_arr.end());
    cout << "Sorted to verify: ";
    for (int x : sorted_arr) cout << x << " ";
    cout << "\n\n";

    int kth_smallest = deterministicSelect(arr, 0, arr.size() - 1, k);
    cout << "The " << k << "th smallest element is: " << kth_smallest << "\n";

    return 0;
}
