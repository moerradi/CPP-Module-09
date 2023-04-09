#pragma once
#include <string>
#include <stack>
#include <sstream>
#include <iostream>

class RPN {
    private:
        std::stack<double> _stack;
        bool perform_operation(const std::string &operation);
        bool is_operator(const std::string &operation);
        int pop();


    public:
        RPN();
        RPN(RPN const &other);
        ~RPN();
        RPN &operator=(RPN const &other);

        void calculate(const std::string &input);
};
