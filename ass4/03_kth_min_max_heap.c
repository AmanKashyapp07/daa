/*
 * Problem C: Find K-th Minimum Element using Max-Heap
 *
 * Logic:
 * 1. Create a Max-Heap of the first K elements. (Time: O(K))
 * 2. For each of the remaining N-K elements:
 *    - If the element is smaller than the root (maximum) of the Max-Heap,
 *      replace the root with this element and max-heapify. (Time: O((N-K) log K))
 * 3. After the loop, the root of the Max-Heap will be the K-th minimum element.
 * 
 * Total Time Complexity: O(K + (N-K) log K).
 * Space Complexity: O(K) for the Max-Heap array.
 */

#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void maxHeapify(int heap[], int size, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < size && heap[left] > heap[largest])
        largest = left;

    if (right < size && heap[right] > heap[largest])
        largest = right;

    if (largest != i) {
        swap(&heap[i], &heap[largest]);
        maxHeapify(heap, size, largest);
    }
}

void buildMaxHeap(int heap[], int size) {
    for (int i = size / 2 - 1; i >= 0; i--) {
        maxHeapify(heap, size, i);
    }
}

int findKthMinimum(int arr[], int n, int k) {
    if (k <= 0 || k > n) {
        printf("Invalid K\n");
        return -1;
    }

    // Create a Max-Heap of the first K elements
    int *maxHeap = (int *)malloc(k * sizeof(int));
    for (int i = 0; i < k; i++) {
        maxHeap[i] = arr[i];
    }
    
    buildMaxHeap(maxHeap, k);

    // Process the remaining N - K elements
    for (int i = k; i < n; i++) {
        if (arr[i] < maxHeap[0]) {
            maxHeap[0] = arr[i];
            maxHeapify(maxHeap, k, 0);
        }
    }

    int kthMin = maxHeap[0];
    free(maxHeap);
    
    return kthMin;
}

int main() {
    int elements[] = {50, 10, 20, 30, 5, 90, 80, 100, 85};
    int n = sizeof(elements) / sizeof(elements[0]);

    printf("Array elements: ");
    for (int i = 0; i < n; i++) printf("%d ", elements[i]);
    printf("\n");

    int k = 4; // Using 4 as a default example
    // printf("Enter K to find the K-th minimum element: ");
    // scanf("%d", &k);
    
    printf("The %d-th minimum element is: %d\n", k, findKthMinimum(elements, n, k));

    return 0;
}
