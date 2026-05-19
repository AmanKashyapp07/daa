/*
 * Knight's Tour Problem
 *
 * Description:
 * A knight's tour is a sequence of moves of a knight on a chessboard such that the knight
 * visits every square exactly once. If the knight ends on a square that is one knight's move
 * from the beginning square, the tour is closed, otherwise it is open. This program finds an open tour.
 *
 * Logic (Recursion + Backtracking):
 * 1. Initialize an N x N chessboard with -1 (unvisited).
 * 2. Start the knight at the first block (0, 0) and mark it as visited with move number 0.
 * 3. Explore all 8 possible moves of the knight from the current position.
 * 4. For each move, check if the new position is valid (inside the board and unvisited).
 * 5. If valid, recursively attempt to complete the tour from the new position.
 * 6. If the recursion successfully fills the board (move == N*N), return true.
 * 7. If the recursion fails, BACKTRACK by unmarking the position (reset to -1) and try the next move.
 *
 * Time Complexity: O(8^(N^2)) - Worst-case loose upper bound.
 * Space Complexity: O(N^2) - For the recursion call stack and board array.
 */

#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

#define N 8

class KnightTour {
private:
    // All 8 possible relative movements for a knight
    int xMove[8] = {2, 1, -1, -2, -2, -1, 1, 2};
    int yMove[8] = {1, 2, 2, 1, -1, -2, -2, -1};

    // Helper function to check if the destination is valid
    bool isSafe(int x, int y, const vector<vector<int>>& board) {
        return (x >= 0 && x < N && y >= 0 && y < N && board[x][y] == -1);
    }

    bool solveKTUtil(int x, int y, int movei, vector<vector<int>>& board) {
        // Base case: If all squares are visited, the tour is complete
        if (movei == N * N)
            return true;

        // Try all next moves from the current coordinate x, y
        for (int k = 0; k < 8; k++) {
            int next_x = x + xMove[k];
            int next_y = y + yMove[k];

            if (isSafe(next_x, next_y, board)) {
                
                // MAKE TENTATIVE ASSIGNMENT
                board[next_x][next_y] = movei; 

                // RECURSE
                if (solveKTUtil(next_x, next_y, movei + 1, board)) { 
                    return true;
                }
                
                // BACKTRACK
                else {
                    board[next_x][next_y] = -1; 
                }
            }
        }

        return false;
    }

public:
    void solveKT() {
        vector<vector<int>> board(N, vector<int>(N, -1));

        // Start knight at the first block
        board[0][0] = 0;

        // Start exploring tours from step 1
        if (!solveKTUtil(0, 0, 1, board)) {
            cout << "Solution does not exist\n";
        } else {
            printSolution(board);
        }
    }

    void printSolution(const vector<vector<int>>& board) {
        cout << "Knight's Tour (Sequence of moves 0 to " << N*N - 1 << "):\n\n";
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cout << setw(2) << board[i][j] << " ";
            }
            cout << "\n";
        }
        cout << "\n";
    }
};

int main() {
    cout << "--- Knight's Tour Problem Solver (Recursion + Backtracking) ---\n\n";
    KnightTour kt;
    kt.solveKT();
    return 0;
}
