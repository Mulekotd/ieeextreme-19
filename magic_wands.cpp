#include <iostream>
#include <vector>
#include <string>

void solve() {
    int N, K;
    std::string S;
    std::cin >> N >> K >> S;

    std::vector<int> state(N);
    for (int i = 0; i < N; ++i) {
        if (S[i] == 'S') { state[i] = 1; }
        else { state[i] = 0; }
    }

    // flip_deltas[i] = 1 if an operation stops at index i
    std::vector<int> flip_deltas(N + 1, 0); 
    
    long long total_ops = 0;
    int current_flips = 0;
    bool possible = true;

    for (int i = 0; i < N; ++i) {
        current_flips = (current_flips + flip_deltas[i]) % 2;
        int current_state = (state[i] + current_flips) % 2;
        
        if (current_state == 1) {
            // Check if the operation is valid
            if (i + K > N) {
                possible = false;
                break;
            }
            
            // Perform the operation
            total_ops++;
            
            // 1. The op starts flipping us right now
            current_flips = (current_flips + 1) % 2; 
            
            // 2. Schedule this op to stop at index i + K
            flip_deltas[i + K] = (flip_deltas[i + K] + 1) % 2;
        }
    }

    if (possible) { std::cout << total_ops << "\n"; }
    else { std::cout << -1 << "\n"; }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int T;
    std::cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}
