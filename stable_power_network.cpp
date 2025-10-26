#include <iostream>
#include <vector>
#include <tuple>
#include <queue>
#include <climits>
#include <algorithm>

typedef long long ll;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    
    int T;
    std::cin >> T;
    
    while (T--) {
        int N, M;
        std::cin >> N >> M;
        
        std::vector<std::vector<std::tuple<int, int, int>>> adj(N + 1);
        std::vector<int> risks;
        
        for (int i = 0; i < M; i++) {
            int u, v, W, R;
            std::cin >> u >> v >> W >> R;
            adj[u].push_back({v, W, R});
            adj[v].push_back({u, W, R});
            risks.push_back(R);
        }
        
        // Sort and remove duplicate risks
        std::sort(risks.begin(), risks.end());
        risks.erase(std::unique(risks.begin(), risks.end()), risks.end());
        
        int bestRisk = -1;
        ll bestTime = LLONG_MAX;
        
        // Optimized Binary Search
        int left = 0, right = risks.size() - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;
            int currentRisk = risks[mid];
            
            std::vector<ll> dist(N + 1, LLONG_MAX);
            dist[1] = 0;
            
            std::priority_queue<std::pair<ll, int>, 
                              std::vector<std::pair<ll, int>>, 
                              std::greater<std::pair<ll, int>>> pq;
            
            pq.push({0, 1});
            
            bool found = false;
            ll currentTime = LLONG_MAX;
            
            while (!pq.empty()) {
                auto [time, u] = pq.top();
                pq.pop();
                
                if (time != dist[u]) continue;
                
                if (u == N) {
                    found = true;
                    currentTime = time;
                    break;
                }
                
                for (const auto& edge : adj[u]) {
                    int v = std::get<0>(edge);
                    int W = std::get<1>(edge);
                    int R = std::get<2>(edge);
                    
                    if (R <= currentRisk && dist[v] > time + W) {
                        dist[v] = time + W;
                        pq.push({dist[v], v});
                    }
                }
            }
            
            if (found) {
                bestRisk = currentRisk;
                bestTime = currentTime;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        
        if (bestRisk == -1) { std::cout << -1 << "\n"; }
        else { std::cout << bestRisk << " " << bestTime << "\n"; }
    }
    
    return 0;
}
