/*
 * Sudoku Solver
 *
 * Description:
 * Given a partially filled 9x9 2D array grid[9][9], the goal is to assign digits (from 1 to 9) to the
 * empty cells so that every row, column, and subgrid of size 3x3 contains exactly one instance
 * of the digits from 1 to 9.
 *
 * Logic (Recursion + Backtracking):
 * 1. Find the first empty cell in the grid (denoted by 0).
 * 2. If no empty cell is found, the Sudoku is implicitly solved!
 * 3. For the found empty cell, try placing all digits from 1 to 9 sequentially.
 * 4. For each digit, check if it's "safe" to place:
 *    - It shouldn't exist anywhere in the same row.
 *    - It shouldn't exist anywhere in the same column.
 *    - It shouldn't exist anywhere in the local 3x3 subgrid.
 * 5. If safe, assign the digit and recursively try to solve the rest of the board.
 * 6. If the recursive call returns true, we are done.
 * 7. If false, BACKTRACK by resetting the cell to 0 and trying the next available digit.
 *
 * Time Complexity: O(9^(N*N)) where N = 9. Upper bound as we explore 9 options per empty cell.
 * Space Complexity: O(N*N) - Bounded strictly by the recursion call stack depth.
 */

#include <iostream>
#include <vector>

using namespace std;

#define N 9

class SudokuSolver {
private:
    // Checks if the digit exists in the specified row
    bool usedInRow(const vector<vector<int>>& grid, int row, int num) {
        for (int col = 0; col < N; col++) {
            if (grid[row][col] == num) {
                return true;
            }
        }
        return false;
    }

    // Checks if the digit exists in the specified column
    bool usedInCol(const vector<vector<int>>& grid, int col, int num) {
        for (int row = 0; row < N; row++) {
            if (grid[row][col] == num) {
                return true;
            }
        }
        return false;
    }

    // Checks if the digit exists within the specific 3x3 subgrid
    bool usedInBox(const vector<vector<int>>& grid, int boxStartRow, int boxStartCol, int num) {
        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 3; col++) {
                if (grid[row + boxStartRow][col + boxStartCol] == num) {
                    return true;
                }
            }
        }
        return false;
    }

    // Comprehensive check to see if the digit is completely safe to place
    bool isSafe(const vector<vector<int>>& grid, int row, int col, int num) {
        return !usedInRow(grid, row, num) &&
               !usedInCol(grid, col, num) &&
               !usedInBox(grid, row - row % 3, col - col % 3, num) &&
               grid[row][col] == 0;
    }

    // Scans sequentially and finds the next unassigned (empty) cell
    bool findUnassignedLocation(const vector<vector<int>>& grid, int& row, int& col) {
        for (row = 0; row < N; row++) {
            for (col = 0; col < N; col++) {
                if (grid[row][col] == 0) {
                    return true;
                }
            }
        }
        return false;
    }

    bool solveSudokuUtil(vector<vector<int>>& grid) {
        int row, col;

        // Base Case: If there is no unassigned location, we are fully done!
        if (!findUnassignedLocation(grid, row, col)) {
            return true;
        }

        // Try placing digits 1 to 9
        for (int num = 1; num <= 9; num++) {
            if (isSafe(grid, row, col, num)) {
                
                // MAKE TENTATIVE ASSIGNMENT
                grid[row][col] = num;

                // RECURSE
                if (solveSudokuUtil(grid)) {
                    return true;
                }

                // BACKTRACK
                grid[row][col] = 0;
            }
        }

        // Trigger backtracking up the stack if no valid digit 1-9 could be placed
        return false; 
    }

public:
    void solveSudoku(vector<vector<int>>& grid) {
        if (solveSudokuUtil(grid)) {
            cout << "Sudoku solved successfully:\n\n";
            printGrid(grid);
        } else {
            cout << "No solution exists for the provided Sudoku.\n";
        }
    }

    void printGrid(const vector<vector<int>>& grid) {
        for (int row = 0; row < N; row++) {
            for (int col = 0; col < N; col++) {
                if (grid[row][col] == 0) cout << ". ";
                else cout << grid[row][col] << " ";
                
                if ((col + 1) % 3 == 0 && col < 8) cout << "| ";
            }
            cout << "\n";
            if ((row + 1) % 3 == 0 && row < 8) {
                cout << "---------------------\n";
            }
        }
        cout << "\n";
    }
};

int main() {
    cout << "--- Sudoku Solver (Recursion + Backtracking) ---\n\n";

    // Standard hard Sudoku puzzle. 0 represents empty cells.
    vector<vector<int>> grid = {
        {3, 0, 6, 5, 0, 8, 4, 0, 0},
        {5, 2, 0, 0, 0, 0, 0, 0, 0},
        {0, 8, 7, 0, 0, 0, 0, 3, 1},
        {0, 0, 3, 0, 1, 0, 0, 8, 0},
        {9, 0, 0, 8, 6, 3, 0, 0, 5},
        {0, 5, 0, 0, 9, 0, 6, 0, 0},
        {1, 3, 0, 0, 0, 0, 2, 5, 0},
        {0, 0, 0, 0, 0, 0, 0, 7, 4},
        {0, 0, 5, 2, 0, 6, 3, 0, 0}
    };

    SudokuSolver solver;
    cout << "Original Unsolved Grid:\n";
    solver.printGrid(grid);
    
    solver.solveSudoku(grid);

    return 0;
}
