#include <iostream>
#include <climits>
#include <cstring>
using namespace std;
const int MAX_N = 10; // Maximum number of cities
int finalPath[MAX_N + 1]; // Store final path
bool visited[MAX_N]; // Track visited cities
int minCost = INT_MAX; // To track the minimum cost
void tsp(int costMatrix[MAX_N][MAX_N], int currentPos, int n, int count, int cost, int path[]) {
    // Base case: If all cities have been visited
    if (count == n && costMatrix[currentPos][0]) {
        int totalCost = cost + costMatrix[currentPos][0]; // Include return cost to starting city
        if (totalCost < minCost) {
            minCost = totalCost;
            // Copy the current path to the final path
            for (int i = 0; i < n; i++)
                finalPath[i] = path[i];
            finalPath[n] = 0; // Complete the cycle
        }
        return;
    }
    // Try to go to every city
    for (int i = 0; i < n; i++) {
        if (!visited[i] && costMatrix[currentPos][i]) {
            // Mark the city as visited
            visited[i] = true;
            path[count] = i;
            // Calculate new cost with current move
            int newCost = cost + costMatrix[currentPos][i];
            // Calculate lower bound (this can be a simple heuristic, e.g., the minimum edge cost from currentPos)
            int lowerBound = newCost; // Start with the cost incurred
            for (int j = 0; j < n; j++) {
                if (!visited[j]) {
                    int minEdgeCost = INT_MAX;
                    for (int k = 0; k < n; k++) {
                        if (!visited[k] && costMatrix[j][k] < minEdgeCost) {
                            minEdgeCost = costMatrix[j][k];
                        }
                    }
                    lowerBound += minEdgeCost; // Add the minimum cost of unvisited cities
                }
            }
            // Prune branches if lower bound exceeds current minimum cost
            if (lowerBound < minCost) {
                tsp(costMatrix, i, n, count + 1, newCost, path);
            }
            // Backtrack: Unmark the city
            visited[i] = false;
        }
    }
}
int main() {
    int n;
    cout << "Enter the number of cities: ";
    cin >> n;
    if (n > MAX_N) {
        cout << "Number of cities exceeds the maximum allowed (" << MAX_N << ")." << endl;
        return 1;
    }
    int costMatrix[MAX_N][MAX_N];
    cout << "Enter the cost matrix"<< endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> costMatrix[i][j];
        }
    }
    // Initialize the visited array and path
    memset(visited, false, sizeof(visited));
    visited[0] = true; // Start from the first city
    int path[MAX_N];
    path[0] = 0; // Starting city is 0
    // Start TSP from the first city
    tsp(costMatrix, 0, n, 1, 0, path);
    cout << "Minimum cost: " << minCost << endl;
    cout << "Path: ";
    for (int i = 0; i <= n; i++)
        cout << finalPath[i] << " ";
    cout << endl;
    return 0;
}
