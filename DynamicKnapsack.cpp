#include <iostream>
#include <algorithm>
using namespace std;
struct Item {
    int profit, weight;
};
int knapSack(int W, Item items[], int n) {
    int K[n + 1][W + 1]; 
    bool included[n] = {false};
    for (int i = 0; i <= n; ++i) {
        for (int w = 0; w <= W; ++w) {
            if (i == 0 || w == 0)
                K[i][w] = 0;
            else if (items[i - 1].weight <= w)
                K[i][w] = max(items[i - 1].profit + K[i - 1][w - items[i - 1].weight], 
                              K[i - 1][w]);
            else
                K[i][w] = K[i - 1][w];
        }
    }
    cout << "\nKnapSack DP Matrix:\n";
    for (int i = 0; i <= n; ++i) {
        for (int w = 0; w <= W; ++w) {
            cout << K[i][w] << "\t";
        }
        cout << endl;
    }
    int res = K[n][W];
    cout << "\nMaximum Profit: " << res << endl;
    int w = W;
    for (int i = n; i > 0 && res > 0; --i) {
        if (res != K[i - 1][w]) {  // Item i-1 was included
            included[i - 1] = true; // Mark item as included
            res -= items[i - 1].profit;
            w -= items[i - 1].weight;
        }
    }
    cout << "Items included: ";
    for (int i = 0; i < n; ++i) {
        if (included[i]) {
            cout << i+1 << " ";
        }
    }
    cout << endl;
    cout << "Items not included : ";
    for (int i = 0; i < n; ++i) {
        if (!included[i]) {
            cout << i+1 << " ";
        }
    }
    cout << endl;
    return K[n][W];
}
int main() {
    int n, W;
    cout << "Enter the number of items: ";
    cin >> n;
    Item items[n]; 
    cout << "Enter the profits and weights of the items:\n";
    for (int i = 0; i < n; ++i) {
        cin >> items[i].profit >> items[i].weight;
    }
    cout << "Enter the maximum weight the knapsack can hold: ";
    cin >> W;
    knapSack(W, items, n);
    return 0;
}