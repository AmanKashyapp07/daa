/*
 * Dynamic Hash Table with Rehashing
 *
 * Description:
 * Implements a hash table using separate chaining that dynamically resizes
 * (rehashes) when the load factor (alpha = n/m) exceeds a certain threshold.
 * 
 * When the load factor exceeds the threshold (e.g., 0.75), the capacity of the
 * hash table is doubled, and all existing elements are re-inserted into the
 * new, larger table. This ensures operations remain O(1) on average.
 *
 * Time Complexity:
 * - Insert: O(1) on average. O(n) worst-case when rehashing occurs.
 *   (The amortized time complexity of insertion is O(1)).
 * - Search: O(1) on average.
 * - Delete: O(1) on average.
 * 
 * Space Complexity: O(n + m), where n is the number of elements and m is capacity.
 */

#include <iostream>
#include <vector>
#include <list>

using namespace std;

class DynamicHashTable {
private:
    vector<list<int>> table;
    int numElements;
    int capacity;
    const float MAX_LOAD_FACTOR = 0.75;

    int hashFunction(int key) const {
        // Simple modulo hash function.
        // Modulo arithmetic to handle potential negative keys gracefully:
        return (key % capacity + capacity) % capacity;
    }

    void rehash() {
        int oldCapacity = capacity;
        capacity *= 2; // Double the capacity
        
        cout << "\n[Rehash Triggered] Load factor exceeded " << MAX_LOAD_FACTOR 
             << ". Growing capacity from " << oldCapacity << " to " << capacity << ".\n";

        // Create a new empty table with double capacity
        vector<list<int>> oldTable = table;
        table.assign(capacity, list<int>());
        numElements = 0; // Reset elements count as we will re-insert

        // Re-insert all elements from the old table into the new table
        for (int i = 0; i < oldCapacity; i++) {
            for (int key : oldTable[i]) {
                insert(key); // This uses the new capacity for hashing
            }
        }
    }

public:
    DynamicHashTable(int initialCapacity = 7) {
        capacity = initialCapacity;
        numElements = 0;
        table.resize(capacity);
    }

    void insert(int key) {
        int index = hashFunction(key);
        
        // Prevent duplicates (assuming a set-like behavior)
        for(int k : table[index]) {
            if (k == key) {
                return; // Element already exists
            }
        }

        table[index].push_back(key);
        numElements++;

        // Check if load factor alpha exceeds the maximum allowed load factor
        float currentLoadFactor = (float)numElements / capacity;
        if (currentLoadFactor > MAX_LOAD_FACTOR) {
            rehash();
        }
    }

    bool search(int key) const {
        int index = hashFunction(key);
        for (int k : table[index]) {
            if (k == key) {
                return true;
            }
        }
        return false;
    }

    void remove(int key) {
        int index = hashFunction(key);
        for (auto it = table[index].begin(); it != table[index].end(); ++it) {
            if (*it == key) {
                table[index].erase(it);
                numElements--;
                return;
            }
        }
    }
    
    void display() const {
        cout << "Hash Table (Capacity = " << capacity << ", Elements = " << numElements 
             << ", Load Factor = " << (float)numElements / capacity << "):\n";
        for (int i = 0; i < capacity; i++) {
            cout << "[" << i << "] -> ";
            for (int key : table[i]) {
                cout << key << " -> ";
            }
            cout << "NULL\n";
        }
        cout << "------------------------------------------\n";
    }
};

int main() {
    cout << "=== Dynamic Hash Table with Rehashing Demonstration ===\n\n";
    
    // Initialize with a small capacity to demonstrate rehashing quickly
    DynamicHashTable ht(5);
    
    cout << "Inserting elements to trigger rehashing...\n";
    
    int elements[] = {10, 22, 31, 4, 15, 28, 17, 88, 59};
    
    for (int e : elements) {
        cout << "Inserting " << e << "...\n";
        ht.insert(e);
    }
    
    cout << "\nFinal state after all insertions:\n";
    ht.display();

    cout << "\nSearching for 28: " << (ht.search(28) ? "Found" : "Not Found") << "\n";
    cout << "Searching for 100: " << (ht.search(100) ? "Found" : "Not Found") << "\n";

    return 0;
}
