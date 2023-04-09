#include "RPN.hpp"

RPN::RPN() {
}

RPN::RPN(RPN const &other) {
    *this = other;
}

RPN::~RPN() {
}

int RPN::pop() {
    if (_stack.empty()) {
        throw std::runtime_error("Stack is empty.");
    }
    double value = _stack.top();
    _stack.pop();
    return value;
}

RPN &RPN::operator=(RPN const &other) {
    if (this != &other) {
        _stack = other._stack;
    }
    return *this;
}

bool RPN::is_operator(const std::string &operation) {
    return operation == "+" || operation == "-" || operation == "*" || operation == "/";
}

bool RPN::perform_operation(const std::string &operation) {
    if (_stack.size() < 2)
        return false;
    double a = pop();
    double b = pop();
    if (operation == "+") {
        _stack.push(a + b);
    } else if (operation == "-") {
        _stack.push(b - a);
    } else if (operation == "*") {
        _stack.push(a * b);
    } else if (operation == "/") {
        _stack.push(b / a);
    }
    return true;
}

void RPN::calculate(const std::string &input) {
    std::istringstream iss(input);
    std::string token;
    while (iss >> token) {
        if (is_operator(token)) {
            if (!perform_operation(token)) {
                throw std::runtime_error("Error: invalid input.");
                return;
            }
        } else if (token.length() == 1 && std::isdigit(token[0])) {
            _stack.push(std::stod(token));
        } else {
            throw std::runtime_error("Error: invalid input.");
            return;
        }
    }
    if (_stack.size() != 1) {
        throw std::runtime_error("Error: invalid input.");
        return;
    }
    std::cout << _stack.top() << std::endl;
}