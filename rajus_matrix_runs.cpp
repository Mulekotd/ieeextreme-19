#include <iostream>
#include <vector>
#include <algorithm>

int N, M;
std::vector<std::vector<long long>> grid;
std::vector<std::vector<int>> dp; // Memoization table

// Directions: up, down, left, right
int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};

int solve(int r, int c) {
    // If this state is already computed, return the stored value
    if (dp[r][c] != 0)
        return dp[r][c];

    // Every path has at least length 1 (the cell itself)
    int max_len_from_neighbor = 0;

    // Check all 4 directions
    for (int i = 0; i < 4; ++i) {
        int nr = r + dr[i];
        int nc = c + dc[i];

        // Check if the neighbor is within the grid bounds
        if (nr >= 0 && nr < N && nc >= 0 && nc < M) {
            // Check for the strictly increasing condition
            if (grid[nr][nc] > grid[r][c])
                max_len_from_neighbor = std::max(max_len_from_neighbor, solve(nr, nc));
        }
    }

    dp[r][c] = 1 + max_len_from_neighbor;
    return dp[r][c];
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::cin >> N >> M;

    // Resize the grid and DP table
    grid.resize(N, std::vector<long long>(M));
    dp.resize(N, std::vector<int>(M, 0));

    // Read the grid values
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            std::cin >> grid[i][j];
        }
    }

    int global_max_length = 0;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            global_max_length = std::max(global_max_length, solve(i, j));
        }
    }

    std::cout << global_max_length << "\n";

    return 0;
}
