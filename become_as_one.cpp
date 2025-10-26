#include <iostream>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int N, Q;
    std::cin >> N >> Q;

    // Precompute prefix sums of 2^(A[i])
    std::vector<long long> prefix_sum(N + 1, 0);
    
    for (int i = 1; i <= N; ++i) {
        int val;
        std::cin >> val;
        
        prefix_sum[i] = prefix_sum[i - 1] + (1LL << val);
    }

    // Answer Queries
    for (int q = 0; q < Q; ++q) {
        int L, R;
        std::cin >> L >> R;

        long long total = prefix_sum[R] - prefix_sum[L - 1];
        
        // Check if total is a power of two
        if (total > 0 && (total & (total - 1)) == 0) { std::cout << "Yes\n"; }
        else { std::cout << "No\n"; }
    }

    return 0;
}
