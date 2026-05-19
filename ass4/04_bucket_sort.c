/*
 * Problem D: Bucket Sort
 *
 * Performance Study:
 * - Uniform Distribution: Elements are evenly spread across the range. Each bucket
 *   gets roughly the same number of elements (O(1) per bucket). Sorting each bucket 
 *   takes O(1) time. Total Time Complexity: O(N) average.
 * - Clustered Distribution: Elements are bunched together, causing some buckets to 
 *   have many elements while others are empty. Sorting a dense bucket with Insertion Sort 
 *   takes O(B^2) where B is the number of elements in the bucket.
 *   Total Time Complexity degrades to O(N^2) worst case.
 * 
 * Space Complexity: O(N) for the buckets and nodes.
 */

#include <stdio.h>
#include <stdlib.h>

// Node for linked list in each bucket
struct Node {
    float data;
    struct Node* next;
};

// Insert into a sorted linked list (Insertion Sort logic within the bucket)
void insertSorted(struct Node** head, float val) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = val;
    newNode->next = NULL;

    if (*head == NULL || (*head)->data >= val) {
        newNode->next = *head;
        *head = newNode;
        return;
    }

    struct Node* current = *head;
    while (current->next != NULL && current->next->data < val) {
        current = current->next;
    }
    
    newNode->next = current->next;
    current->next = newNode;
}

void bucketSort(float arr[], int n) {
    // Array of pointers to the buckets (Linked Lists)
    struct Node** buckets = (struct Node**)calloc(n, sizeof(struct Node*));

    // Scatter elements into different buckets based on their range
    for (int i = 0; i < n; i++) {
        int bucketIndex = n * arr[i]; // Works for numbers strictly [0.0, 1.0)
        if (bucketIndex >= n) bucketIndex = n - 1; // Edge case safeguard
        
        insertSorted(&buckets[bucketIndex], arr[i]);
    }

    // Gather and concatenate all buckets back into arr[]
    int index = 0;
    for (int i = 0; i < n; i++) {
        struct Node* current = buckets[i];
        while (current != NULL) {
            arr[index++] = current->data;
            struct Node* temp = current;
            current = current->next;
            free(temp); // clean up memory as we go
        }
    }
    free(buckets);
}

void printArray(float arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%0.4f ", arr[i]);
    printf("\n");
}

int main() {
    float uniform_arr[] = {0.897, 0.565, 0.656, 0.1234, 0.665, 0.3434};
    int n1 = sizeof(uniform_arr) / sizeof(uniform_arr[0]);

    printf("--- Uniformly Distributed Data ---\n");
    printf("Original array: \n");
    printArray(uniform_arr, n1);
    bucketSort(uniform_arr, n1);
    printf("Sorted array: \n");
    printArray(uniform_arr, n1);

    // Highly clustered array mapping roughly to just 2 index buckets
    float clustered_arr[] = {0.112, 0.119, 0.115, 0.881, 0.885, 0.889};
    int n2 = sizeof(clustered_arr) / sizeof(clustered_arr[0]);

    printf("\n--- Clustered Distributed Data ---\n");
    printf("Original array: \n");
    printArray(clustered_arr, n2);
    bucketSort(clustered_arr, n2);
    printf("Sorted array: \n");
    printArray(clustered_arr, n2);

    return 0;
}
