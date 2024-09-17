#include <iostream>
#include <vector>

void start(const std::vector<int>& field, std::size_t n, std::size_t m) {
    std::vector<std::vector<int>> dp(n, std::vector<int>(m, 0)); // Создаем и инициализируем массив dp нулями

    // Заполняем dp массив слева направо и сверху вниз
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            dp[i][j] = field[i * m + j]; // Монеты в текущей клетке
            if (i > 0) {
                dp[i][j] = std::max(dp[i][j], dp[i - 1][j] + field[i * m + j]);
            }
            if (j > 0) {
                dp[i][j] = std::max(dp[i][j], dp[i][j - 1] + field[i * m + j]);
            }
        }
    }

    // Максимальное количество монет, которое можно собрать, храниться в правой нижней клетке
    std::cout << dp[n - 1][m - 1] << std::endl;

    // Восстановление пути
    int i = n - 1, j = m - 1;
    std::string path;
    while (i > 0 || j > 0) {
        if (i > 0 && j > 0) {
            if (dp[i - 1][j] > dp[i][j - 1]) {
                path = 'D' + path; // Двигаемся вверх
                i--;
            } else {
                path = 'R' + path; // Двигаемся влево
                j--;
            }
        } else if (i > 0) {
            path = 'D' + path; // Двигаемся вверх
            i--;
        } else {
            path = 'R' + path; // Двигаемся влево
            j--;
        }
    }

    // Вывод пути
    std::cout << path << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::size_t n, m;
    std::cin >> n >> m;

    std::vector<int> field(n * m);
    for (std::size_t i = 0; i < n; i++) {
        for (std::size_t j = 0; j < m; j++) {
            std::cin >> field.at(i * m + j);
        }
    }

    start(field, n, m);

    return 0;
}