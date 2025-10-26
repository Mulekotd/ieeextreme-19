#include <iostream>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N, k;
    std::cin >> N >> k;

    std::vector<int> C(N);
    std::vector<bool> has_loop(2001, false);

    for (int i = 1; i < N; ++i) {
        std::cin >> C[i];
        has_loop[2 * C[i]] = true; 
    }

    std::vector<bool> dp(k + 1, false);
    dp[0] = true; // Base case: 0 miles = 0 loops

    for (int L = 2; L <= 2000; ++L) {
        if (has_loop[L]) {
            // Unbounded knapsack DP
            for (int x = L; x <= k; ++x) {
                dp[x] = dp[x] || dp[x - L];
            }
        }
    }

    int Q;
    std::cin >> Q;

    for (int j = 0; j < Q; ++j) {
        int A, B;
        std::cin >> A >> B;

        int base_cost = 0;

        if (A != 0) base_cost += C[A]; // Cost to get from A to 0
        if (B != 0) base_cost += C[B]; // Cost to get from 0 to B

        int target = k - base_cost;

        if (target >= 0 && dp[target]) { std::cout << "Yes\n"; }
        else { std::cout << "No\n"; }
    }

    return 0;
}
