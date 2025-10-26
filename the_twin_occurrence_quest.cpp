#include <iostream>
#include <vector>
#include <algorithm>

std::pair<int, int> findIndexes(const std::vector<int>& arr, int target) {
    int n = arr.size();
    
    // Binary search to find the first occurrence
    int left = 0, right = n - 1;
    int first_idx = -1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target) {
            first_idx = mid;
            right = mid - 1;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    if (first_idx == -1) {
        return {-1, -1};
    }
    
    // Binary search to find the last occurrence
    left = 0;
    right = n - 1;
    int last_idx = -1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target) {
            last_idx = mid;
            left = mid + 1;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return {first_idx + 1, last_idx + 1};
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    
    int n, q;
    std::cin >> n >> q;
    
    std::vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }
    
    for (int i = 0; i < q; i++) {
        int target;
        std::cin >> target;
        
        std::pair<int, int> result = findIndexes(arr, target);
        std::cout << result.first << " " << result.second << "\n";
    }
    
    return 0;
}
