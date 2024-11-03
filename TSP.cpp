#include <iostream>
#include <climits>
using namespace std;
const int MAX_N = 10;
int N, adj[MAX_N][MAX_N];             // Distance matrix
int final_path[MAX_N + 1];             // Stores the final path
bool visited[MAX_N];                   // Tracks visited cities
int final_res = INT_MAX;               // Stores minimum cost
// Copies the current path to the final path
void copyToFinal(int path[]) {
    for (int i = 0; i < N; i++) 
        final_path[i] = path[i];
    final_path[N] = path[0];
}
// Finds the minimum or second minimum edge weight for a given city
int findMin(int i, bool excludeMin = false) {
    int first = INT_MAX, second = INT_MAX;
    for (int j = 0; j < N; j++) {
        if (i == j) continue;
        if (adj[i][j] <= first) { 
            second = first; 
            first = adj[i][j]; 
        } else if (adj[i][j] < second) 
            second = adj[i][j];
    }
    return excludeMin ? second : first;
}
// Recursive function to solve the TSP using branch and bound
void TSPRec(int bound, int weight, int level, int path[]) {
    if (level == N) { // All cities visited, complete cycle
        if (adj[path[level - 1]][path[0]]) { // If there's an edge back to the start
            int curr_res = weight + adj[path[level - 1]][path[0]];
            if (curr_res < final_res) { // Update minimum result if better
                copyToFinal(path);
                final_res = curr_res;
            }
        }
        return;
    }
    // Try visiting the next city
    for (int i = 0; i < N; i++) {
        if (!visited[i] && adj[path[level - 1]][i]) { // If city `i` is unvisited and reachable
            int temp = bound;
            int new_weight = weight + adj[path[level - 1]][i];
            // Calculate the updated bound
            bound -= ((level == 1 ? findMin(path[level - 1]) : findMin(path[level - 1], true)) + findMin(i)) / 2;
            if (bound + new_weight < final_res) { // Proceed if promising
                path[level] = i;
                visited[i] = true;
                TSPRec(bound, new_weight, level + 1, path);
            }
            // Reset bound and mark city `i` as unvisited for the next iteration
            bound = temp;
            visited[i] = false;
        }
    }
}
// Sets up and initiates the TSP recursive function
void TSP() {
    int path[MAX_N + 1] = {0}; // Starting path
    int bound = 0;
    // Initialize visited cities and calculate initial lower bound
    fill(visited, visited + N, false);
    for (int i = 0; i < N; i++) 
        bound += (findMin(i) + findMin(i, true));
    bound = (bound + 1) / 2;
    visited[0] = true; // Start from the first city
    TSPRec(bound, 0, 1, path);
}
int main() {
    cout << "Enter number of cities (max " << MAX_N << "): ";
    cin >> N;
    if (N > MAX_N) {
        cout << "Error: Maximum cities is " << MAX_N << ".\n";
        return 1;
    }
    cout << "Enter the distance matrix (0 for diagonal elements):\n";
    for (int i = 0; i < N; i++) 
        for (int j = 0; j < N; j++) 
            cin >> adj[i][j];
    TSP();
    // Output the result
    cout << "Minimum cost: " << final_res << "\nPath Taken: ";
    for (int i = 0; i <= N; i++) 
        cout << final_path[i] << " ";
    cout << endl;
    return 0;
}