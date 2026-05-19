/*
 * Problem B: Heap Sort using Min-Heap
 *
 * Performance Analysis:
 * - Building the Min-Heap takes O(N) time.
 * - We extract the minimum element N times. Each extraction takes O(log N) time.
 * - Total Time Complexity: O(N log N) in best, average, and worst cases.
 * - Space Complexity: O(1) auxiliary space (in-place sort).
 *   Note: Extracting the minimum element and placing it at the end sorts the
 *   array in descending order. A final O(N) reversal step provides ascending order.
 */

#include <stdio.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(int arr[], int n, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] < arr[smallest])
        smallest = left;

    if (right < n && arr[right] < arr[smallest])
        smallest = right;

    if (smallest != i) {
        swap(&arr[i], &arr[smallest]);
        minHeapify(arr, n, smallest);
    }
}

void heapSortAscending(int arr[], int n) {
    // 1. Build Min-Heap: O(N)
    for (int i = n / 2 - 1; i >= 0; i--) {
        minHeapify(arr, n, i);
    }

    // 2. Extract elements one by one
    // Extracting min places the smallest element at the back, 
    // ultimately sorting the array in DESCENDING order in-place!
    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]); // Move current root (min) to end
        minHeapify(arr, i, 0);  // MinHeapify the reduced heap
    }

    // 3. To get ascending order, reverse the array: O(N)
    for (int i = 0; i < n / 2; i++) {
        swap(&arr[i], &arr[n - 1 - i]);
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int arr[] = {50, 10, 20, 30, 5, 90, 80, 100, 85};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: \n");
    printArray(arr, n);

    heapSortAscending(arr, n);

    printf("Sorted array (Ascending via Min-Heap): \n");
    printArray(arr, n);

    return 0;
}
