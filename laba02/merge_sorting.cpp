#include <iostream>
#include <vector>

void merge(std::vector<int> &arr, std::vector<int> &buffer, size_t begin,
           size_t middle, size_t end) {
    size_t leftIdx = begin;
    size_t rightIdx = middle + 1;
    size_t bufferIdx = begin;

    // Слияние двух подмассивов
    while (leftIdx <= middle && rightIdx <= end) {
        if (arr[leftIdx] <= arr[rightIdx]) {
            buffer[bufferIdx] = arr[leftIdx];
            leftIdx++;
        } else {
            buffer[bufferIdx] = arr[rightIdx];
            rightIdx++;
        }
        bufferIdx++;
    }

    // Копирование оставшихся элементов из левого подмассива
    while (leftIdx <= middle) {
        buffer[bufferIdx] = arr[leftIdx];
        leftIdx++;
        bufferIdx++;
    }

    // Копирование оставшихся элементов из правого подмассива
    while (rightIdx <= end) {
        buffer[bufferIdx] = arr[rightIdx];
        rightIdx++;
        bufferIdx++;
    }

    // Копирование отсортированных элементов обратно в исходный массив
    for (size_t i = begin; i <= end; i++) {
        arr[i] = buffer[i];
    }
}

void merge_sort(std::vector<int> &arr, std::vector<int> &buffer, size_t begin,
                size_t end) {
    if (begin < end) {
        size_t middle = (begin + end) / 2;
        // Рекурсивно сортируем левую и правую половины
        merge_sort(arr, buffer, begin, middle);
        merge_sort(arr, buffer, middle + 1, end);//так как индексация с 0
        // Слияние двух отсортированных половин
        merge(arr, buffer, begin, middle, end);
    }
}

void run_merge_sort(std::vector<int> &arr) {
    std::vector<int> buffer(arr.size()); // Буфер для временного хранения данных
    merge_sort(arr, buffer, 0, arr.size() - 1);//так как вызов рекурсивно, arr.size-1=последний элемент массива arr
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    size_t n;
    std::cin >> n;

    std::vector<int> arr(n);
    for (size_t i = 0; i < n; i++) {
        std::cin >> arr[i];
    }

    run_merge_sort(arr);

    for (auto i : arr) {
        std::cout << i << " ";
    }

    return 0;
}