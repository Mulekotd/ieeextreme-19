#include <iostream>
#include <vector>
#include <cmath>

typedef long long ll;

const ll MOD = 1e9 + 7;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    
    int N_INPUT_MAX = 100000;
    int V_MAX = N_INPUT_MAX * 212;

    // Denominations in units of 25 Piastras
    std::vector<int> D = {1, 2, 4, 20, 40, 80, 200, 400, 800};
    std::vector<ll> dp(V_MAX + 1, 0);

    dp[0] = 1; // Base case: 1 way to make sum 0

    // Fill the DP array
    for (int i = 1; i <= V_MAX; ++i) {
        for (int d : D) {
            if (i >= d)
                dp[i] += dp[i - d]; // dp[i] = (dp[i] + dp[i - d]) % MOD;
        }

        dp[i] %= MOD;
    }

    int T;
    std::cin >> T;

    while (T--) {
        int N;
        ll M, A;

        std::cin >> N >> M >> A;

        // The actual target in "units" is N * 212
        ll target_value = (ll)N * 212;
        ll actual_answer = dp[target_value];

        // Use ll for distances
        ll dist_M = std::abs(actual_answer - M);
        ll dist_A = std::abs(actual_answer - A);

        if (dist_M == 0 && dist_A == 0) { std::cout << "TIE\n"; }
        else if (dist_M < dist_A) { std::cout << "Mikel\n"; }
        else if (dist_A < dist_M) { std::cout << "Andrew\n"; }
        else { std::cout << "NONE\n"; } // dist_M == dist_A
    }

    return 0;
}
