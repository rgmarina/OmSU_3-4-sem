#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int findClosestElement(const vector<int>& arr, int query) {//ближайший элемент в массиве
    if (arr.empty()) {
        cout << "Массив пуст" << endl;
        return -1;
    }

    int low = 0;
    int high = arr.size() - 1;

    while (low < high - 1) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == query) {
            return arr[mid];
        }
        if (arr[mid] < query) {
            low = mid;
        }
        if (arr[mid] > query) {
            high = mid;
        }
    }

    if (low == 0) {
        return arr[low];
    } else if (low == arr.size() - 1) {
        return arr[low];
    } else {
        int prev = arr[low];
        int next = arr[low+1];

        if (query - prev <= next - query) {
            return prev;
        } else {
            return next;
        }
    }
}

int main() {
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    int m;
    cin >> m;

    for (int i = 0; i < m; ++i) {
        int query;
        cin >> query;

        int closest = findClosestElement(arr, query);
        cout << closest << " ";
    }

    return 0;
}
