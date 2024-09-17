#include <iostream>
#include <vector>

std::vector<int> longest_increasing_subseq(const std::vector<int>& seq) {
    int n = seq.size();
    std::vector<int> dp(n, 1); // Создаем массив dp и заполняем его 1, потому что самая короткая подпоследовательность - это один элемент.
    std::vector<int> prev(n, -1); // Массив для хранения предыдущего элемента в наибольшей подпоследовательности

    int max_len = 1;
    int end_index = 0;

    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (seq[i] > seq[j] && dp[i] < dp[j] + 1) {
                dp[i] = dp[j] + 1;
                prev[i] = j;
            }
        }
        if (dp[i] > max_len) {
            max_len = dp[i];
            end_index = i;
        }
    }

    std::vector<int> longest_seq;
    while (end_index != -1) {
        longest_seq.insert(longest_seq.begin(), seq[end_index]);
        end_index = prev[end_index];
    }

    return longest_seq;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::size_t n;
    std::cin >> n;
    std::vector<int> seq(n);

    for (auto& el : seq) {
        std::cin >> el;
    }

    auto longest_seq = longest_increasing_subseq(seq);

    std::cout << longest_seq.size() << "\n";
    for (auto el : longest_seq) {
        std::cout << el << " ";
    }

    return 0;
}
