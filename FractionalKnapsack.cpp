#include <iostream>
#include <algorithm>
using namespace std;
struct Item {
    int weight, profit;
};
bool compare(Item a, Item b) {
    double r1 = (double)a.profit / a.weight;
    double r2 = (double)b.profit / b.weight;
    return r1 > r2;
}
double FractionalKnapsack(int W, Item arr[], int n) {
    sort(arr, arr + n, compare);
    int curWeight = 0;
    double FinalValue = 0.0;

    for (int i = 0; i < n; i++) {
        if (curWeight + arr[i].weight <= W) {
            curWeight += arr[i].weight;
            FinalValue += arr[i].profit;
            cout << "Item " << i + 1;
            cout << " Ratio included: 1 (fully included)\n";
        } else {
            int remain = W - curWeight;
            if (remain > 0) {
                curWeight += remain;
                double fraction = (double)remain / arr[i].weight;
                FinalValue += (double)arr[i].profit * fraction;
                cout << "Item " << i + 1;
                cout << " Ratio included: " << fraction << " \n";
            } else {
                cout << "Item " << i + 1 << " excluded (not enough space)\n";
            }
        }
    }
    return FinalValue;
}
int main() {
    int W, n;
    cout << "Enter number of items you want to include in knapsack: ";
    cin >> n;
    cout << "Enter the maximum weight that knapsack can handle: ";
    cin >> W;
    Item arr[n];
    for (int i = 0; i < n; i++) {
        cout << "Enter the weight of Item " << i + 1 << ": ";
        cin >> arr[i].weight;
    }
    for (int i = 0; i < n; i++) {
        cout << "Enter the profit of Item " << i + 1 << ": ";
        cin >> arr[i].profit;
    } 
    cout << "\n" << FractionalKnapsack(W, arr, n) << " is maximum profit\n";
    return 0;
}