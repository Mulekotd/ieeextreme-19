#include <iostream>

typedef long long ll;

const ll MOD = 998244353;

// Computes (base^exp) % mod
ll power(ll base, ll exp) {
    ll res = 1;
    base %= MOD;

    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp /= 2;
    }

    return res;
}

// Computes (n^-1) % mod using Fermat's Little Theorem
ll modInverse(ll n) {
    return power(n, MOD - 2);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int T;
    std::cin >> T;

    while (T--) {
        int N;
        std::cin >> N;
        
        if (N % 2 == 0) { std::cout << 0 << "\n"; }  // Case 1: N is even
        else { std::cout << modInverse(N) << "\n"; } // Case 2: N is odd
    }

    return 0;
}
