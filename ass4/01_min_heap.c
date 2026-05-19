/*
 * Problem A: Min-Heap Operations
 *
 * Time Complexities:
 * - Build Heap (heapify array): O(N)
 * - Add an element (insert): O(log N)
 * - Remove the minimum element (extract_min): O(log N)
 * - Find minimum element (get_min): O(1)
 * - Min-Heapify (fix a node): O(log N)
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct {
    int data[MAX_SIZE];
    int size;
} MinHeap;

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// O(log N) time
void minHeapify(MinHeap *heap, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < heap->size && heap->data[left] < heap->data[smallest])
        smallest = left;

    if (right < heap->size && heap->data[right] < heap->data[smallest])
        smallest = right;

    if (smallest != i) {
        swap(&heap->data[i], &heap->data[smallest]);
        minHeapify(heap, smallest);
    }
}

// O(N) time
void buildMinHeap(MinHeap *heap) {
    for (int i = (heap->size / 2) - 1; i >= 0; i--) {
        minHeapify(heap, i);
    }
}

// O(log N) time
void insert(MinHeap *heap, int value) {
    if (heap->size >= MAX_SIZE) {
        printf("Heap is full\n");
        return;
    }
    
    int i = heap->size++;
    heap->data[i] = value;
    
    // Fix upward
    while (i != 0 && heap->data[(i - 1) / 2] > heap->data[i]) {
        swap(&heap->data[i], &heap->data[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// O(log N) time
int extractMin(MinHeap *heap) {
    if (heap->size <= 0) return -1;
    if (heap->size == 1) {
        heap->size--;
        return heap->data[0];
    }
    
    int root = heap->data[0];
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;
    minHeapify(heap, 0);
    
    return root;
}

// O(1) time
int getMin(MinHeap *heap) {
    if (heap->size <= 0) return -1;
    return heap->data[0];
}

void printHeap(MinHeap *heap) {
    for (int i = 0; i < heap->size; i++) {
        printf("%d ", heap->data[i]);
    }
    printf("\n");
}

int main() {
    MinHeap heap;
    heap.size = 0;
    
    int elements[] = {50, 10, 20, 30, 5, 90, 80, 100, 85};
    int n = sizeof(elements) / sizeof(elements[0]);
    
    // Populate the array
    for (int i = 0; i < n; i++) {
        heap.data[i] = elements[i];
    }
    heap.size = n;
    
    printf("Initial array elements: ");
    printHeap(&heap);
    
    buildMinHeap(&heap);
    printf("After building Min-Heap (heapify): ");
    printHeap(&heap);
    
    printf("Minimum element (get_min): %d\n", getMin(&heap));
    
    printf("Adding element '2'...\n");
    insert(&heap, 2);
    printf("Heap after insertion: ");
    printHeap(&heap);
    
    printf("Removing minimum element (%d)...\n", extractMin(&heap));
    printf("Heap after extraction: ");
    printHeap(&heap);
    
    return 0;
}
