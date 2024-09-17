#include <iostream>
#include <vector>
#include <string>

std::size_t longest_common_subseq(const std::string& seq1, const std::string& seq2) {
    std::size_t len1 = seq1.length();
    std::size_t len2 = seq2.length();

    // Создаем двумерный вектор для хранения результатов
    std::vector<std::vector<std::size_t>> dp(len1 + 1, std::vector<std::size_t>(len2 + 1, 0));

    // Заполняем таблицу
    for (std::size_t i = 1; i <= len1; ++i) {
        for (std::size_t j = 1; j <= len2; ++j) {
            if (seq1[i - 1] == seq2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    return dp[len1][len2];
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string seq1;
    std::string seq2;

    std::cin >> seq1;
    std::cin >> seq2;

    auto len = longest_common_subseq(seq1, seq2);

    std::cout << len;

    return 0;
}