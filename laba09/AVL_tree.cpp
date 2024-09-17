#include <bits/stdc++.h>

using namespace std;

class Node {
public:
    int key;
    int height;
    Node* left;
    Node* right;

    Node(int value) : key(value), height(1), left(nullptr), right(nullptr) {
    }
};

class AVLTree {
private:
    Node* root;

    int height(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return node->height;
    }

    int balanceFactor(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return height(node->left) - height(node->right);
    }

    void updateHeight(Node* node) {//обновление высоты
        if (node != nullptr) {
            node->height = 1 + std::max(height(node->left), height(node->right));
        }
    }

    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T = x->right;

        x->right = y;
        y->left = T;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T = y->left;

        y->left = x;
        x->right = T;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    Node* insertRecursive(Node* node, int key) {
        if (node == nullptr) {
            return new Node(key);
        }

        if (key < node->key) {
            node->left = insertRecursive(node->left, key);
        }
        else if (key > node->key) {
            node->right = insertRecursive(node->right, key);
        }
        else {
            return node;
        }

        updateHeight(node);

        int balance = balanceFactor(node);

        if (balance > 1 && key < node->left->key) {
            return rotateRight(node);
        }

        if (balance < -1 && key > node->right->key) {
            return rotateLeft(node);
        }

        if (balance > 1 && key > node->left->key) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        if (balance < -1 && key < node->right->key) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    Node* findMin(Node* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    Node* deleteRecursive(Node* node, int key) {
        if (node == nullptr) {
            return node;
        }

        if (key < node->key) {
            node->left = deleteRecursive(node->left, key);
        }
        else if (key > node->key) {
            node->right = deleteRecursive(node->right, key);
        }
        else {
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            Node* temp = findMin(node->right);
            node->key = temp->key;
            node->right = deleteRecursive(node->right, temp->key);
        }

        updateHeight(node);

        int balance = balanceFactor(node);

        if (balance > 1 && balanceFactor(node->left) >= 0) {
            return rotateRight(node);
        }

        if (balance > 1 && balanceFactor(node->left) < 0) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        if (balance < -1 && balanceFactor(node->right) <= 0) {
            return rotateLeft(node);
        }

        if (balance < -1 && balanceFactor(node->right) > 0) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    bool hasRecursive(Node* node, int key) {
        if (node == nullptr) {
            return false;
        }

        if (key == node->key) {
            return true;
        }
        else if (key < node->key) {
            return hasRecursive(node->left, key);
        }
        else {
            return hasRecursive(node->right, key);
        }
    }

public:
    AVLTree() : root(nullptr) {
    }

    void insert(int key) {
        root = insertRecursive(root, key);
    }

    void remove(int key) {
        root = deleteRecursive(root, key);
    }

    bool has(int key) {
        return hasRecursive(root, key);
    }

    int next(int key) {
        Node* current = root;
        Node* successor = nullptr;

        while (current != nullptr) {
            if (current->key > key) {
                successor = current;
                current = current->left;
            }
            else {
                current = current->right;
            }
        }

        if (successor != nullptr) {
            return successor->key;
        }
        else {
            return -1;
        }
    }

    int prev(int key) {
        Node* current = root;
        Node* predecessor = nullptr;

        while (current != nullptr) {
            if (current->key < key) {
                predecessor = current;
                current = current->right;
            }
            else {
                current = current->left;
            }
        }

        if (predecessor != nullptr) {
            return predecessor->key;
        }
        else {
            return -1;
        }
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    AVLTree avl;

    while (true) {
        string command;
        cin >> command;

        if (command == "insert") {
            int x;
            cin >> x;
            avl.insert(x);
        }
        else if (command == "delete") {
            int x;
            cin >> x;
            avl.remove(x);
        }
        else if (command == "has") {
            int x;
            cin >> x;
            cout << (avl.has(x) ? "t" : "f") << endl;
        }
        else if (command == "next") {
            int x;
            std::cin >> x;
            int result = avl.next(x);
            if (result != -1) {
                cout << result << endl;
            }
            else {
                cout << "none" << endl;
            }
        }
        else if (command == "prev") {
            int x;
            cin >> x;
            int result = avl.prev(x);
            if (result != -1) {
                cout << result << endl;
            }
            else {
                cout << "none" << endl;
            }
        }
        else if (command == "-1") {
            break;
        }
        else {
            cout << "Invalid argument." << endl;
        }
    }

    return 0;
}
