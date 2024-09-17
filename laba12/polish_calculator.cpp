#include <bits/stdc++.h>

using namespace std;

// Парсер чисел с плавающей точкой
class FloatParser {
public:
    static float parse(const string& token) {
        size_t len = token.length();
        if (len == 0) {//пустая строка
            throw runtime_error("Invalid float: empty string");
        }

        // Проверка допустимых символов и позиций
        bool hasDecimalPoint = false;
        size_t start = 0;//начальная позиция
        if (token[0] == '-' || token[0] == '+') {
            start = 1;
        }

        if (start == len) {
            throw runtime_error("Invalid float: " + token);
        }

        for (size_t i = start; i < len; ++i) {
            if (token[i] == '.') {//является ли символ десятичной точкой или цифрой
                if (hasDecimalPoint) {
                    throw runtime_error("Invalid float: multiple decimal points in " + token);
                }
                hasDecimalPoint = true;
            } else if (!isdigit(token[i])) {
                throw runtime_error("Invalid float: non-digit character in " + token);
            }
        }

        // Конвертация строки в число
        float result = 0.0f;
        float sign = (token[0] == '-') ? -1.0f : 1.0f;//определение знака
        float factor = 1.0f;//дробная часть числа
        bool decimalPart = false;

        for (size_t i = (token[0] == '-' || token[0] == '+') ? 1 : 0; i < len; ++i) {//если первый сивол-знак
            if (token[i] == '.') {
                decimalPart = true;
                continue;
            }

            int digit = token[i] - '0';

            if (decimalPart) {//добавлять в дробную или целую часть числа
                factor *= 0.1f;
                result += digit * factor;
            } else {
                result = result * 10.0f + digit;
            }
        }

        return result * sign;
    }
};

// Базовый класс для всех операторов
class Operator {
public:
    virtual void apply(stack<float>& stk) const = 0;
    virtual ~Operator() = default;
};

// Класс калькулятора
class Calculator {
public:
    void registerOp(const string& symbol, shared_ptr<Operator> op) {
        operators[symbol] = op;
    }

    float eval(const vector<string>& tokens) {//возравщает результат как число с плавающей точкой
        stack<float> stk;//стек
        for (const auto& token : tokens) {
            if (isOperator(token)) {
                if (operators.count(token) == 1) {
                    auto& op = operators[token];
                    op->apply(stk);
                } else {
//                    try parse float
                    throw runtime_error("Unknown operator: " + token);
                }

//                auto it = operators.find(token);
//                if (it != operators.end()) {//ищем оператор
//                    it->second->apply(stk);
//                } else {
//                    throw runtime_error("Unknown operator: " + token);
//                }
//
            } else {
                stk.push(FloatParser::parse(token));
            }
        }

        if (stk.size() != 1) {//1 число в стеке
            throw runtime_error("Invalid expression");
        }
        return stk.top();//результат
    }

private:
    unordered_map<string, shared_ptr<Operator>> operators;//операторы калькулятора

//    bool isOperator(const string& token) const {
//        return operators.find(token) != operators.end();
//    }
};

// Оператор сложения двух чисел
class AddOp : public Operator {
public:
    void apply(stack<float>& stk) const override {
        if (stk.size() < 2) {
            throw runtime_error("Insufficient operands for +");
        }

        float b = stk.top();
        stk.pop();
        float a = stk.top();
        stk.pop();

        stk.push(a + b);
    }
};

// Оператор разности двух чисел
class SubtractOp : public Operator {
public:
    void apply(stack<float>& stk) const override {
        if (stk.size() < 2) {
            throw runtime_error("Insufficient operands for -");
        }

        float b = stk.top();
        stk.pop();
        float a = stk.top();
        stk.pop();

        stk.push(a - b);
    }
};

// Оператор умножения двух чисел
class MultiplyOp : public Operator {
public:
    void apply(stack<float>& stk) const override {
        if (stk.size() < 2) {
            throw runtime_error("Insufficient operands for *");
        }

        float b = stk.top();
        stk.pop();
        float a = stk.top();
        stk.pop();

        stk.push(a * b);
    }
};

// Оператор деления двух чисел
class DivideOp : public Operator {
public:
    void apply(stack<float>& stk) const override {
        if (stk.size() < 2) {
            throw runtime_error("Insufficient operands for /");
        }

        float b = stk.top();
        stk.pop();
        float a = stk.top();
        stk.pop();

        if (b == 0) {
            throw runtime_error("Division by zero");
        }

        stk.push(a / b);
    }
};

// Оператор остатка от деления
class ModuloOp : public Operator {
public:
    void apply(stack<float>& stk) const override {
        if (stk.size() < 2) {
            throw runtime_error("Insufficient operands for %");
        }

        float b = stk.top();
        stk.pop();
        float a = stk.top();
        stk.pop();

        stk.push(static_cast<int>(a) % static_cast<int>(b));
    }
};

// Оператор суммирования последовательности чисел
class SumOp : public Operator {
public:
    void apply(stack<float>& stk) const override {
        float sum = 0;

        while (!stk.empty()) {
            sum += stk.top();
            stk.pop();
        }

        stk.push(sum);
    }
};

// Функция разбора строки на токены
vector<string> Tokenize(const string& expression) {
    istringstream tokens(expression);
    vector<string> result;
    string token;

    while (tokens >> token) {
        result.push_back(token);
    }

    return result;//токены возвраащются в виде вектора
}

bool floatEquals(float a, float b, float epsilon = 0.0001f) {//сравнение не целых чисел
    return fabs(a - b) < epsilon;
}

int main() {
    Calculator calc;
    calc.registerOp("+", make_shared<AddOp>());
    calc.registerOp("-", make_shared<SubtractOp>());
    calc.registerOp("*", make_shared<MultiplyOp>());
    calc.registerOp("/", make_shared<DivideOp>());
    calc.registerOp("%", make_shared<ModuloOp>());
    calc.registerOp("sum", make_shared<SumOp>());

    {
        auto tokens = Tokenize("6 8 + 3 %"); // ( 6 + 8 ) % 3
        float res = calc.eval(tokens);
        assert(floatEquals(res, static_cast<int>(6 + 8) % 3));
    }

    {
        auto tokens = Tokenize("1 2 3 4 5 6 sum");
        float res = calc.eval(tokens);
        assert(floatEquals(res, 1 + 2 + 3 + 4 + 5 + 6));
    }

    {
        auto tokens = Tokenize("5 3 - 2 /");
        float res = calc.eval(tokens);
        assert(floatEquals(res, (5 - 3) / 2.0f));
    }

    {
        auto tokens = Tokenize("7 3 * 2 + 5 /");
        float res = calc.eval(tokens);
        assert(floatEquals(res, (7 * 3 + 2) / 5.0f));
    }

    {
        auto tokens = Tokenize("7.5 3.1 * 2.1 + 5.0 /");
        float res = calc.eval(tokens);
        assert(floatEquals(res, (7.5 * 3.1 + 2.1) / 5.0f));
    }

    {
        auto tokens = Tokenize("-7.5 3.1 * 2.1 + -5.0 /");
        float res = calc.eval(tokens);
        assert(floatEquals(res, (-7.5 * 3.1 + 2.1) / -5.0f));
    }

    {
        auto tokens = Tokenize("-7.531 3.199 * 2.143 + -5.0 /");
        float res = calc.eval(tokens);
        assert(floatEquals(res, (-7.531 * 3.199 + 2.143) / -5.0f));
    }

    {
        auto tokens = Tokenize("8 2 % 3.132 +");
        float res = calc.eval(tokens);
        assert(floatEquals(res, 8 % 2 + 3.132));
    }

    {
        auto tokens = Tokenize("8 2 % 3.132 2.123 5.6723 sum");
        float res = calc.eval(tokens);
        assert(floatEquals(res, 8 % 2 + 3.132 + 2.123 + 5.6723));
    }

    cout << "All tests passed!" << endl;
    return 0;
}
