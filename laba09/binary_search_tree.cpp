#include <bits/stdc++.h>

using namespace std;

class Node {
public:
    int key;
    Node* left;
    Node* right;

    Node(int value) : key(value), left(nullptr), right(nullptr) {}
};

class BinarySearchTree {
private:
    Node* root;

    Node* insertRecursive(Node* node, int key) {
        if (node == nullptr) {
            return new Node(key);
        }

        if (key < node->key) {
            node->left = insertRecursive(node->left, key);
        } else if (key > node->key) {
            node->right = insertRecursive(node->right, key);
        }

        return node;
    }

    Node* findMin(Node* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    Node* findMax(Node* node) {
        while (node->right != nullptr) {
            node = node->right;
        }
        return node;
    }

    Node* deleteRecursive(Node* node, int key) {
        if (node == nullptr) {
            return node;
        }

        if (key < node->key) {
            node->left = deleteRecursive(node->left, key);
        } else if (key > node->key) {
            node->right = deleteRecursive(node->right, key);
        } else {
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            Node* temp = findMin(node->right);

            node->key = temp->key;

            node->right = deleteRecursive(node->right, temp->key);
        }
        return node;
    }

    bool hasRecursive(Node* node, int key) {//проверка наличия дерева
        if (node == nullptr) {
            return false;
        }

        if (key == node->key) {
            return true;
        } else if (key < node->key) {
            return hasRecursive(node->left, key);
        } else {
            return hasRecursive(node->right, key);
        }
    }

public:
    BinarySearchTree() : root(nullptr) {}

    ~BinarySearchTree() {
        // TODO: удалить все дерево
    }

    void insert(int key) {
        root = insertRecursive(root, key);
    }

    void remove(int key) {
        root = deleteRecursive(root, key);
    }

    bool has(int key) { //проверка наличия
        return hasRecursive(root, key);
    }

    int next(int key) {
        Node* current = root;
        Node* successor = nullptr;

        while (current != nullptr) {
            if (current->key > key) {
                successor = current;
                current = current->left;
            } else {
                current = current->right;
            }
        }

        if (successor != nullptr) {
            return successor->key;
        } else {
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
            } else {
                current = current->left;
            }
        }

        if (predecessor != nullptr) {
            return predecessor->key;
        } else {
            return -1;
        }
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    BinarySearchTree bst;

    while (true) {
        string command;
        cin >> command;

        if (command == "insert") {
            int x;
            cin >> x;
            bst.insert(x);
        } else if (command == "delete") {
            int x;
            cin >> x;
            bst.remove(x);
        } else if (command == "has") {
            int x;
            cin >> x;
            cout << (bst.has(x) ? "t" : "f") << endl;
        } else if (command == "next") {
            int x;
            cin >> x;
            int result = bst.next(x);
            if (result != -1) {
                cout << result << endl;
            } else {
                cout << "none" << endl;
            }
        } else if (command == "prev") {
            int x;
            cin >> x;
            int result = bst.prev(x);
            if (result != -1) {
                cout << result << endl;
            } else {
                cout << "none" << endl;
            }
        } else if (command == "-1") {
            break;
        } else {
            cout << "Invalid argument." << endl;
        }
    }

    return 0;
}
