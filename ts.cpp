//Write a program to solve the travelling salesman problem and to print 
//the path and the cost using LC Branch and Bound.
//Name:Abhiram Yagnamurthy
//Roll no:TIA01
#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 10;  // Maximum number of cities
int N;  // Actual number of cities

int final_path[MAX_N + 1];
bool visited[MAX_N];
int final_res = INT_MAX;

void copyToFinal(int curr_path[]) {
    for (int i = 0; i < N; i++)
        final_path[i] = curr_path[i];
    final_path[N] = curr_path[0];
}

int firstMin(vector<vector<int>>& adj, int i) {
    int min = INT_MAX;
    for (int k = 0; k < N; k++)
        if (adj[i][k] < min && i != k)
            min = adj[i][k];
    return min;
}

int secondMin(vector<vector<int>>& adj, int i) {
    int first = INT_MAX, second = INT_MAX;
    for (int j = 0; j < N; j++) {
        if (i == j)
            continue;
        if (adj[i][j] <= first) {
            second = first;
            first = adj[i][j];
        } else if (adj[i][j] <= second && adj[i][j] != first)
            second = adj[i][j];
    }
    return second;
}

void TSPRec(vector<vector<int>>& adj, int curr_bound, int curr_weight, int level, int curr_path[]) {
    if (level == N) {
        if (adj[curr_path[level - 1]][curr_path[0]] != 0) {
            int curr_res = curr_weight + adj[curr_path[level - 1]][curr_path[0]];
            if (curr_res < final_res) {
                copyToFinal(curr_path);
                final_res = curr_res;
            }
        }
        return;
    }
    for (int i = 0; i < N; i++) {
        if (adj[curr_path[level - 1]][i] != 0 && visited[i] == false) {
            int temp = curr_bound;
            curr_weight += adj[curr_path[level - 1]][i];
            if (level == 1)
                curr_bound -= ((firstMin(adj, curr_path[level - 1]) + firstMin(adj, i)) / 2);
            else
                curr_bound -= ((secondMin(adj, curr_path[level - 1]) + firstMin(adj, i)) / 2);
            if (curr_bound + curr_weight < final_res) {
                curr_path[level] = i;
                visited[i] = true;
                TSPRec(adj, curr_bound, curr_weight, level + 1, curr_path);
            }
            curr_weight -= adj[curr_path[level - 1]][i];
            curr_bound = temp;
            fill(visited, visited + N, false);
            for (int j = 0; j <= level - 1; j++)
                visited[curr_path[j]] = true;
        }
    }
}

void TSP(vector<vector<int>>& adj) {
    int curr_path[MAX_N + 1];
    int curr_bound = 0;
    fill(curr_path, curr_path + MAX_N + 1, -1);
    fill(visited, visited + MAX_N, false);

    // Compute initial bound
    for (int i = 0; i < N; i++)
        curr_bound += (firstMin(adj, i) + secondMin(adj, i));
    curr_bound = (curr_bound & 1) ? curr_bound / 2 + 1 : curr_bound / 2;

    visited[0] = true;
    curr_path[0] = 0;
    TSPRec(adj, curr_bound, 0, 1, curr_path);
}

int main() {
    int choice;

    do {
        cout << "\n----- Traveling Salesman Problem (TSP) -----\n";
        cout << "1. Enter the number of cities and the distance matrix\n";
        cout << "2. Solve TSP using LC Branch and Bound\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            cout << "\nEnter the number of cities (max " << MAX_N << "): ";
            cin >> N;
            if (N > MAX_N) {
                cout << "Error: Maximum number of cities is " << MAX_N << ".\n";
                continue;
            }

            vector<vector<int>> adj(N, vector<int>(N));
            cout << "Enter the distance matrix (enter 0 for diagonal elements):\n";
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    cin >> adj[i][j];
                }
            }

            cout << "\nDistance matrix entered successfully.\n";

            // Save the adjacency matrix for TSP solving
            while (true) {
                cout << "Press 2 to solve TSP or 3 to exit.\n";
                cin >> choice;
                if (choice == 2) {
                    TSP(adj);
                    cout << "Minimum cost: " << final_res << endl;
                    cout << "Path Taken: ";
                    for (int i = 0; i <= N; i++)
                        cout << final_path[i] << " ";
                    cout << endl;
                    break;
                } else if (choice == 3) {
                    exit(0);
                } else {
                    cout << "Invalid input! Try again.\n";
                }
            }

        } else if (choice == 3) {
            cout << "Exiting program.\n";
            break;
        } else {
            cout << "Invalid choice. Please select a valid option.\n";
        }

    } while (choice != 3);
    return 0;
}
/*---- Traveling Salesman Problem (TSP) -----
1. Enter the number of cities and the distance matrix
2. Solve TSP using LC Branch and Bound
3. Exit
Enter your choice: 1

Enter the number of cities (max 10): 4
Enter the distance matrix (enter 0 for diagonal elements):
0    
20
30
10
15 
0
16
4
3
5
0
2
19
6
18
0

Distance matrix entered successfully.
Press 2 to solve TSP or 3 to exit.
2
Minimum cost: 35
Path Taken: 0 3 1 2 0

----- Traveling Salesman Problem (TSP) -----
1. Enter the number of cities and the distance matrix
2. Solve TSP using LC Branch and Bound
3. Exit
Enter your choice: 3
Exiting program.*/