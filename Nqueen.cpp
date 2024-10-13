#include <iostream>
using namespace std;
const int MAX_N = 20;
bool isSafe(int board[MAX_N][MAX_N], int row, int col, int N) {
    for (int i = 0; i < col; ++i)
        if (board[row][i] == 1)
            return false; // Check row
    for (int i = row, j = col; i >= 0 && j >= 0; --i, --j)
        if (board[i][j] == 1)
            return false; // Check upper diagonal
    for (int i = row, j = col; i < N && j >= 0; ++i, --j)
        if (board[i][j] == 1)
            return false; // Check lower diagonal
    return true; // Position is safe
}
void printBoard(int board[MAX_N][MAX_N], int N) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << (board[i][j] == 1 ? "Q " : ". "); // Print queen or empty space
        }
        cout << endl; // New line for each row
    }
    cout << endl; // Extra line between solutions
}
void solveNQueensUtil(int board[MAX_N][MAX_N], int col, int N, int& solutionCount) {
    if (col >= N) {
        solutionCount++;
        cout << "Solution " << solutionCount << ":\n";
        printBoard(board, N);
        return; // Continue searching for other solutions
    }
    for (int i = 0; i < N; ++i) {
        if (isSafe(board, i, col, N)) {
            board[i][col] = 1; // Place the queen
            solveNQueensUtil(board, col + 1, N, solutionCount); // Recur for the next column
            board[i][col] = 0; // Backtrack
        }
    }
}
int main() {
    cout << "Enter the number of queens: ";
    int N;
    cin >> N;
    if (N > MAX_N) {
        cout << "The maximum number of queens allowed is " << MAX_N << ".\n";
        return 1; 
    }
    int board[MAX_N][MAX_N] = {0}; // Initialize the board to 0
    int solutionCount = 0; // Count of solutions
    solveNQueensUtil(board, 0, N, solutionCount); // Start solving
    if (solutionCount == 0) {
        cout << "No solution exists.\n"; // If no solutions were found
    } else {
        cout << "Total solutions: " << solutionCount << endl; // Total solutions found
    }
    return 0;
}