#include <iostream>
#include <cmath>

double equation(double x, double a) {
    return x * x - x + std::sqrt(x) - a;
}

double findRoot(double a) {
    double left = 0.0;
    double right = a; // Первоначальная оценка корня
    double tolerance = 1e-6; // Точность вычислений
    while (right - left > tolerance) {
        double mid = (left + right) / 2;
        if (equation(mid, a) > 0) {
            right = mid;
        } else {
            left = mid;
        }
    }
    return (left + right) / 2;
}

int main() {
    double a;
    std::cin >> a;

    double x = findRoot(a);
    std::cout << std::fixed << x << std::endl;

    return 0;
}
