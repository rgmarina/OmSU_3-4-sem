#include <iostream>
#include <vector>

void insertions_sort(std::vector<int> &arr) {
    for (int i = 1; i < arr.size(); ++i) {
        for (int j = i; j > 0 && arr[j - 1] > arr[j]; --j) {
            auto x = arr[j - 1];
            arr[j - 1] = arr[j];
            arr[j] = x;
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    size_t n;
    std::cin >> n;

    std::vector<int> arr(n);
    for (size_t i = 0; i < n; i++) {
        std::cin >> arr[i];
    }

    insertions_sort(arr);

    for (auto i: arr) {
        std::cout << i << " ";
    }
    return 0;
}
