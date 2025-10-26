#include <iostream>
#include <vector>
#include <cstring>

typedef long long ll;

const ll MOD = 1e9 + 7;

ll memo[60][2][2][2][2];
ll N1, N2, N3, N4;

ll dp(int bit, bool t1, bool t2, bool t3, bool t4) {
    // Base case: We've successfully assigned all bits
    if (bit == -1) {
        return 1;
    }
    // Memoization
    if (memo[bit][t1][t2][t3][t4] != -1) {
        return memo[bit][t1][t2][t3][t4];
    }

    ll ans = 0;
    
    // Determine the upper limit for this bit (0 or 1)
    // If we are 'tight', limit is the bit from N. Otherwise, limit is 1.
    int l1 = (t1) ? (N1 >> bit) & 1 : 1;
    int l2 = (t2) ? (N2 >> bit) & 1 : 1;
    int l3 = (t3) ? (N3 >> bit) & 1 : 1;
    int l4 = (t4) ? (N4 >> bit) & 1 : 1;

    // Iterate over all valid bit choices for a, b, c
    for (int da = 0; da <= l1; da++) {
        for (int db = 0; db <= l2; db++) {
            for (int dc = 0; dc <= l3; dc++) {
                
                // Determine the required bit for d to make XOR sum 0
                int dd = (da ^ db ^ dc);

                // Check if this required bit for d is within its limit
                if (dd <= l4) {
                    // This combination (da, db, dc, dd) is valid
                    // Calculate the 'tight' status for the next recursion
                    bool nt1 = t1 && (da == l1);
                    bool nt2 = t2 && (db == l2);
                    bool nt3 = t3 && (dc == l3);
                    bool nt4 = t4 && (dd == l4);
                    
                    // Recurse
                    ans = (ans + dp(bit - 1, nt1, nt2, nt3, nt4)) % MOD;
                }
            }
        }
    }
    return memo[bit][t1][t2][t3][t4] = ans;
}

// Helper function to call the DP
// Counts losing tuples in ranges [0, n1] x [0, n2] x [0, n3] x [0, n4]
ll count_losing(ll n1, ll n2, ll n3, ll n4) {
    // If any bound is negative, no tuples are possible
    if (n1 < 0 || n2 < 0 || n3 < 0 || n4 < 0)
        return 0;

    // Set global bounds for the DP
    N1 = n1; N2 = n2; N3 = n3; N4 = n4;
    memset(memo, -1, sizeof(memo));

    return dp(59, true, true, true, true);
}

// Modulo-safe multiplication
ll mul(ll a, ll b) {
    return (a * b) % MOD;
}

// Modulo-safe subtraction
ll sub(ll a, ll b) {
    return (a - b + MOD) % MOD;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int Q;
    std::cin >> Q;

    while (Q--) {
        ll A1, B1, A2, B2, A3, B3, A4, B4;
        std::cin >> A1 >> B1 >> A2 >> B2 >> A3 >> B3 >> A4 >> B4;

        // 1. Calculate total number of tuples
        ll l1 = (B1 - A1 + 1) % MOD;
        ll l2 = (B2 - A2 + 1) % MOD;
        ll l3 = (B3 - A3 + 1) % MOD;
        ll l4 = (B4 - A4 + 1) % MOD;
        ll total = mul(mul(l1, l2), mul(l3, l4));

        // 2. Calculate losing tuples using 4D Inclusion-Exclusion
        ll losing_count = 0;

        // Iterate through all 16 combinations of {A-1, B}
        for (int i = 0; i < 16; i++) {
            ll n1 = (i & 1) ? B1 : A1 - 1;
            ll n2 = (i & 2) ? B2 : A2 - 1;
            ll n3 = (i & 4) ? B3 : A3 - 1;
            ll n4 = (i & 8) ? B4 : A4 - 1;

            ll val = count_losing(n1, n2, n3, n4);
            
            // Count number of 'A-1' terms
            int num_A_terms = 0;
            if (!(i & 1)) num_A_terms++;
            if (!(i & 2)) num_A_terms++;
            if (!(i & 4)) num_A_terms++;
            if (!(i & 8)) num_A_terms++;

            // Sign is (-1)^(number of 'A-1' terms)
            if (num_A_terms % 2 == 1) { losing_count = sub(losing_count, val); }
            else { losing_count = (losing_count + val) % MOD; }
        }

        ll winning_count = sub(total, losing_count);
        std::cout << winning_count << "\n";
    }

    return 0;
}
