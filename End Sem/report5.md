# Heap Sort & Heap Operations: Exam Cheat Sheet

A **Heap** is a nearly complete binary tree stored as an array. There are two types:
- **Max-Heap:** Every parent node is $\ge$ its children. The largest element is at the root.
- **Min-Heap:** Every parent node is $\le$ its children. The smallest element is at the root.

### Array Representation (1-indexed)
For any node at index $i$:
- `Parent(i)` returns $\lfloor i / 2 \rfloor$
- `Left(i)` returns $2i$
- `Right(i)` returns $2i + 1$

---

## 1. Core Heap Operations

### A. Max-Heapify
**Purpose:** Maintains the Max-Heap property. If a node $i$ is smaller than its children, it "floats down" the tree until the property is restored. Assumes the left and right subtrees are already valid Max-Heaps.
**Time Complexity:** $O(\log n)$ (Height of the tree)

```text
function Max-Heapify(A, i):
    l = Left(i)
    r = Right(i)
    largest = i
    
    // Find the largest among node i, its left child, and its right child
    if l <= A.heap_size and A[l] > A[largest]:
        largest = l
    if r <= A.heap_size and A[r] > A[largest]:
        largest = r
        
    // If the parent is not the largest, swap and recursively heapify down
    if largest != i:
        Swap(A[i], A[largest])
        Max-Heapify(A, largest)
```

### B. Build-Max-Heap
**Purpose:** Converts an unordered array into a valid Max-Heap. It works bottom-up, starting from the last non-leaf node down to the root.
**Time Complexity:** $O(n)$ *(Not $O(n \log n)$! A crucial exam fact proven via mathematical summation).*

```text
function Build-Max-Heap(A):
    A.heap_size = A.length
    // The leaves start at floor(n/2) + 1. Leaves are inherently valid heaps.
    // So we iterate backwards from the last non-leaf node.
    for i from floor(A.length / 2) down to 1:
        Max-Heapify(A, i)
```

### C. Heap-Extract-Max (Priority Queue Operation)
**Purpose:** Removes and returns the maximum element (the root) from the heap, then repairs the heap.
**Time Complexity:** $O(\log n)$

```text
function Heap-Extract-Max(A):
    if A.heap_size < 1:
        error "Heap underflow"
        
    max_element = A[1]
    
    // Move the last element to the root and shrink the heap
    A[1] = A[A.heap_size]
    A.heap_size = A.heap_size - 1
    
    // Repair the heap property from the root downwards
    Max-Heapify(A, 1)
    
    return max_element
```

### D. Max-Heap-Insert (Priority Queue Operation)
**Purpose:** Inserts a new key into the heap and "floats it up" until the Max-Heap property is restored.
**Time Complexity:** $O(\log n)$

```text
function Max-Heap-Insert(A, key):
    A.heap_size = A.heap_size + 1
    i = A.heap_size
    A[i] = -infinity // Dummy value
    
    // Heap-Increase-Key Logic inline:
    // Float the node up as long as it's larger than its parent
    while i > 1 and A[Parent(i)] < key:
        A[i] = A[Parent(i)]
        i = Parent(i)
        
    A[i] = key
```

---

## 2. The Heap Sort Algorithm

**Purpose:** Sorts an array in-place in ascending order using a Max-Heap.
**Algorithm Intuition:** 
1. Build a Max-Heap so the largest element is at the root `A[1]`.
2. Swap the root with the last element in the heap.
3. Shrink the heap size by 1 (so the largest element is now locked in its final sorted position at the end of the array).
4. Run `Max-Heapify` on the new root to fix the heap.
5. Repeat until the heap size is 1.

**Time Complexity:** $O(n \log n)$ 
- `Build-Max-Heap` takes $O(n)$.
- The `for` loop runs $n-1$ times, and `Max-Heapify` takes $O(\log n)$ each time.
**Space Complexity:** $O(1)$ (In-place sort)

```text
function Heap-Sort(A):
    // Step 1: Transform array into a Max-Heap
    Build-Max-Heap(A)
    
    // Step 2: Extract maximums one by one
    for i from A.length down to 2:
        // Move current root (maximum) to the end of the array
        Swap(A[1], A[i])
        
        // Shrink the active heap boundary
        A.heap_size = A.heap_size - 1
        
        // Restore the Max-Heap property for the new root
        Max-Heapify(A, 1)
```
