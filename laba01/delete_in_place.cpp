#include <iostream>
#include <vector>

using namespace std;

int removeElementInplace(vector<int> &arr, int val) {
    int write = 0;

    for (int read = 0; read < arr.size(); ++read) {
        if (arr[read] != val) {
            arr[write] = arr[read];
            write++;
        }
    }
    return write;
}

int main() {
    vector<int> arr = {0, 2, 6, 6, 1, 0, 4, 6};
    int val = 6;
    int new_s = removeElementInplace(arr, val);
    cout << new_s << endl;
    for (int i = 0; i < new_s; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}
