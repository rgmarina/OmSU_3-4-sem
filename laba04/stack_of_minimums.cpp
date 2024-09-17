#include <iostream>

class StackMin {
private:
    struct Node {
        int data;
        int min_value; // Минимальное значение на данном уровне стека
        Node* next;

        Node(int val, int min_val) : data(val), min_value(min_val), next(nullptr) {}
    };

    Node* top_node;

public:
    StackMin() : top_node(nullptr) {}

    void push(const int value) {
        int new_min = (top_node == nullptr) ? value : std::min(value, top_node->min_value); // Выбираем минимальный между старым минимумом и числом которое добавляем
        Node* new_node = new Node(value, new_min);
        if (top_node == nullptr) {
            top_node = new_node;
        } else {
            new_node->next = top_node;
            top_node = new_node;
        }
    }

    void pop() {
        if (top_node == nullptr) {
            std::cerr << "Stack is empty. Cannot pop.\n";
            return;
        }
        Node* tmp = top_node;
        top_node = top_node->next;
        delete tmp;
    }

    [[nodiscard]] int top() {
        if (top_node == nullptr) {
            std::cerr << "Stack is empty. Cannot get top element.\n";
            return INT_MIN; // Возврат минимального значения int, чтобы обозначить ошибку
        }
        return top_node->data;
    }

    [[nodiscard]] int min() {
        if (top_node == nullptr) {
            std::cerr << "Stack is empty. Cannot get minimum.\n";
            return INT_MIN; // Возврат минимального значения int, чтобы обозначить ошибку
        }
        return top_node->min_value;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    StackMin stack;

    std::string cmd;
    while (std::cin >> cmd) {
        if (cmd == "push") {
            int value;
            std::cin >> value;
            stack.push(value);
        } else if (cmd == "top") {
            int number = stack.top();
            if (number != INT_MIN) { // Выводим число только если не произошла ошибка
                std::cout << stack.top() << std::endl;
            }
        } else if (cmd == "min") {
            int number = stack.min();
            if(number != INT_MIN) {
                std::cout << stack.min() << std::endl; // Выводим число только если не произошла ошибка
            }
        } else if (cmd == "pop") {
            stack.pop();
        } else if (cmd == "exit") {
            break;
        } else {
            std::cout << "Unknown command " << cmd;
        }
    }

    return 0;
}
