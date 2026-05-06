/*
 * ============================================================================
 *  SORTING LOWER BOUNDS & HEAPSORT
 * ============================================================================
 *  1. LOWER BOUNDS FOR COMPARISON-BASED SORTING:
 *     - Any comparison-based sorting algorithm can be modeled as a Decision Tree.
 *     - A tree for sorting N elements must have at least N! leaves (all 
 *       possible permutations).
 *     - A binary tree with N! leaves must have a height of at least log2(N!).
 *     - By Stirling's approximation, log(N!) is Theta(N log N).
 *     - CONCLUSION: No comparison-based sort can be faster than O(N log N) 
 *       in the worst case. (Examples: MergeSort, HeapSort).
 *
 *  2. HEAPSORT:
 *     - Uses a Binary Max-Heap.
 *     - Step 1: Build a Max-Heap from the array. This takes O(N) time using 
 *       bottom-up heapify.
 *     - Step 2: Swap the root (maximum element) with the last element of the 
 *       heap, reduce the heap size by 1, and heapify the new root down. 
 *       Repeat N-1 times. Each extraction takes O(log N).
 *     - Total Time Complexity: O(N) + O(N log N) = O(N log N).
 *     - Space Complexity: O(1) in-place.
 *
 *  EXAM TIP:
 *  - HeapSort is in-place (unlike MergeSort) and has a guaranteed O(N log N) 
 *    worst-case (unlike QuickSort). However, it is often slower than QuickSort 
 *    in practice because of poor cache locality (nodes are far apart in array).
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
//  HEAPSORT IMPLEMENTATION
// ─────────────────────────────────────────────────────────────────────────────
// To heapify a subtree rooted with node i which is an index in arr[].
// n is size of heap
void heapify(vector<int>& arr, int n, int i) {
    int largest = i;       // Initialize largest as root
    int left = 2 * i + 1;  // left child index
    int right = 2 * i + 2; // right child index

    // If left child is larger than root
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    // If right child is larger than largest so far
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    // If largest is not root
    if (largest != i) {
        swap(arr[i], arr[largest]);

        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}

void heapSort(vector<int>& arr) {
    int n = arr.size();

    // 1. Build Max-Heap (rearrange array)
    // Start from the last non-leaf node and heapify each node up to root
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    // 2. Extract elements from heap one by one
    for (int i = n - 1; i > 0; i--) {
        // Move current root (maximum) to the end of the array
        swap(arr[0], arr[i]);

        // Call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}

// ─────────────────────────────────────────────────────────────────────────────
//  DRIVER
// ─────────────────────────────────────────────────────────────────────────────
int main() {
    cout << "=== HEAP SORT ===\n";
    vector<int> arr = {12, 11, 13, 5, 6, 7};
    
    cout << "Original array: ";
    for (int x : arr) cout << x << " ";
    cout << "\n";

    heapSort(arr);

    cout << "Sorted array:   ";
    for (int x : arr) cout << x << " ";
    cout << "\n";

    return 0;
}
