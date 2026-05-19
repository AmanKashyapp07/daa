/**
 * ============================================================================
 *  COMPREHENSIVE SORTING ALGORITHMS (EXAM PREP)
 * ============================================================================

 *  Algorithm    | Best Time | Avg Time | Worst Time | Space | Stable? |
 *  -------------|-----------|----------|------------|-------|---------|
 *  Bubble Sort  | O(N)      | O(N^2)   | O(N^2)     | O(1)  | Yes     |
 *  Selection Sort| O(N^2)   | O(N^2)   | O(N^2)     | O(1)  | No      |
 *  Insertion Sort| O(N)     | O(N^2)   | O(N^2)     | O(1)  | Yes     |
 *  Merge Sort   | O(NlogN)  | O(NlogN) | O(NlogN)   | O(N)  | Yes     |
 *  Quick Sort   | O(NlogN)  | O(NlogN) | O(N^2)     | O(logN)| No     |
 *  Counting Sort| O(N+K)    | O(N+K)   | O(N+K)     | O(N+K)| Yes     |
 *  Radix Sort   | O(d*(N+K))|O(d*(N+K))| O(d*(N+K)) | O(N+K)| Yes     |
 *  Bucket Sort  | O(N+K)    | O(N+K)   | O(N^2)     | O(N+K)| Yes     |
 *  Heap Sort*   | O(NlogN)  | O(NlogN) | O(NlogN)   | O(1)  | No      |
 *  
 *  TERMINOLOGY:
 *  - "Stable": If two elements have the same value, their relative order is 
 *    preserved in the sorted array.
 *  - "In-place": Uses strictly O(1) or O(log N) auxiliary space (recursion stack).
 *
 *  EXAM TIP:
 *  - If the array is "almost sorted", Insertion Sort is the fastest (O(N)).
 *  - Merge Sort is preferred for Linked Lists (doesn't need random access O(N) space).
 *  - Quick Sort is preferred for Arrays due to excellent cache locality.
 *  - Radix Sort is preferred when numbers are large but the number of digits 'd' is small.
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

// Helper to print array
template <typename T>
void printArray(const vector<T>& arr, string name) {
    cout << name << ": ";
    for (T x : arr) cout << x << " ";
    cout << "\n";
}

// ─────────────────────────────────────────────────────────────────────────────
//  1. BUBBLE SORT
//  Logic: Repeatedly swap adjacent elements if they are in wrong order.
//  Optimization: If no swaps occur in a pass, the array is sorted.
// ─────────────────────────────────────────────────────────────────────────────
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    bool swapped;
    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break; // Optimization
    }
}

// ─────────────────────────────────────────────────────────────────────────────
//  2. SELECTION SORT
//  Logic: Repeatedly find the minimum element from the unsorted part and 
//  put it at the beginning. Does at most O(N) swaps.
// ─────────────────────────────────────────────────────────────────────────────
void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            swap(arr[i], arr[min_idx]);
        }
    }
}

// ─────────────────────────────────────────────────────────────────────────────
//  3. INSERTION SORT
//  Logic: Build the sorted array one element at a time by picking the next 
//  element and inserting it into its correct position in the sorted part.
// ─────────────────────────────────────────────────────────────────────────────
void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// ─────────────────────────────────────────────────────────────────────────────
//  4. MERGE SORT
//  Logic: Divide and Conquer. Split array in half, recursively sort both 
//  halves, then merge the two sorted halves into a temporary array.
// ─────────────────────────────────────────────────────────────────────────────
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++) L[i] = arr[left + i]; // Copy left half
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j]; // Copy right half

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) { // <= ensures stability
            arr[k++] = L[i++]; // Copy from left half
        } else {
            arr[k++] = R[j++]; // Copy from right half
        }
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(vector<int>& arr, int left, int right) {
    while (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid); 
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// ─────────────────────────────────────────────────────────────────────────────
//  5. QUICK SORT
//  Logic: Divide and Conquer. Pick a pivot, partition the array so that 
//  elements smaller than pivot are on left, and greater are on right. Recurse.
// ─────────────────────────────────────────────────────────────────────────────
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high]; // Choosing last element as pivot
    int i = low - 1; // i denotes boundary of elements smaller than pivot, while j is the current element being compared
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) { // Strictly less than ensures better performance on duplicates
            i++; // Increment index of smaller element
            swap(arr[i], arr[j]); // increase the bounary of smaller elements and swap the current element with the element at the boundary
        }
    }
    // at the end of the loop, all elements smaller than pivot are on the left of index i, and all elements greater than or equal to pivot are on the right of index i. Now we need to place the pivot in its correct position by swapping it with the element at index i + 1
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// ─────────────────────────────────────────────────────────────────────────────
//  6. COUNTING SORT (Non-Comparison Sort)
//  Logic: Count the frequency of each distinct element, compute prefix sums 
//  to determine positions, and place elements into a new array.
//  Time: O(N + K) where K is the maximum element. Good when K is small.
// ─────────────────────────────────────────────────────────────────────────────
void countingSort(vector<int>& arr) {
    if (arr.empty()) return;
    int max_val = *max_element(arr.begin(), arr.end());
    
    vector<int> count(max_val + 1, 0);
    vector<int> output(arr.size());

    // Store count of each element
    for (int i = 0; i < arr.size(); i++) {
        count[arr[i]]++;
    }

    // Change count[i] so that count[i] contains actual position of this element
    for (int i = 1; i <= max_val; i++) {
        count[i] += count[i - 1];
    }

    // Build the output array (iterate backwards to maintain STABILITY)
    for (int i = arr.size() - 1; i >= 0; i--) {
        output[count[arr[i]] - 1] = arr[i]; // count[arr[i]] is the position of this element in output
        count[arr[i]]--;
    }

    // Copy back
    for (int i = 0; i < arr.size(); i++) {
        arr[i] = output[i];
    }
}

// ─────────────────────────────────────────────────────────────────────────────
//  7. RADIX SORT (Non-Comparison Sort)
//  Logic: Does digit by digit sort starting from least significant digit to 
//  most significant digit. Uses Counting Sort as a stable subroutine.
//  Time: O(d * (N + K)) where d is the number of digits.
// ─────────────────────────────────────────────────────────────────────────────
void countingSortForRadix(vector<int>& arr, int exp) {
    int n = arr.size();
    vector<int> output(n);
    vector<int> count(10, 0);

    // Store count of occurrences in count[] based on the current digit (exp)
    for (int i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    // Change count[i] so that count[i] now contains actual position
    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // Build the output array (backward iteration to maintain stability)
    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    // Copy the output array to arr[]
    for (int i = 0; i < n; i++)
        arr[i] = output[i];
}

void radixSort(vector<int>& arr) {
    if (arr.empty()) return;
    int max_val = *max_element(arr.begin(), arr.end());

    // Do counting sort for every digit. 
    // exp is 10^i where i is current digit number.
    for (int exp = 1; max_val / exp > 0; exp *= 10) {
        countingSortForRadix(arr, exp);
    }
}

// ─────────────────────────────────────────────────────────────────────────────
//  8. BUCKET SORT (For floating point numbers [0, 1))
//  Logic: Divides the range into N buckets, distributes elements into buckets, 
//  sorts individual buckets (usually with Insertion Sort), and concatenates them.
//  Time: Average O(N + K), Worst O(N^2) if all elements fall in one bucket.
// ─────────────────────────────────────────────────────────────────────────────
void bucketSort(vector<float>& arr) {
    int n = arr.size();
    if (n <= 0) return;

    // 1. Create n empty buckets
    vector<vector<float>> buckets(n);

    // 2. Put array elements in different buckets
    for (int i = 0; i < n; i++) {
        // Multiply by n to get the bucket index
        int bucket_idx = n * arr[i]; 
        
        // Handle edge case where element is exactly 1.0 (should not happen if [0, 1))
        if(bucket_idx >= n) bucket_idx = n - 1; 
        
        buckets[bucket_idx].push_back(arr[i]);
    }

    // 3. Sort individual buckets (Insertion sort is typically used)
    for (int i = 0; i < n; i++) {
        sort(buckets[i].begin(), buckets[i].end()); 
    }

    // 4. Concatenate all buckets into arr[]
    int index = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < buckets[i].size(); j++) {
            arr[index++] = buckets[i][j];
        }
    }
}

// ─────────────────────────────────────────────────────────────────────────────
//  DRIVER
// ─────────────────────────────────────────────────────────────────────────────
int main() {
    cout << "=== COMPREHENSIVE SORTING ALGORITHMS ===\n\n";

    vector<int> original = {64, 34, 25, 12, 22, 11, 90, 11};
    printArray(original, "Original Array");

    vector<int> arr;

    arr = original;
    bubbleSort(arr);
    printArray(arr, "Bubble Sort   ");

    arr = original;
    selectionSort(arr);
    printArray(arr, "Selection Sort");

    arr = original;
    insertionSort(arr);
    printArray(arr, "Insertion Sort");

    arr = original;
    mergeSort(arr, 0, arr.size() - 1);
    printArray(arr, "Merge Sort    ");

    arr = original;
    quickSort(arr, 0, arr.size() - 1);
    printArray(arr, "Quick Sort    ");

    arr = original;
    countingSort(arr);
    printArray(arr, "Counting Sort ");

    arr = original;
    radixSort(arr);
    printArray(arr, "Radix Sort    ");

    cout << "\n=== BUCKET SORT (For floats [0, 1)) ===\n";
    vector<float> float_arr = {0.897, 0.565, 0.656, 0.1234, 0.665, 0.3434};
    printArray(float_arr, "Original Floats");
    bucketSort(float_arr);
    printArray(float_arr, "Bucket Sort    ");

    return 0;
}
