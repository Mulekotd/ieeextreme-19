#include <iostream>
#include <vector>
#include <string>
#include <climits>

std::vector<int> pair;
std::vector<int> rank_map;

int find(int x) {
    if (pair[x] != x)
        pair[x] = find(pair[x]);

    return pair[x];
}

void unite(int x, int y) {
    x = find(x);
    y = find(y);

    if (x != y) {
        if (rank_map[x] < rank_map[y]) {
            pair[x] = y;
        } else if (rank_map[x] > rank_map[y]) {
            pair[y] = x;
        } else {
            pair[y] = x;
            rank_map[x]++;
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, m;
    std::cin >> n >> m;
    std::cin.ignore();
    
    std::vector<std::string> grid(n);
    for (int i = 0; i < n; i++) {
        std::getline(std::cin, grid[i]);
    }
    
    std::vector<std::string> original = grid;
    
    int total_cells = n * m;
    pair.resize(total_cells);
    rank_map.resize(total_cells, 0);
    
    for (int i = 0; i < total_cells; i++) {
        pair[i] = i;
    }
    
    // Union for lines
    for (int i = 0; i < n; i++) {
        int l = 0;

        while (l < m) {
            if (grid[i][l] == '.') {
                l++;
                continue;
            }

            int r = l;

            while (r < m && grid[i][r] != '.') r++;
            
            if (r - l >= 2) {
                int half = (r - l) / 2;

                for (int k = 0; k < half; k++) {
                    int a = i * m + l + k;
                    int b = i * m + r - 1 - k;

                    unite(a, b);
                }
            }

            l = r;
        }
    }
    
    // Union for columns
    for (int j = 0; j < m; j++) {
        int t = 0;

        while (t < n) {
            if (grid[t][j] == '.') {
                t++;
                continue;
            }

            int b = t;

            while (b < n && grid[b][j] != '.') b++;
            
            if (b - t >= 2) {
                int half = (b - t) / 2;

                for (int k = 0; k < half; k++) {
                    int a = (t + k) * m + j;
                    int c = (b - 1 - k) * m + j;

                    unite(a, c);
                }
            }

            t = b;
        }
    }
    
    // Group by root
    std::vector<std::vector<int>> groups(total_cells);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] != '.') {
                int idx = i * m + j;
                int root = find(idx);

                groups[root].push_back(idx);
            }
        }
    }
    
    // Process groups
    for (int root = 0; root < total_cells; root++) {
        if (groups[root].empty()) continue;
        
        // Collect original values
        std::vector<int> vals;
        vals.reserve(groups[root].size());

        for (int idx : groups[root]) {
            int i = idx / m;
            int j = idx % m;
            vals.push_back(original[i][j] - '0');
        }
        
        // Find best digit
        int min_cost = INT_MAX;
        int best = 0;
        
        for (int d = 0; d <= 9; d++) {
            int cost = 0;

            for (int v : vals) {
                cost += abs(v - d);
            }

            if (cost < min_cost) {
                min_cost = cost;
                best = d;
            }
        }
        
        for (int idx : groups[root]) {
            int i = idx / m;
            int j = idx % m;

            grid[i][j] = '0' + best;
        }
    }
    
    for (const std::string& row : grid) {
        std::cout << row << '\n';
    }
    
    return 0;
}
