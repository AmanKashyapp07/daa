/*
 * ============================================================================
 *  BINARY HEAPS & PRIORITY QUEUES
 * ============================================================================
 *  CONCEPTS:
 *  - A Binary Heap is a complete binary tree.
 *  - Max-Heap Property: Parent is greater than or equal to children.
 *  - Min-Heap Property: Parent is less than or equal to children.
 *  - Array Representation: For a node at index `i` (0-based):
 *      - Left Child = 2*i + 1
 *      - Right Child = 2*i + 2
 *      - Parent = (i - 1) / 2
 *
 *  PRIORITY QUEUE:
 *  - An Abstract Data Type (ADT) that operates similar to a queue, but each 
 *    element has a "priority". Elements with higher priority are dequeued first.
 *  - Binary Heaps are the standard data structure used to implement Priority Queues.
 *
 *  OPERATIONS:
 *  1. Insert: Add to end of array, then "Bubble Up" (or Heapify-Up). O(log N)
 *  2. Extract-Min/Max: Remove root, replace with last element, "Bubble Down" 
 *     (or Heapify-Down). O(log N)
 *  3. Peek: Return root. O(1)
 *  4. Build-Heap: Convert unsorted array to a heap. O(N).
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
//  MIN-HEAP PRIORITY QUEUE IMPLEMENTATION
// ─────────────────────────────────────────────────────────────────────────────
class MinPriorityQueue {
private:
    vector<int> heap;

    int parent(int i) { return (i - 1) / 2; }
    int left(int i) { return 2 * i + 1; }
    int right(int i) { return 2 * i + 2; }

    void heapifyDown(int i) {
        int smallest = i;
        int l = left(i);
        int r = right(i);

        if (l < heap.size() && heap[l] < heap[smallest])
            smallest = l;
        if (r < heap.size() && heap[r] < heap[smallest])
            smallest = r;

        if (smallest != i) {
            swap(heap[i], heap[smallest]);
            heapifyDown(smallest);
        }
    }

    void heapifyUp(int i) {
        while (i != 0 && heap[parent(i)] > heap[i]) {
            swap(heap[parent(i)], heap[i]);
            i = parent(i);
        }
    }

public:
    void push(int key) {
        heap.push_back(key);
        heapifyUp(heap.size() - 1);
    }

    void pop() {
        if (heap.empty()) return;
        heap[0] = heap.back();
        heap.pop_back();
        if (!heap.empty()) {
            heapifyDown(0);
        }
    }

    int top() {
        if (heap.empty()) return -1;
        return heap[0];
    }

    bool empty() {
        return heap.empty();
    }
};

// ─────────────────────────────────────────────────────────────────────────────
//  DRIVER
// ─────────────────────────────────────────────────────────────────────────────
int main() {
    cout << "=== BINARY MIN-HEAP PRIORITY QUEUE ===\n";
    MinPriorityQueue pq;

    cout << "Inserting: 10, 5, 20, 2, 8\n";
    pq.push(10);
    pq.push(5);
    pq.push(20);
    pq.push(2);
    pq.push(8);

    cout << "Extracting elements based on priority (Min first):\n";
    while (!pq.empty()) {
        cout << pq.top() << " ";
        pq.pop();
    }
    cout << "\n";

    return 0;
}
