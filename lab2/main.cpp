#include "lab2.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <queue>
#include <sstream>
#include <cctype>

int right_symbols[15] = { 42, 43, 45, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 61 };

bool is_matching_pair(char open, char close) {
    return (open == '(' && close == ')');
}
bool check_pairs(const std::string& expr, stack& sequence) {
    for (char element : expr) {
        if (element == '(') {
            sequence.push(element);
        }
        else if (element == ')') {
            if (sequence.is_empty() || !is_matching_pair(sequence.peek(), element)) {
                return false;
            }
            sequence.pop();
        }
    }
    return sequence.is_empty();
}
bool check_unnecessary_symbols(const std::string& expr) {
    for (char element : expr) {
        if (!std::isdigit(element) && std::find(std::begin(right_symbols), std::end(right_symbols), element) == std::end(right_symbols)
            && element != '(' && element != ')' && element != '=') {
            return true;
        }
    }
    return false;
}
int precedence(char op) {
    if (op == '+' || op == '-') {
        return 1;
    }
    if (op == '*' || op == '/') {
        return 2;
    }
    return 0;
}

double apply_operator(double a, double b, char op) {
    switch (op) {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/':
        if (b == 0) {
            throw std::runtime_error("Division by zero");
        }
        return a / b;
    default:
        throw std::runtime_error("Unknown operator");
    }
}

std::queue<std::string> infix_to_postfix(const std::string& expr) {
    stack operators(expr.size());
    std::queue<std::string> output;
    std::string number;

    for (size_t i = 0; i < expr.length(); ++i) {
        char token = expr[i];

        if (std::isdigit(token)) {
            number += token;
        }
        else {
            if (!number.empty()) {
                output.push(number);
                number.clear();
            }

            if (token == '+' || token == '-' || token == '*' || token == '/') {
                while (!operators.is_empty() && precedence(operators.peek()) >= precedence(token)) {
                    output.push(std::string(1, operators.pop()));
                }
                operators.push(token);
            }
            else if (token == '(') {
                operators.push(token);
            }
            else if (token == ')') {
                while (!operators.is_empty() && operators.peek() != '(') {
                    output.push(std::string(1, operators.pop()));
                }
                operators.pop(); 
            }
        }
    }

    if (!number.empty()) {
        output.push(number);
    }

    while (!operators.is_empty()) {
        output.push(std::string(1, operators.pop()));
    }

    return output;
}

double evaluate_postfix(std::queue<std::string>& postfix) {
    stack values(postfix.size());

    while (!postfix.empty()) {
        std::string token = postfix.front();
        postfix.pop();

        if (std::isdigit(token[0])) {
            values.push(std::stod(token));
        }
        else {
            double b = values.pop();
            double a = values.pop();
            values.push(apply_operator(a, b, token[0]));
        }
    }

    return values.peek();
}

int main() {
    std::string expr;
    std::cout << "Enter expression:" << std::endl;
    std::getline(std::cin, expr); 

    if (expr.back() == '=') {
        expr.pop_back();
    }
    if (check_unnecessary_symbols(expr)) {
        std::cout << "Error" << std::endl;
        return 1;
    }
    stack sequence(expr.size());
    if (!check_pairs(expr, sequence)) {
        std::cout << "Error" << std::endl;
        return 1;
    }
    try {
        std::queue<std::string> postfix = infix_to_postfix(expr);
        double result = evaluate_postfix(postfix);
        std::cout << "Result: " << result << std::endl;
    }
    catch (const std::runtime_error& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    return 0;
}
