#include <iostream>
#include <list>
#include <string>
#include <vector>

constexpr size_t P = 300007;  // Размер таблицы. Ближайшее простое > 3*100000
constexpr size_t A = 31;      // Простое и не меньше размера алфавита

size_t hash_str(const std::string& value) {
    size_t h = 0;
    for (char ch : value) {
        h = (h * A + ch) % P;
    }
    return h;
}

class HashMap {
public:
    void put(const std::string &key, const std::string &value) {
        size_t index = hash_str(key) % P;
        for (auto &pair : table[index]) {
            if (pair.first == key) {
                pair.second = value;
                return;
            }
        }
        table[index].push_back(std::make_pair(key, value));
    }

    std::string get(const std::string &key) {
        size_t index = hash_str(key) % P;
        for (const auto &pair : table[index]) {
            if (pair.first == key) {
                return pair.second;
            }
        }
        return "null";
    }

    void erase(const std::string &key) {
        size_t index = hash_str(key) % P;
        for (auto it = table[index].begin(); it != table[index].end(); ++it) {
            if (it->first == key) {
                table[index].erase(it);
                return;
            }
        }
    }

private:
    std::vector<std::list<std::pair<std::string, std::string>>> table{P};
};


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    HashMap map;

    std::string cmd;
    while (std::cin >> cmd) {
        if (cmd == "put") {
            std::string x;
            std::string y;
            std::cin >> x >> y;
            map.put(x, y);
        } else if (cmd == "get") {
            std::string x;
            std::cin >> x;
            std::cout << map.get(x) << "\n";
        } else if (cmd == "delete") {
            std::string x;
            std::cin >> x;
            map.erase(x);
        } else if (cmd == "exit") {
            break;
        }
        else {
            std::cout << "Unknown command " << cmd;
            return -1;
        }
    }

    return 0;
}