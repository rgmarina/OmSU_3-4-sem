#include <iostream>

using namespace std;

bool canFitDiplomas(int n, int w, int h, long long side) {//кол-во, ширина, высота, длина
    return (side / w) * (side / h) >= n;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, w, h;
    cin >> n >> w >> h;

    long long left = 1;
    long long right = std::max(w, h) * n;

    while (left < right) {
        long long mid = (left + right) / 2;
        if (canFitDiplomas(n, w, h, mid)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    std::cout << left << std::endl;
    return 0;
}
