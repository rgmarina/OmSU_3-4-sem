#include <iostream>
#include <vector>

void counting_sort(std::vector<std::string> &arr, int exp) {
    const int n = arr.size();
    std::vector<std::string> output(n);
    std::vector<int> count(10, 0);

    // Подсчитываем количество элементов в каждой корзине
    for (int i = 0; i < n; i++) {
        int digit = (arr[i][exp] - '0');//берется с конца
        count[digit]++;
    }

    // Подсчитываем сумму элементов в count[i]<=
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    // Помещаем элементы в output в правильном порядке
    for (int i = n - 1; i >= 0; i--) {
        int digit = (arr[i][exp] - '0');
        output[count[digit] - 1] = arr[i];
        count[digit]--;//чтобы следующий элемент с той же цифрой был перед ним
    }

    // Копируем отсортированный массив обратно в arr
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
}

void radix_sort(std::vector<std::string> &arr) {
    const int n = arr.size();
    // Находим максимальное число для определения количества разрядов
    int max_len = arr[0].length();
    for (int i = 1; i < n; i++) {
        if (arr[i].length() > max_len) {
            max_len = arr[i].length();
        }
    }

    // Применяем сортировку подсчетом для каждого разряда начиная с самого маленького
    for (int exp = max_len - 1; exp >= 0; exp--) {
        counting_sort(arr, exp);
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    size_t n;
    std::cin >> n;

    std::vector<std::string> lines(n);
    for (auto &line : lines) {
        std::cin >> line;
    }

    radix_sort(lines);

    for (const auto &line : lines) {
        std::cout << line << "\n";
    }

    return 0;
}