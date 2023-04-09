#include "RPN.hpp"

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cout << "Error: please provide a correct input." << std::endl;
        return 1;
    }
    try
    {
        RPN rpn;
        rpn.calculate(argv[1]);
        return 0;
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << '\n';
        return 1;
    }
}