/*
 * ============================================================================
 *  HASHING, HASH FUNCTIONS & COLLISION ANALYSIS
 * ============================================================================
 *  CONCEPTS:
 *  - Hashing maps large amounts of data (keys) to a smaller table (hash table)
 *    using a Hash Function.
 *  - Expected Search/Insert/Delete Time: O(1)
 *  - Worst-Case Time: O(N) (if all keys hash to the same slot)
 *  - Unordered Maps in c++ use a hash table with separate chaining under the hood.
 *  - Maps use balanced BSTs (like Red-Black Trees) under the hood, which guarantees O(log N) time even in worst case, but has higher constant factors than hash tables.
 *
 *  HASH FUNCTIONS:
 *  1. Division Method: h(k) = k mod M. (M should be a prime number not too 
 *     close to a power of 2).
 *  2. Multiplication Method: h(k) = floor(M * (k * A mod 1)), where 
 *     0 < A < 1 (A is often the golden ratio).
 *
 *  COLLISION RESOLUTION:
 *  - Collision: When two keys hash to the same index (h(k1) == h(k2)).
 *  1. Separate Chaining: Each slot in the hash table contains a linked list. 
 *     Colliding elements are appended to the list.
 *     - Load Factor (alpha) = N / M. Expected list length = alpha.
 *  2. Open Addressing: All elements are stored in the hash table itself. 
 *     If a collision occurs, we probe for the next empty slot using:
 *     - Linear Probing: h(k, i) = (h'(k) + i) mod M
 *     - Quadratic Probing: h(k, i) = (h'(k) + c1*i + c2*i^2) mod M
 *     - Double Hashing: h(k, i) = (h1(k) + i * h2(k)) mod M
 *
 *  EXAM TIP:
 *  - Universal Hashing: Choosing a hash function randomly from a carefully 
 *    designed class of functions. Guarantees low collision probability even 
 *    against a malicious adversary.
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
#include <list>

using namespace std;

// ─────────────────────────────────────────────────────────────────────────────
//  HASH TABLE WITH SEPARATE CHAINING
// ─────────────────────────────────────────────────────────────────────────────
class HashTableChaining {
private:
    int M; // Number of slots
    vector<list<pair<int, string>>> table; // Array of linked lists
    int collisions; // Metric for lab analysis

    // Hash function: Division method
    int hashFunction(int key) {
        return key % M;
    }

public:
    HashTableChaining(int size) {
        M = size;
        table.resize(M);
        collisions = 0;
    }

    void insert(int key, string value) {
        int index = hashFunction(key); // Compute hash index
        
        // Check for collision (if the list at index is not empty, it's a collision)
        if (!table[index].empty()) {
            // Check if key already exists, to update instead of duplicate
            for (auto& pair : table[index]) {
                if (pair.first == key) {
                    pair.second = value;
                    return; // No new collision, just update
                }
            }
            collisions++;
        }

        // Insert at the beginning of the list
        table[index].push_front({key, value});
    }

    string search(int key) {
        int index = hashFunction(key);
        for (auto pair : table[index]) {
            if (pair.first == key) {
                return pair.second;
            }
        }
        return "NOT_FOUND";
    } 

    void printTable() {
        cout << "Hash Table Contents (Chaining):\n";
        for (int i = 0; i < M; i++) {
            cout << "Slot " << i << ": ";
            for (auto pair : table[i]) {
                cout << "[" << pair.first << ":" << pair.second << "] -> ";
            }
            cout << "NULL\n";
        }
        cout << "Total Collisions recorded during insertions: " << collisions << "\n";
    }
};

// ─────────────────────────────────────────────────────────────────────────────
//  DRIVER
// ─────────────────────────────────────────────────────────────────────────────
int main() {
    cout << "=== HASH COLLISION ANALYSIS (Chaining) ===\n";
    
    // Choose M = 7 (prime number)
    HashTableChaining ht(7);

    // Insert keys. Note that 15, 22, and 8 will all hash to slot 1 (15%7=1, 22%7=1, 8%7=1)
    ht.insert(10, "Apple");  // 10 % 7 = 3
    ht.insert(15, "Banana"); // 15 % 7 = 1
    ht.insert(20, "Cherry"); // 20 % 7 = 6
    ht.insert(22, "Date");   // 22 % 7 = 1 (COLLISION)
    ht.insert(8, "Elderberry"); // 8 % 7 = 1 (COLLISION)
    ht.insert(33, "Fig");    // 33 % 7 = 5

    ht.printTable();

    cout << "\nSearch key 22: " << ht.search(22) << "\n";
    cout << "Search key 99: " << ht.search(99) << "\n";

    return 0;
}
