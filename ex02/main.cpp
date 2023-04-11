#include <iostream>
#include <sstream>
#include <vector>
#include "PmergeMe.hpp"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Error: Not enough arguments." << std::endl;
        return 1;
    }
    try
    {

        PmergeMe pmergeMe;
        pmergeMe.parse(argc, argv);
        pmergeMe.run();
    }
    catch (std::runtime_error &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}
