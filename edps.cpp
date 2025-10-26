#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>

bool solve(int N, std::vector<int>& A, std::string& result) {
    std::vector<std::pair<int, int>> pairs;

    for (int i = 0; i < N; i++) {
        pairs.push_back({A[i], i});
    }
    
    std::sort(pairs.rbegin(), pairs.rend());
    
    std::vector<bool> used(N, false);
    std::string s(2 * N, ' ');
    
    std::function<bool(int, int, int)> build = [&](int l, int r, int idx) -> bool {
        if (l > r) return true;
        if (idx == N) return false;
        
        int d = pairs[idx].first;
        int pos = pairs[idx].second;
        
        if (used[pos])
            return build(l, r, idx + 1);
        
        if (l + d + 1 <= r && s[l] == ' ' && s[l + d + 1] == ' ') {
            s[l] = '(';
            s[l + d + 1] = ')';

            used[pos] = true;
            
            if (build(l + 1, l + d, 0) && build(l + d + 2, r, 0))
                return true;
            
            s[l] = ' ';
            s[l + d + 1] = ' ';

            used[pos] = false;
        }
        
        return build(l, r, idx + 1);
    };
    
    bool success = build(0, 2 * N - 1, 0);

    if (success) {
        // Remove spaces from the string
        result = "";
        
        for (char c : s) {
            if (c != ' ') {
                result += c;
            }
        }
    }

    return success;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N;
    std::cin >> N;

    std::vector<int> A(N);
    for (int i = 0; i < N; i++) {
        std::cin >> A[i];
    }

    std::string result;

    if (solve(N, A, result)) { std::cout << "Yes\n"; std::cout << result << "\n"; }
    else { std::cout << "No\n"; }

    return 0;
}
