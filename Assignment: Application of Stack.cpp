#include <iostream>
#include <stack>
#include <string>
using namespace std;

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

int applyOp(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
    }
    return 0;
}

string infixToPostfix(const string& expression) {
    stack<char> operators;
    string postfix;
    
    for (char ch : expression) {
        if (isdigit(ch)) {
            postfix += ch;
        } else if (ch == '(') {
            operators.push(ch);
        } else if (ch == ')') {
            while (!operators.empty() && operators.top() != '(') {
                postfix += operators.top();
                operators.pop();
            }
            operators.pop();
        } else {
            while (!operators.empty() && precedence(operators.top()) >= precedence(ch)) {
                postfix += operators.top();
                operators.pop();
            }
            operators.push(ch);
        }
    }

    while (!operators.empty()) {
        postfix += operators.top();
        operators.pop();
    }

    return postfix;
}

int evaluatePostfix(const string& expression) {
    stack<int> values;
    
    for (char ch : expression) {
        if (isdigit(ch)) {
            values.push(ch - '0');
        } else {
            int b = values.top(); values.pop();
            int a = values.top(); values.pop();
            int result = applyOp(a, b, ch);
            values.push(result);
        }
    }

    return values.top();
}

int main() {
    string infix_expr = "3+5-2*3/2";
    string postfix_expr = infixToPostfix(infix_expr);
    
    cout << "Postfix Expression: " << postfix_expr << endl;
    
    int result = evaluatePostfix(postfix_expr);
    cout << "Result: " << result << endl;
    
    return 0;
}
