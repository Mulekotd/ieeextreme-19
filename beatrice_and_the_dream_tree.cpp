#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>

std::vector<std::vector<int>> children;
std::vector<int> node_hash;
std::map<std::vector<int>, int> canonical_map;

int next_hash = 1;

int dfs_hash(int u) {
    if (children[u].empty()) {
        node_hash[u] = 0;
        return 0;
    }

    // 1. Get hashes of all children
    std::vector<int> child_hashes;
    for (int v : children[u]) {
        child_hashes.push_back(dfs_hash(v));
    }

    // 2. Sort to make canonical
    std::sort(child_hashes.begin(), child_hashes.end());

    // 3. Map this canonical signature to a new integer hash
    if (canonical_map.find(child_hashes) == canonical_map.end())
        canonical_map[child_hashes] = next_hash++;

    int my_hash = canonical_map[child_hashes];
    node_hash[u] = my_hash;

    return my_hash;
}

int total_identified = 0;

void dfs_solve(int u) {    
    // 1. Count hash frequencies of all children of 'u'
    std::map<int, int> hash_counts;
    for (int v : children[u]) {
        hash_counts[node_hash[v]]++;
    }

    // 2. Check each child
    for (int v : children[u]) {
        if (hash_counts[node_hash[v]] == 1) {
            total_identified++;
            dfs_solve(v);
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int N;
    std::cin >> N;
    std::vector<std::vector<int>> adj(N + 1);

    children.resize(N + 1);
    node_hash.resize(N + 1);

    for (int i = 0; i < N - 1; ++i) {
        int u, v;
        std::cin >> u >> v;
        
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // --- 1. Root the tree at 1 ---
    std::queue<int> q;
    q.push(1);

    std::vector<bool> visited(N + 1, false);
    visited[1] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                children[u].push_back(v);
                q.push(v);
            }
        }
    }

    // --- 2. Hash all subtrees ---
    dfs_hash(1);

    // --- 3. Count identifiable nodes ---
    total_identified = 1;
    dfs_solve(1);

    std::cout << total_identified << "\n";

    return 0;
}
