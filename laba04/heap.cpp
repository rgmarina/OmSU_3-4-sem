#include <iostream>
#include <vector>

using namespace std;

struct Element {
    int value;//значение элемента
    int operationNumber;//номер операции

    Element(int v, int opNum) : value(v), operationNumber(opNum) {}
};

class PriorityQueue {
private:
    vector<Element> elements;

    void heapifyUp(int index) {
        while (index > 0) {
            int parentIndex = (index - 1) / 2;
            if (elements[index].value > elements[parentIndex].value) {
                swap(elements[index], elements[parentIndex]);
                index = parentIndex;
            } else {
                break;
            }
        }
    }

    void heapifyDown(int index) {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        int largest = index;

        if (leftChild < elements.size() && elements[leftChild].value > elements[largest].value) {
            largest = leftChild;
        }

        if (rightChild < elements.size() && elements[rightChild].value > elements[largest].value) {
            largest = rightChild;
        }

        if (largest != index) {
            swap(elements[index], elements[largest]);
            heapifyDown(largest);
        }
    }

public:
    void push(const Element &element) {
        elements.push_back(element);
        heapifyUp(elements.size() - 1);
    }

    Element top() {
        if (!empty()) {
            return elements[0];
        }
        throw runtime_error("Queue is empty");
    }

    void pop() {
        if (!empty()) {
            elements[0] = elements.back();
            elements.pop_back();
            heapifyDown(0);
        }
    }

    bool empty() const {
        return elements.empty();
    }

    bool decrementValue(int operationNumber) {
        for (Element &element: elements) {
            if (element.operationNumber == operationNumber) {
                element.value -= 1;
                size_t index = &element - &elements[0]; // индекс элемента
                heapifyDown(index);
                return true;
            }
        }
        return false;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    PriorityQueue maxHeap;
    int operationNumber = 0;

    while (true) {
        string operation;
        cin >> operation;

        if (operation == "1") {
            int value;
            cin >> value;
            operationNumber++;
            maxHeap.push(Element(value, operationNumber));
        } else if (operation == "2") {
            if (!maxHeap.empty()) {
                Element maxElement = maxHeap.top();
                maxHeap.pop();
                cout << "Извлечен элемент " << maxElement.value << ", добавлен на операции "
                     << maxElement.operationNumber << endl;
            } else {
                cout << "Очередь пуста." << endl;
            }
        } else if (operation == "3") {
            int oldValue;
            cin >> oldValue;
            operationNumber++;

            bool isRewrite = maxHeap.decrementValue(oldValue);
            if (!isRewrite) {
                cout << "Такого элемента нет в очереди" << endl;
            }

        } else if (operation == "exit") {
            break;
        } else {
            cout << "Некорректная операция." << endl;
        }
    }

    return 0;
}
