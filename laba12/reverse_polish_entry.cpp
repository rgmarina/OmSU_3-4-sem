#include <bits/stdc++.h>

using namespace std;

bool isInteger(const string& s) {//является ли строка допустимым целым числом
    if (s.empty()) {
        return false;
    }

    size_t start = (s[0] == '-') ? 1 : 0;//если -, то 1

    if (start == 1 && s.size() == 1) {
        return false;
    }

    for (size_t i = start; i < s.size(); ++i) {//проверка символа на цифры
        if (!isdigit(s[i])) return false;
    }

    return true;
}

int calc(const string& expression) {
    stack<int> stk;//стек
    istringstream tokens(expression);//поток для разбиения на токены
    string token;

    while (tokens >> token) {
        if (token == "+" || token == "-" || token == "*" || token == "/") {
            if (stk.size() < 2) {//проверка на нужное кол-во операндов в стеке
                throw runtime_error("Invalid expression");
            }

            int b = stk.top();//извлекаем 2 вверхних значения
            stk.pop();
            int a = stk.top();
            stk.pop();

            if (token == "+") {
                stk.push(a + b);
            } else if (token == "-") {
                stk.push(a - b);
            } else if (token == "*") {
                stk.push(a * b);
            } else if (token == "/") {
                if (b == 0) {
                    throw runtime_error("Division by zero");
                }

                stk.push(a / b);//убираем результата в стек
            }
        } else if (isInteger(token)) {//проверка, что токен это либо оператор, илбо целое число
            stk.push(stoi(token));
        } else {
            throw runtime_error("Invalid token: " + token);
        }
    }

    if (stk.size() != 1) {//в стеке 1 значение
        throw runtime_error("Invalid expression");
    }

    return stk.top();//конечный результат
}

int main() {//тесты
    int res1 = calc("4 1 + 5 *");
    assert(res1 == (4 + 1) * 5);//проверка
    cout << "Result1: " << res1 << endl;

    int res2 = calc("-4 2 * 3 +");
    assert(res2 == -5);
    cout << "Result2: " << res2 << endl;

    int res3 = calc("3 -4 +");
    assert(res3 == -1);
    cout << "Result3: " << res3 << endl;

    int res4 = calc("4 -1 + 5 *");
    assert(res4 == (4 + -1) * 5);
    cout << "Result4: " << res4 << endl;

    cout << "All tests passed!" << endl;
    return 0;
}