#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

typedef long long ll;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N, K;
    std::cin >> N >> K;

    std::vector<int> A(N + 1);
    int max_val = 0;

    for (int i = 1; i <= N; ++i) {
        std::cin >> A[i];

        if (A[i] > max_val)
            max_val = A[i];
    }

    int B_max = 0;
    if (max_val > 0)
        B_max = std::floor(log2(max_val));

    std::vector<ll> Answers(K + 1, 0);
    std::vector<int> P(N + 1); // Prefix sum array

    for (int p = 1; p <= B_max; ++p) {
        ll V = 1LL << p; // V = 2^p

        P[0] = 0;
        for (int i = 1; i <= N; ++i) {
            P[i] = P[i - 1] + (A[i] >= V ? 1 : 0);
        }

        for (int k = 1; k <= K; ++k) {
            ll T_k_V = 0; 
            int r0 = 1; 

            for (int l = 1; l <= N; ++l) {
                // Find first r >= l s.t. P[r] - P[l-1] >= k
                int target = P[l - 1] + k;

                r0 = std::max(r0, l);
                while (r0 <= N && P[r0] < target) {
                    r0++;
                }

                if (r0 > N)
                    break;

                ll num_terms = (ll)N - r0 + 1;
                ll first_len = (ll)r0 - l + 1;
                ll last_len  = (ll)N - l + 1;

                ll sum_for_l = (num_terms * (first_len + last_len)) / 2;
                
                T_k_V += sum_for_l;
            }

            Answers[k] += T_k_V;
        }
    }

    for (int k = 1; k <= K; ++k) {
        std::cout << Answers[k] << (k == K ? "" : " ");
    }

    std::cout << "\n";

    return 0;
}
