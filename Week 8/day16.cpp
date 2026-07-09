// Number of Islands

#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

class Solution {
public:
    void dfs(vector<vector<char>>& grid, int r, int c) {
        int m = grid.size();
        int n = grid[0].size();

        //base case - out of bounds or in water
        if ( r < 0 || r >= m || c < 0 || c >= n || grid[r][c] == '0') {
            return;
        }

        grid[r][c] = '0';

        dfs(grid, r - 1, c);
        dfs(grid, r + 1, c);
        dfs(grid, r , c - 1);
        dfs(grid, r , c + 1);
    }

    int numIslands(vector<vector<char>>& grid) {
        if (grid.empty()) return 0;
        int count = 0;

        for (int r = 0; r < grid.size(); r++) {
            for (int c = 0; c < grid[0].size(); c++) {
                if (grid[r][c] == '1') {
                    count++;
                    dfs(grid, r , c);
                }
            }

        }
        return count;
    }
};

int main() {
    Solution sol;

    // Test Case 1: Standard grid with multiple islands
    vector<vector<char>> grid1 = {
        {'1', '1', '1', '1', '0'},
        {'1', '1', '0', '1', '0'},
        {'1', '1', '0', '0', '0'},
        {'0', '0', '0', '0', '0'}
    };
    cout << "Test Case 1 (Expected 1): " << sol.numIslands(grid1) << endl;

    // Test Case 2: Grid with separated islands
    vector<vector<char>> grid2 = {
        {'1', '1', '0', '0', '0'},
        {'1', '1', '0', '0', '0'},
        {'0', '0', '1', '0', '0'},
        {'0', '0', '0', '1', '1'}
    };
    cout << "Test Case 2 (Expected 3): " << sol.numIslands(grid2) << endl;

    // Test Case 3: Empty grid
    vector<vector<char>> grid3 = {};
    cout << "Test Case 3 (Expected 0): " << (grid3.empty() ? 0 : sol.numIslands(grid3)) << endl;

    // Test Case 4: Water only
    vector<vector<char>> grid4 = {
        {'0', '0', '0'},
        {'0', '0', '0'}
    };
    cout << "Test Case 4 (Expected 0): " << sol.numIslands(grid4) << endl;

    return 0;
}