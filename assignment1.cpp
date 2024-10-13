#include <iostream>
#include <algorithm>
using namespace std;

struct Item {
    int value;
    int weight;
};

// Comparator to sort items by value-to-weight ratio
bool compare(Item a, Item b) {
    return (double)a.value / a.weight > (double)b.value / b.weight;
}

// Function to calculate the maximum value for the knapsack
double fractionalKnapsack(int W, Item arr[], int n) {
    // Sort items by value-to-weight ratio
    sort(arr, arr + n, compare);

    int curWeight = 0;
    double totalValue = 0.0;

    cout << "\nIncluded items:\n";
    for (int i = 0; i < n; i++) {
        if (curWeight + arr[i].weight <= W) {
            // Fully include the item
            curWeight += arr[i].weight;
            totalValue += arr[i].value;
            cout << "Item " << i + 1 << ": Value = " << arr[i].value 
                 << ", Weight = " << arr[i].weight << "\n";
        } else {
            // Partially include the item to fill the remaining capacity
            int remaining = W - curWeight;
            totalValue += arr[i].value * ((double)remaining / arr[i].weight);
            cout << "Item " << i + 1 << ": Value = " << arr[i].value 
                 << ", Weight = " << arr[i].weight << " (partially included)\n";
            break;  // No more space left, exit loop
        }
    }

    return totalValue;
}

int main() {
    int n, W;

    // Take input from the user
    cout << "Enter the maximum weight the knapsack can hold: ";
    cin >> W;

    cout << "Enter the number of items: ";
    cin >> n;

    Item arr[n];
    cout << "Enter the value and weight of each item:\n";
    for (int i = 0; i < n; i++) {
        cout << "Item " << i + 1 << " - Value: ";
        cin >> arr[i].value;
        cout << "Item " << i + 1 << " - Weight: ";
        cin >> arr[i].weight;
    }

    double maxValue = fractionalKnapsack(W, arr, n);
    cout << "\nMaximum value we can obtain = " << maxValue << endl;

    return 0;
}