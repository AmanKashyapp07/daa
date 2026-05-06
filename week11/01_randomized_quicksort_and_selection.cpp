/*
 * ============================================================================
 *  RANDOMIZED QUICKSORT & RANDOMIZED SELECTION
 * ============================================================================
 *  CONCEPTS:
 *  - Randomized Algorithms use a degree of randomness as part of their logic.
 *  - The goal is to improve the EXPECTED time complexity, avoiding worst-case
 *    scenarios that occur due to structured/adversarial inputs.
 *
 *  1. RANDOMIZED QUICKSORT:
 *  - Standard QuickSort uses the last (or first) element as a pivot. If the 
 *    input is already sorted, this leads to O(N^2) worst-case time.
 *  - Randomized QuickSort picks a RANDOM element as the pivot and swaps it 
 *    with the last element before partitioning.
 *  - Expected Time Complexity: O(N log N)
 *  - Worst-Case Time Complexity: O(N^2) (But probability is astronomically low)
 *  - Space Complexity: O(log N) for recursion stack.
 *
 *  2. RANDOMIZED SELECTION (QuickSelect):
 *  - Problem: Find the k-th smallest element in an unordered array.
 *  - Logic: Similar to QuickSort, but we only recurse into the partition 
 *    that contains the k-th element.
 *  - Expected Time Complexity: O(N)
 *  - Worst-Case Time Complexity: O(N^2)
 *
 *  EXPECTED-TIME ANALYSIS (QuickSort):
 *  - We analyze the expected number of comparisons.
 *  - The probability that the i-th smallest and j-th smallest elements are 
 *    compared is exactly 2 / (j - i + 1), 
 *  - proof : Consider the subarray that contains elements from i to j. The first pivot chosen from this subarray will determine whether i and j are compared. If the pivot is i or j, they are compared. If the pivot is any element between i and j, then i and j will be in different partitions and will never be compared. Since there are (j - i + 1) elements in the subarray, the probability of choosing either i or j as the pivot is 2 / (j - i + 1).
 *  - Summing this over all pairs gives O(N log N) expected comparisons.
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
//  PARTITION LOGIC (Shared by QuickSort and QuickSelect)
// ─────────────────────────────────────────────────────────────────────────────
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high]; // Pivot is now at the end
    int i = low - 1;       // Index of smaller element

    for (int j = low; j < high; ++j) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Randomized Partition: Picks a random pivot and swaps it to the end
int randomizedPartition(vector<int>& arr, int low, int high) {
    // Generate random index between low and high
    int random_idx = low + rand() % (high - low + 1);
    
    // Swap random pivot with the last element
    swap(arr[random_idx], arr[high]);
    
    // Call standard partition
    return partition(arr, low, high);
}

// ─────────────────────────────────────────────────────────────────────────────
//  RANDOMIZED QUICKSORT
// ─────────────────────────────────────────────────────────────────────────────
void randomizedQuickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = randomizedPartition(arr, low, high);

        // Recursively sort elements before and after partition
        randomizedQuickSort(arr, low, pi - 1);
        randomizedQuickSort(arr, pi + 1, high);
    }
}

// ─────────────────────────────────────────────────────────────────────────────
//  RANDOMIZED SELECTION (QuickSelect)
// ─────────────────────────────────────────────────────────────────────────────
// Returns the k-th smallest element of array. (k is 1-based index)
int randomizedSelect(vector<int>& arr, int low, int high, int k) {
    if (low == high) {
        return arr[low];
    }

    int pi = randomizedPartition(arr, low, high);

    // Number of elements in the left partition (including pivot)
    int left_count = pi - low + 1;

    if (k == left_count) {
        return arr[pi]; // The pivot is exactly the k-th element
    } else if (k < left_count) {
        // The k-th element is in the left partition
        return randomizedSelect(arr, low, pi - 1, k);
    } else {
        // The k-th element is in the right partition.
        // We adjust k because we are ignoring the left_count elements.
        return randomizedSelect(arr, pi + 1, high, k - left_count);
    }
}

// ─────────────────────────────────────────────────────────────────────────────
//  DRIVER
// ─────────────────────────────────────────────────────────────────────────────
int main() {
    // Seed random number generator
    srand(time(0));

    cout << "=== RANDOMIZED QUICKSORT ===\n";
    vector<int> arr1 = {10, 7, 8, 9, 1, 5};
    cout << "Original Array: ";
    for (int x : arr1) cout << x << " ";
    cout << "\n";

    randomizedQuickSort(arr1, 0, arr1.size() - 1);

    cout << "Sorted Array:   ";
    for (int x : arr1) cout << x << " ";
    cout << "\n\n";

    cout << "=== RANDOMIZED SELECTION ===\n";
    vector<int> arr2 = {12, 3, 5, 7, 4, 19, 26};
    int k = 3; // Find the 3rd smallest element
    cout << "Array: ";
    for (int x : arr2) cout << x << " ";
    cout << "\n";

    int kth_smallest = randomizedSelect(arr2, 0, arr2.size() - 1, k);
    cout << "The " << k << "rd smallest element is: " << kth_smallest << "\n";

    return 0;
}
