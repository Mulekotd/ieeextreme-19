#include <iostream>
#include <vector>

typedef long long ll;

ll safeMod(ll n, ll p) {
    return (n % p + p) % p;
}

ll power(ll base, ll exp, ll mod) {
    ll res = 1;
    base = safeMod(base, mod);

    while (exp > 0) {
        if (exp % 2 == 1) 
            res = (res * base) % mod;

        exp = exp >> 1;
        base = (base * base) % mod;
    }

    return res;
}

ll modInverse(ll n, ll p) {
    return power(n, p - 2, p);
}

void solve() {
    ll a, b, p, x1, y1, x2, y2;
    std::cin >> a >> b >> p >> x1 >> y1 >> x2 >> y2;

    ll x3, y3, lambda;

    if (x1 == x2 && y1 == y2) {
        if (y1 == 0) {
            std::cout << "POINT_AT_INFINITY\n";
        } else {
            ll num = safeMod(3 * x1 * x1 + a, p);
            ll den = safeMod(2 * y1, p);
    
            lambda = safeMod(num * modInverse(den, p), p);

            x3 = safeMod(lambda * lambda - 2 * x1, p);
            y3 = safeMod(lambda * (x1 - x3) - y1, p);

            std::cout << x3 << " " << y3 << "\n";
        }
    } else if (x1 == x2) {
        std::cout << "POINT_AT_INFINITY\n";
    } else {
        ll num = safeMod(y2 - y1, p);
        ll den = safeMod(x2 - x1, p);

        lambda = safeMod(num * modInverse(den, p), p);

        x3 = safeMod(lambda * lambda - x1 - x2, p);
        y3 = safeMod(lambda * (x1 - x3) - y1, p);

        std::cout << x3 << " " << y3 << "\n";
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}
