#include <iostream>
#include <algorithm>
using namespace std;

struct Item {
    int weight, profit, index;  
};

bool compare(Item a, Item b) {
    double r1 = (double)a.profit / a.weight;
    double r2 = (double)b.profit / b.weight;
    return r1 > r2;
}

double FractionalKnapsack(int W, Item arr[], int n) {
    sort(arr, arr + n, compare);
    int curWeight = 0;
    double maxProfit = 0.0;
    bool included[n] = {false};
    for (int i = 0; i < n; i++) {
        if (curWeight + arr[i].weight <= W) {
            curWeight += arr[i].weight;
            maxProfit += arr[i].profit;
            included[arr[i].index] = true;
            cout << "Item " << arr[i].index + 1 << " Ratio included: 1 (fully included)\n";
        }
        else {
            int remain = W - curWeight;
            double fraction = (double)remain / arr[i].weight;
            maxProfit += arr[i].profit * fraction;
            curWeight = W;  
            included[arr[i].index] = true;
            cout << "Item " << arr[i].index + 1 << " Ratio included: " << fraction << " (fractionally included)\n";
            break;  
        }
    }
    for (int i = 0; i < n; i++) {
        if (!included[i]) {
            cout << "Item " << i + 1 << " not included\n";
        }
    }
    return maxProfit;
}
int main() {
    int W, n;
    cout << "Enter number of items you want to include in knapsack: ";
    cin >> n;
    cout << "Enter the maximum weight that knapsack can handle: ";
    cin >> W;
    Item arr[n];
    for (int i = 0; i < n; i++) {
        arr[i].index = i;  // Track original index
        cout << "Enter the weight of Item " << i + 1 << ": ";
        cin >> arr[i].weight;
    }
    for (int i = 0; i < n; i++) {
        cout << "Enter the profit of Item " << i + 1 << ": ";
        cin >> arr[i].profit;
    }
    cout << "\nMaximum profit: " << FractionalKnapsack(W, arr, n) << endl;
    return 0;
}
