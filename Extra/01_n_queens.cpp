/*
 * N-Queens Problem
 *
 * Description:
 * The N Queen is the problem of placing N chess queens on an N x N chessboard so that
 * no two queens attack each other. This means no two queens can be in the same row,
 * column, or diagonal.
 *
 * Logic (Pure Recursion + Backtracking):
 * 1. We process the chessboard column by column, starting from the leftmost column (col 0).
 * 2. For each column, we try placing a queen in every row (0 to N-1).
 * 3. Before placing a queen, we check if it's "safe" using a helper function `isSafe`.
 *    - `isSafe` loops through the left side of the current row, upper-left diagonal, 
 *      and lower-left diagonal to ensure no other queen is attacking.
 * 4. If the position is safe, we place the queen ('Q') and recurse to the next column.
 * 5. If we reach a state where a queen cannot be placed in any row of the current column,
 *    we systematically backtrack (remove the queen from the current row and try the next row).
 * 6. Once we successfully place queens in all N columns, we record the board as a valid solution.
 *
 * Time Complexity: O(N!) - Upper bound, which is still 
 * Space Complexity: O(N) - Used for the recursion call stack.
 */

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class NQueens {
private:
    vector<vector<string>> solutions;

    // Helper function to check if placing a queen at board[row][col] is safe, by checking the left side of the current row and both diagonals and return true if it's safe, otherwise false.
    bool isSafe(int row, int col, const vector<string>& board, int n) {
        // Check the same row on the left side
        for (int i = 0; i < col; i++) {
            if (board[row][i] == 'Q') {
                return false;
            }
        }

        // Check the upper diagonal on the left side
        for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
            if (board[i][j] == 'Q') {
                return false;
            }
        }

        // Check the lower diagonal on the left side
        for (int i = row, j = col; i < n && j >= 0; i++, j--) {
            if (board[i][j] == 'Q') {
                return false;
            }
        }

        return true;
    }

    void solve(int col, int n, vector<string>& board) {
        // Base case: If all columns are filled, we successfully found an arrangement
        if (col == n) {
            solutions.push_back(board);
            return;
        }

        // Try placing a queen in each row for the current column
        for (int row = 0; row < n; row++) {
            
            // Check if the current cell (row, col) is safe to place a Queen
            if (isSafe(row, col, board, n)) {
                
                // PLACE THE QUEEN
                board[row][col] = 'Q';

                // RECURSE to the next column
                solve(col + 1, n, board);

                // BACKTRACK: Remove the queen and try the next row
                board[row][col] = '.';
            }
        }
    }

public:
    vector<vector<string>> solveNQueens(int n) {
        vector<string> board(n, string(n, '.'));
        solve(0, n, board);
        return solutions;
    }
    
    void printSolutions() {
        if (solutions.empty()) {
            cout << "No solutions exist.\n";
            return;
        }
        
        cout << "Total Solutions found: " << solutions.size() << "\n\n";
        for (int i = 0; i < solutions.size(); i++) {
            cout << "Solution " << i + 1 << ":\n";
            for (const string& row : solutions[i]) {
                cout << row << "\n";
            }
            cout << "\n";
        }
    }
};

int main() {
    int N;
    cout << "--- N-Queens Problem Solver (Recursion + Backtracking) ---\n";
    cout << "Enter the value of N (e.g., 4 or 8): ";
    
    // Read user input. If it fails (e.g., run in a non-interactive environment), default to 4.
    if (!(cin >> N)) {
        N = 4;
        cout << N << " (Auto-assigned)\n";
    }

    NQueens solver;
    solver.solveNQueens(N);
    solver.printSolutions();

    return 0;
}

