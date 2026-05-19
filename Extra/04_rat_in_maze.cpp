/*
 * Rat in a Maze
 *
 * Description:
 * A Maze is given as an N*N binary matrix of blocks where source block is the upper left most block
 * (0, 0) and destination block is lower rightmost block (N-1, N-1). A rat starts from source and
 * has to reach the destination. The rat can move in four directions: 'U'(up), 'D'(down), 'L' (left), 'R' (right).
 * Value 0 means the cell is blocked, 1 means open.
 *
 * Time Complexity: O(4^(N^2)) - Upper bound as we explore 4 directions from each cell.
 * Space Complexity: O(N^2) - Auxiliary space for recursion depth and visited tracking.
 */
#include <iostream>
#include <vector>
#include <string>

using namespace std;

#define N 4

class RatMaze {
private:
    vector<string> allPaths;

    bool isSafe(int x, int y, const vector<vector<int>>& maze, const vector<vector<bool>>& visited) {
        return (x >= 0 && x < N && y >= 0 && y < N && maze[x][y] == 1 && !visited[x][y]);
    }

    void solve(int x, int y, vector<vector<int>>& maze, vector<vector<bool>>& visited, string path) {
        // Base case: Reached destination
        if (x == N - 1 && y == N - 1) {
            allPaths.push_back(path);
            return;
        }

        // TENTATIVE ASSIGNMENT
        visited[x][y] = true;

        // Try Down
        if (isSafe(x + 1, y, maze, visited)) solve(x + 1, y, maze, visited, path + "D");
        // Try Left
        if (isSafe(x, y - 1, maze, visited)) solve(x, y - 1, maze, visited, path + "L");
        // Try Right
        if (isSafe(x, y + 1, maze, visited)) solve(x, y + 1, maze, visited, path + "R");
        // Try Up
        if (isSafe(x - 1, y, maze, visited)) solve(x - 1, y, maze, visited, path + "U");

        // BACKTRACK
        visited[x][y] = false;
    }

public:
    void solveMaze(vector<vector<int>>& maze) {
        // Start from (0,0) check
        if (maze[0][0] == 0 || maze[N - 1][N - 1] == 0) {
            cout << "No path possible (source/dest is blocked).\n";
            return;
        }

        vector<vector<bool>> visited(N, vector<bool>(N, false));
        solve(0, 0, maze, visited, "");

        if (allPaths.empty()) {
            cout << "No paths found.\n";
        } else {
            cout << "Total Paths: " << allPaths.size() << "\n";
            for (const string& p : allPaths) {
                cout << p << "\n";
            }
        }
    }
};

int main() {
    cout << "--- Rat in a Maze (Backtracking) ---\n";
    vector<vector<int>> maze = {
        {1, 0, 0, 0},
        {1, 1, 0, 1},
        {1, 1, 0, 0},
        {0, 1, 1, 1}
    };
    RatMaze solver;
    solver.solveMaze(maze);
    return 0;
}
