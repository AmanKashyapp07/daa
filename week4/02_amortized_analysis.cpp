/*
 * ============================================================================
 *  AMORTIZED ANALYSIS & DYNAMIC ARRAYS
 * ============================================================================
 *  CONCEPTS:
 *  - Amortized analysis finds the average running time per operation over a 
 *    worst-case sequence of operations. 
 *  - It is NOT the same as average-case analysis (which uses probabilities). 
 *    Amortized guarantees the average performance across a sequence of operations.
 *
 *  3 METHODS OF AMORTIZED ANALYSIS:
 *  
 *  1. AGGREGATE METHOD:
 *     - Show that for a sequence of N operations, the total cost is T(N).
 *     - Amortized cost per operation = T(N) / N.
 *
 *  2. ACCOUNTING METHOD (Banker's Method):
 *     - Charge an "amortized cost" for each operation (some operations are 
 *       overcharged, some undercharged).
 *     - Store the "overcharge" as credit in the data structure.
 *     - Use the credit to pay for expensive operations later.
 *     - Rule: Total credit must never be negative.
 *
 *  3. POTENTIAL METHOD (Physicist's Method):
 *     - Define a potential function Φ(D) on the data structure D.
 *     - Amortized Cost = Actual Cost + ΔΦ (Change in potential).
 *     - Total Amortized Cost = Total Actual Cost + Φ(Dn) - Φ(D0).
 *     - Rule: Φ(Di) >= Φ(D0) for all i.
 *
 *  DYNAMIC ARRAY (std::vector):
 *  - When array is full, allocate new array of size 2 * N and copy elements.
 *  - Actual cost of append: 1 (if not full) or 1 + N (if full, copying N elements).
 *  - Amortized cost using Aggregate: Adding N elements causes array to double at 
 *    sizes 1, 2, 4, 8... The total copying cost is 1+2+4+8+...+N = 2N. Total cost 
 *    for N inserts is N (for insertion) + 2N (for copying) = 3N. 
 *    Amortized cost = 3N / N = O(1).
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
//  DYNAMIC ARRAY IMPLEMENTATION (Demonstrating Amortized Cost)
// ─────────────────────────────────────────────────────────────────────────────
class DynamicArray {
private:
    int* arr;
    int capacity;
    int size;

    // Used for analysis printing
    int total_cost; 

public:
    DynamicArray() {
        capacity = 1;
        size = 0;
        total_cost = 0;
        arr = new int[capacity];
    }

    ~DynamicArray() {
        delete[] arr;
    }

    void push_back(int value) {
        int cost_of_this_op = 0;

        // If array is full, double the capacity
        if (size == capacity) {
            capacity *= 2;
            int* new_arr = new int[capacity];
            
            // Copy existing elements (Cost = size)
            for (int i = 0; i < size; i++) {
                new_arr[i] = arr[i];
            }
            cost_of_this_op += size; // Cost of copying
            
            delete[] arr;
            arr = new_arr;
        }

        // Insert element (Cost = 1)
        arr[size++] = value;
        cost_of_this_op += 1;

        total_cost += cost_of_this_op;

        cout << "Inserted " << value << "\t| Array Size: " << size 
             << "\t| Capacity: " << capacity 
             << "\t| Actual Cost: " << cost_of_this_op 
             << "\t| Avg Amortized Cost So Far: " << (double)total_cost / size << "\n";
    }
};

// ─────────────────────────────────────────────────────────────────────────────
//  DRIVER
// ─────────────────────────────────────────────────────────────────────────────
int main() {
    cout << "=== AMORTIZED ANALYSIS: DYNAMIC ARRAY ===\n";
    DynamicArray d_arr;

    // Insert 10 elements to observe the cost spikes when doubling
    for (int i = 1; i <= 10; i++) {
        d_arr.push_back(i * 10);
    }

    cout << "\nNotice how the 'Actual Cost' spikes when Size crosses Capacity, \n";
    cout << "but the 'Avg Amortized Cost' stays bounded near 3.0 (O(1)).\n";

    return 0;
}
