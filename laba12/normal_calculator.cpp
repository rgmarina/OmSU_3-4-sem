#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>
#include <stdexcept>
#include <cassert>
#include <functional>
#include <memory>
#include <cctype>
#include <cmath>

// Парсер чисел с плавающей точкой без использования std::stof
class FloatParser {
public:
    static float parse(const std::string& token) {
        size_t len = token.length();
        if (len == 0) {
            throw std::runtime_error("Invalid float: empty string");
        }

        bool hasDecimalPoint = false;//содержит ли строка допустимоые числа
        size_t start = 0;
        if (token[0] == '-' || token[0] == '+') {
            start = 1;
        }

        if (start == len) {
            throw std::runtime_error("Invalid float: " + token);
        }

        for (size_t i = start; i < len; ++i) {
            if (token[i] == '.') {
                if (hasDecimalPoint) {
                    throw std::runtime_error("Invalid float: multiple decimal points in " + token);
                }
                hasDecimalPoint = true;
            } else if (!isdigit(token[i])) {
                throw std::runtime_error("Invalid float: non-digit character in " + token);
            }
        }

        float result = 0.0f;
        float sign = (token[0] == '-') ? -1.0f : 1.0f;
        float factor = 1.0f;
        bool decimalPart = false;

        for (size_t i = (token[0] == '-' || token[0] == '+') ? 1 : 0; i < len; ++i) {
            if (token[i] == '.') {
                decimalPart = true;
                continue;
            }
            int digit = token[i] - '0';
            if (decimalPart) {
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
    virtual void apply(std::stack<float>& stk) const = 0;
    virtual ~Operator() = default;
    virtual int precedence() const = 0;
    virtual bool isLeftAssociative() const = 0;
};

// Класс калькулятора
class Calculator {
public:
    void registerOp(const std::string& symbol, std::shared_ptr<Operator> op) {
        operators[symbol] = op;
    }

    float eval(const std::vector<std::string>& tokens) {//вычисление значения выражений
        std::stack<float> stk;
        for (const auto& token : tokens) {
            if (isOperator(token)) {
                auto it = operators.find(token);
                if (it != operators.end()) {
                    it->second->apply(stk);
                } else {
                    throw std::runtime_error("Unknown operator: " + token);
                }
            } else {
                stk.push(FloatParser::parse(token));
            }
        }
        if (stk.size() != 1) {
            throw std::runtime_error("Invalid expression");
        }
        return stk.top();
    }

    bool isOperator(const std::string& token) const {//токен-оператор?, приоритет
        return operators.find(token) != operators.end();
    }

    int getPrecedence(const std::string& token) const {
        auto it = operators.find(token);
        if (it != operators.end()) {
            return it->second->precedence();
        }
        return 0;
    }

    bool isLeftAssociative(const std::string& token) const {
        auto it = operators.find(token);
        if (it != operators.end()) {
            return it->second->isLeftAssociative();
        }
        return true; // Default to true for standard operators
    }

private://хранение операторов
    std::unordered_map<std::string, std::shared_ptr<Operator>> operators;
};

// Операторы для стандартных операций
class AddOp : public Operator {
public:
    void apply(std::stack<float>& stk) const override {
        if (stk.size() < 2) {
            throw std::runtime_error("Insufficient operands for +");
        }
        float b = stk.top(); stk.pop();
        float a = stk.top(); stk.pop();
        stk.push(a + b);
    }

    int precedence() const override { return 1; }
    bool isLeftAssociative() const override { return true; }
};

class SubtractOp : public Operator {
public:
    void apply(std::stack<float>& stk) const override {
        if (stk.size() < 2) {
            throw std::runtime_error("Insufficient operands for -");
        }
        float b = stk.top(); stk.pop();
        float a = stk.top(); stk.pop();
        stk.push(a - b);
    }

    int precedence() const override { return 1; }
    bool isLeftAssociative() const override { return true; }
};

class MultiplyOp : public Operator {
public:
    void apply(std::stack<float>& stk) const override {
        if (stk.size() < 2) {
            throw std::runtime_error("Insufficient operands for *");
        }
        float b = stk.top(); stk.pop();
        float a = stk.top(); stk.pop();
        stk.push(a * b);
    }

    int precedence() const override { return 2; }
    bool isLeftAssociative() const override { return true; }
};

class DivideOp : public Operator {
public:
    void apply(std::stack<float>& stk) const override {
        if (stk.size() < 2) {
            throw std::runtime_error("Insufficient operands for /");
        }
        float b = stk.top(); stk.pop();
        float a = stk.top(); stk.pop();
        if (b == 0) {
            throw std::runtime_error("Division by zero");
        }
        stk.push(a / b);
    }

    int precedence() const override { return 2; }
    bool isLeftAssociative() const override { return true; }
};

// Оператор модуля
class ModuloOp : public Operator {
public:
    void apply(std::stack<float>& stk) const override {
        if (stk.size() < 2) {
            throw std::runtime_error("Insufficient operands for %");
        }
        float b = stk.top(); stk.pop();
        float a = stk.top(); stk.pop();
        stk.push(static_cast<int>(a) % static_cast<int>(b));
    }

    int precedence() const override { return 2; }
    bool isLeftAssociative() const override { return true; }
};

// Оператор суммирования
class SumOp : public Operator {
public:
    void apply(std::stack<float>& stk) const override {
        float sum = 0;
        while (!stk.empty()) {
            sum += stk.top();
            stk.pop();
        }
        stk.push(sum);
    }

    int precedence() const override { return 0; }
    bool isLeftAssociative() const override { return false; }
};

// Обновленная функция разбора строки на токены
std::vector<std::string> Tokenize(const std::string& expression, const Calculator& calc) {
    std::vector<std::string> tokens;
    std::string token;

    for (size_t i = 0; i < expression.size(); ++i) {
        char ch = expression[i];
        if (isspace(ch)) {
            continue;
        }

        if (isdigit(ch) || (ch == '-' && (i == 0 || !isdigit(expression[i - 1])))) {//учет числа, скобки и операторов
            token += ch;
            while (i + 1 < expression.size() && (isdigit(expression[i + 1]) || expression[i + 1] == '.')) {
                token += expression[++i];
            }
            tokens.push_back(token);
            token.clear();
        } else if (ch == '(' || ch == ')') {
            tokens.push_back(std::string(1, ch));
        } else {
            std::string op(1, ch);
            while (i + 1 < expression.size() && !isspace(expression[i + 1]) && !isdigit(expression[i + 1]) && expression[i + 1] != '(' && expression[i + 1] != ')') {
                op += expression[++i];
            }
            if (calc.isOperator(op)) {
                tokens.push_back(op);
            } else {
                throw std::runtime_error("Unknown character or operator: " + op);
            }
        }
    }
    return tokens;
}

// Алгоритм сортировочной станции для преобразования инфиксной записи в обратную польскую
std::vector<std::string> ShuntingYard(const std::vector<std::string>& tokens, const Calculator& calc) {
    std::vector<std::string> output;
    std::stack<std::string> operators;

    for (const auto& token : tokens) {
        if (isdigit(token[0]) || (token[0] == '-' && token.size() > 1 && isdigit(token[1])) || token == ".") {
            output.push_back(token);
        } else if (token == "(") {
            operators.push(token);
        } else if (token == ")") {
            while (!operators.empty() && operators.top() != "(") {
                output.push_back(operators.top());
                operators.pop();
            }
            if (operators.empty()) {
                throw std::runtime_error("Mismatched parentheses");
            }
            operators.pop();
        } else if (calc.isOperator(token)) {
            while (!operators.empty() && calc.isOperator(operators.top()) &&
                   ((calc.isLeftAssociative(token) && calc.getPrecedence(token) <= calc.getPrecedence(operators.top())) ||
                    (!calc.isLeftAssociative(token) && calc.getPrecedence(token) < calc.getPrecedence(operators.top())))) {
                output.push_back(operators.top());
                operators.pop();
            }
            operators.push(token);
        } else {
            throw std::runtime_error("Unknown token: " + token);
        }
    }

    while (!operators.empty()) {
        if (operators.top() == "(") {
            throw std::runtime_error("Mismatched parentheses");
        }
        output.push_back(operators.top());
        operators.pop();
    }

    return output;
}

bool floatEquals(float a, float b, float epsilon = 0.0001f) {
    return std::fabs(a - b) < epsilon;
}

int main() {
    Calculator calc;//операторы выражений
    calc.registerOp("+", std::make_shared<AddOp>());
    calc.registerOp("-", std::make_shared<SubtractOp>());
    calc.registerOp("*", std::make_shared<MultiplyOp>());
    calc.registerOp("/", std::make_shared<DivideOp>());
    calc.registerOp("%", std::make_shared<ModuloOp>());
    calc.registerOp("mod", std::make_shared<ModuloOp>());
    calc.registerOp("sum", std::make_shared<SumOp>());

    // Тесты с использованием обратной польской нотации (RPN)
    {
        auto tokens = std::vector<std::string>{"6", "8", "+", "3", "mod"};
        float res = calc.eval(tokens);
        assert(floatEquals(res, static_cast<int>(6 + 8) % 3));
    }

    {
        auto tokens = std::vector<std::string>{"1", "2", "3", "4", "5", "6", "sum"};
        float res = calc.eval(tokens);
        assert(floatEquals(res, 1 + 2 + 3 + 4 + 5 + 6));
    }

    {
        auto tokens = std::vector<std::string>{"5", "3", "-", "2", "/"};
        float res = calc.eval(tokens);
        assert(floatEquals(res, (5 - 3) / 2.0f));
    }

    {
        auto tokens = std::vector<std::string>{"7", "3", "*", "2", "+", "5", "/"};
        float res = calc.eval(tokens);
        assert(floatEquals(res, (7 * 3 + 2) / 5.0f));
    }

    // Тесты с использованием инфиксной нотации и алгоритма сортировочной станции
    {
        std::string s = "(1 + 4) / 5 + 9 mod 2";
        auto infix_tokens = Tokenize(s, calc);
        auto polish_tokens = ShuntingYard(infix_tokens, calc);
        float res = calc.eval(polish_tokens);
        assert(floatEquals(res, (1 + 4) / 5.0f + static_cast<int>(9) % 2));
    }

    {
        std::string s = "3 + 4 * 2 / ( 1 - 5 )";
        auto infix_tokens = Tokenize(s, calc);
        auto polish_tokens = ShuntingYard(infix_tokens, calc);
        float res = calc.eval(polish_tokens);
        assert(floatEquals(res, 3 + 4 * 2 / static_cast<float>(1 - 5)));
    }

    {
        std::string s = "10 + ( 3 * 5 ) / ( 16 - 4 )";
        auto infix_tokens = Tokenize(s, calc);
        auto polish_tokens = ShuntingYard(infix_tokens, calc);
        float res = calc.eval(polish_tokens);
        assert(floatEquals(res, 10 + (3 * 5) / static_cast<float>(16 - 4)));
    }

    {
        std::string s = "10.23 + (-3.1 * 5.5) / (16.9 - -4.2)";
        auto infix_tokens = Tokenize(s, calc);
        auto polish_tokens = ShuntingYard(infix_tokens, calc);
        float res = calc.eval(polish_tokens);
        assert(floatEquals(res, 10.23 + (-3.1 * 5.5) / static_cast<float>(16.9 - -4.2)));
    }

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
