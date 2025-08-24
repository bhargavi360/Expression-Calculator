#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <cctype>
#include <map>
#include <vector>

using namespace std;

// Function to determine the precedence of operators
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Function to convert infix expression to postfix
string infixToPostfix(const string& infix) {
    stack<char> operators;
    string postfix;
    for (char token : infix) {
        if (isspace(token)) continue; // Skip whitespace
        if (isdigit(token)) {
            postfix += token; // Add number to output
        } else {
            postfix += ' '; // Add space before operator
            while (!operators.empty() && precedence(operators.top()) >= precedence(token)) {
                postfix += operators.top();
                operators.pop();
            }
            operators.push(token);
        }
    }
    while (!operators.empty()) {
        postfix += ' ';
        postfix += operators.top();
        operators.pop();
    }
    return postfix;
}

// Function to evaluate postfix expression
double evaluatePostfix(const string& postfix) {
    stack<double> values;
    istringstream tokens(postfix);
    string token;
    while (tokens >> token) {
        if (isdigit(token[0])) {
            values.push(stod(token)); // Convert string to double and push to stack
        } else {
            double right = values.top(); values.pop();
            double left = values.top(); values.pop();
            switch (token[0]) {
                case '+': values.push(left + right); break;
                case '-': values.push(left - right); break;
                case '*': values.push(left * right); break;
                case '/': values.push(left / right); break;
            }
        }
    }
    return values.top(); // The result is the last value in the stack
}

int main() {
    string infix;
    cout << "Enter an infix expression: ";
    getline(cin, infix);

    string postfix = infixToPostfix(infix);
    cout << "Postfix expression: " << postfix << endl;

    double result = evaluatePostfix(postfix);
    cout << "Result: " << result << endl;

    return 0;
}
