#include <bits/stdc++.h>

using namespace std;

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, k;

    cout << "Введите число n: ";
    cin >> n;
    vector<int> A(n);

    // Заполнили массив данными
    cout << "Введите n чисел:" << endl;
    for (int i = 0; i < n; i++) {
        std::cin >> A[i];
    }

    cout << "Введите число k: ";
    cin >> k;

    // Вычисление префиксных сумм
    vector<int> prefix_sum(n);
    prefix_sum[0] = A[0];
    for (int i = 1; i < n; i++) {
        prefix_sum[i] = prefix_sum[i - 1] + A[i];
    }

    // Обработка запросов
    for (int q = 0; q < k; q++) {
        cout << "Номер запроса = " << q << ": введите пару чисел (концы отрезка): ";
        int i, j;
        cin >> i >> j;

        int result;
        if (i == 0) {
            result = prefix_sum[j];
        } else {
            result = prefix_sum[j] - prefix_sum[i - 1];
        }

        cout << result << endl;
    }

    return 0;
}
