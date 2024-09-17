#include <iostream>
#include <stack>

using namespace std;

bool is_opening(char ch) {
    return ch == '(' || ch == '{' || ch == '[';
}

bool is_closing_for(char opening, char closing) {
    return (opening == '(' && closing == ')') || (opening == '[' && closing == ']') ||
           (opening == '{' && closing == '}');
}

bool is_balanced(string seq) {
    stack<char> brackets;
    for (char ch: seq) {
        if (is_opening(ch)) {
            brackets.push(ch);
        } else {
            if (brackets.empty()) {
                return false;
            }
            if (is_closing_for(brackets.top(), ch)) {
                brackets.pop();
            } else {
                return false;
            }
        }
    }
    return brackets.empty();
}

int main() {
    cout << (is_balanced("[]") == true) << endl;
    cout << (is_balanced("()") == true) << endl;
    cout << (is_balanced("{}") == true) << endl;
    cout << (is_balanced("([{}])") == true) << endl;
    cout << (is_balanced("{}]") == false) << endl;
    cout << (is_balanced("{") == false) << endl;
    cout << (is_balanced(")") == false) << endl;
    cout << (is_balanced(")(") == false) << endl;
    cout << (is_balanced("([)]") == false) << endl;
    cout << (is_balanced("({})[]") == true) << endl;
    return 0;
}
