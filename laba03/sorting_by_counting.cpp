#include <iostream>
#include <vector>

using namespace std;

void count_sort(std::vector<int> &arr) {
    const int max_value = 127;
    const int min_value = 0;
    const int range = max_value - min_value + 1;

    // Создаем массив для подсчета частот элементов
    vector<int> count(range, 0); // Массив длины range заполненный 0
    // Проходимся по исходному массиву
    for (int element: arr) {
        count[element] += 1;
    }
    // Опустошили исходный массив
    arr.clear();
    for (int i = min_value; i < max_value + 1; ++i) {
        while (count[i] != 0) {
            arr.push_back(i);
            count[i] -= 1;
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    size_t n;
    cin >> n;
    vector<int> arr(n);
    for (size_t i = 0; i < n; i++) {
        cin >> arr[i];
    }

    count_sort(arr);

    for (auto i: arr) {
        cout << i << " ";
    }

    return 0;
}