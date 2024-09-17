#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

struct Student {
    std::string name;
    int age;
};

void sort_students(std::vector<Student> &arr) {
    // Сортировка по возрасту
    std::sort(arr.begin(), arr.end(), [](const Student &a, const Student &b) {
        return a.age < b.age;
    });
    // Сортировка по именам
    std::stable_sort(arr.begin(), arr.end(), [](const Student &a, const Student &b) {
        return a.name < b.name;
    });
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    size_t n;
    std::cin >> n;

    std::vector<Student> arr(n);
    for (auto &el : arr) {
        std::cin >> el.name;
        std::cin >> el.age;
    }

    sort_students(arr);

    for (auto el : arr) {
        std::cout << el.name << " " << el.age << "\n";
    }

    return 0;
}