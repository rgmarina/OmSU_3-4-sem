#include <bits/stdc++.h>

using namespace std;

// Структура данных для дерева отрезков
struct SegmentTree {
    vector<int> tree;
    int n;

    // Конструктор для построения дерева отрезков
    SegmentTree(const vector<int>& arr) {
        n = arr.size();
        int tree_size = 2 * pow(2, ceil(log2(n))) - 1;
        tree.resize(tree_size, INT_MAX);
        build(arr, 0, 0, n - 1);
    }

    // Функция для построения дерева отрезков
    void build(const vector<int>& arr, int index, int left, int right) {
        if (left == right) {
            tree[index] = arr[left];
        } else {
            int mid = (left + right) / 2;
            build(arr, 2 * index + 1, left, mid);
            build(arr, 2 * index + 2, mid + 1, right);
            tree[index] = min(tree[2 * index + 1], tree[2 * index + 2]);
        }
    }

    // Функция для поиска минимума на отрезке
    int query(int index, int left, int right, int query_left, int query_right) {
        if (query_left > right || query_right < left) {
            return INT_MAX;
        }
        if (query_left <= left && query_right >= right) {
            return tree[index];
        }
        int mid = (left + right) / 2;
        int left_min = query(2 * index + 1, left, mid, query_left, query_right);
        int right_min = query(2 * index + 2, mid + 1, right, query_left, query_right);
        return min(left_min, right_min);
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, k;

    cout << "Введите число n: ";
    cin >> n;

    vector<int> A(n);
    cout << "Введите n чисел:" << endl;
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }

    SegmentTree segment_tree(A);

    cout << "Введите число k: ";
    cin >> k;

    for (int q = 0; q < k; ++q) {
        cout << "Введите пару чисел (i, j): ";
        int i, j;
        cin >> i >> j;

        int result = segment_tree.query(0, 0, n - 1, i, j - 1);
        cout << result << endl;
    }

    return 0;
}
