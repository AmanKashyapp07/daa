/*
 * Problem B: Fractional Knapsack Problem (Greedy Algorithm)
 *
 * Logic:
 * To maximize the value, we should greedily pick items that have the highest
 * value-to-weight ratio.
 * 1. Calculate the value/weight ratio for each item.
 * 2. Sort the items in descending order of this ratio.
 * 3. Iterate through the sorted items:
 *    - If the item can completely fit in the remaining capacity, take it entirely.
 *    - If the item cannot completely fit, take the fractional part that fits and stop.
 * 
 * Time Complexity: O(N log N) for sorting the items.
 * Space Complexity: O(N) to store the items.
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to represent an Item
struct Item {
    int weight;
    int value;
    
    Item(int w, int v) : weight(w), value(v) {}
};

// Comparator function to sort items by value/weight ratio in descending order
bool compareItems(const Item& a, const Item& b) {
    double r1 = (double)a.value / a.weight;
    double r2 = (double)b.value / b.weight;
    return r1 > r2;
}

double fractionalKnapsack(int W, vector<Item>& items) {
    // Sort items by value/weight ratio
    sort(items.begin(), items.end(), compareItems);

    double total_value = 0.0;
    int current_weight = 0;

    for (const auto& item : items) {
        if (current_weight + item.weight <= W) {
            // If the item fits entirely, add its full value and weight
            current_weight += item.weight;
            total_value += item.value;
            cout << "Added full item: Weight=" << item.weight << ", Value=" << item.value << "\n";
        } else {
            // If the item doesn't fit entirely, take the fractional part that fits
            int remaining_weight = W - current_weight;
            total_value += item.value * ((double)remaining_weight / item.weight);
            cout << "Added fractional item: Took " << remaining_weight << " out of " 
                 << item.weight << " weight for a fractional value.\n";
            break; // Knapsack is full
        }
    }

    return total_value;
}

int main() {
    cout << "--- Fractional Knapsack Problem ---\n\n";
    
    // Example from the problem description
    vector<int> weights = {10, 20, 30};
    vector<int> values = {60, 100, 120};
    int W = 50;

    vector<Item> items;
    for (int i = 0; i < weights.size(); i++) {
        items.push_back(Item(weights[i], values[i]));
    }

    cout << "Weights: "; for (int w : weights) cout << w << " "; cout << "\n";
    cout << "Values:  "; for (int v : values) cout << v << " "; cout << "\n";
    cout << "Knapsack Capacity: " << W << "\n\n";

    double max_value = fractionalKnapsack(W, items);
    cout << "\nResult: Maximum value in Knapsack = " << max_value << "\n";

    return 0;
}
