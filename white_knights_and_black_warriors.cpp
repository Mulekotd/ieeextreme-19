#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

const int MAXLOG = 21; // 2^20 > 1,000,000

int N;

std::vector<std::vector<int>> adj;
std::vector<int> color;
std::vector<int> dist;
std::vector<int> depth;
std::vector<std::vector<int>> up;
std::vector<std::vector<int>> min_path;

// DFS to compute depth and 0-th ancestors (parents)
void dfs(int u, int p, int d) {
    depth[u] = d;
    up[u][0] = p;

    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u, d + 1);
        }
    }
}

// Computes the LCA of two nodes
int lca(int u, int v) {
    if (depth[u] < depth[v])
        std::swap(u, v);

    // Bring u to the same depth as v
    for (int j = MAXLOG - 1; j >= 0; j--) {
        if (depth[u] - (1 << j) >= depth[v]) {
            u = up[u][j];
        }
    }

    if (u == v)
        return u;

    // Jump u and v up together
    for (int j = MAXLOG - 1; j >= 0; j--) {
        if (up[u][j] != 0 && up[u][j] != up[v][j]) {
            u = up[u][j];
            v = up[v][j];
        }
    }

    return up[u][0];
}

// Computes the minimum dist[] on the path from u up to lca
int query_path(int u, int l) {
    int min_ans = INT_MAX;
    int diff = depth[u] - depth[l];
    
    // Jump u up to l, checking min_path values
    for (int j = MAXLOG - 1; j >= 0; j--) {
        if ((diff >> j) & 1) { // If (1 << j) is part of the difference
            min_ans = std::min(min_ans, min_path[u][j]);
            u = up[u][j];
        }
    }

    return min_ans;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int Q;
    std::cin >> N >> Q;

    adj.resize(N + 1);
    color.resize(N + 1);
    dist.resize(N + 1, INT_MAX);
    depth.resize(N + 1);
    up.resize(N + 1, std::vector<int>(MAXLOG, 0));
    min_path.resize(N + 1, std::vector<int>(MAXLOG, INT_MAX));

    std::queue<int> q;

    // 1. Read colors and init BFS
    for (int i = 1; i <= N; i++) {
        std::cin >> color[i];

        if (color[i] == 1) {
            dist[i] = 0;
            q.push(i);
        }
    }

    // 2. Read edges
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        std::cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // 3. Run Multi-Source BFS
    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : adj[u]) {
            if (dist[v] == INT_MAX) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }

    // 4. Run DFS to build parent/depth
    dfs(1, 0, 0);
    dist[0] = INT_MAX;

    for (int j = 1; j < MAXLOG; j++) {
        for (int i = 1; i <= N; i++) {
            int p = up[i][j - 1];
            up[i][j] = up[p][j - 1];
        }
    }

    for (int i = 1; i <= N; i++) {
        min_path[i][0] = std::min(dist[i], dist[up[i][0]]);
    }

    for (int j = 1; j < MAXLOG; j++) {
        for (int i = 1; i <= N; i++) {
            int p = up[i][j - 1];
            min_path[i][j] = std::min(min_path[i][j - 1], min_path[p][j - 1]);
        }
    }


    for (int k = 0; k < Q; k++) {
        int u, v;
        std::cin >> u >> v;

        int l = lca(u, v);
        
        int min_ans_u = query_path(u, l);
        int min_ans_v = query_path(v, l);
        
        std::cout << std::min({min_ans_u, min_ans_v, dist[l]}) << "\n";
    }

    return 0;
}
