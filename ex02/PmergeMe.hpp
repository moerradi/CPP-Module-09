#include <iostream>
#include <sstream>
#include <vector>
#include <deque>
#include <ctime>
#include <sys/time.h>
#include <iomanip>

class PmergeMe {
    public:
        PmergeMe();
        ~PmergeMe();
        void parse(int ac, char **av);
        void run();

    private:
        void print_vec(std::string const &state);
        void print_deq(std::string const &state);
        void vec_insertion_sort(std::vector<int>::iterator left, std::vector<int>::iterator right);
        void deq_insertion_sort(std::deque<int>::iterator left, std::deque<int>::iterator right);
        void merge_vec(std::vector<int>::iterator left, std::vector<int>::iterator mid, std::vector<int>::iterator right);
        void merge_deq(std::deque<int>::iterator left, std::deque<int>::iterator mid, std::deque<int>::iterator right);
        void sort_vector(std::vector<int>& vec, std::vector<int>::iterator left, std::vector<int>::iterator right);
        void sort_deque(std::deque<int>& deq, std::deque<int>::iterator left, std::deque<int>::iterator right);
        bool isNumeric(std::string const &s);
        void runVector();
        void runDeque();

        std::vector<int> vec;
        std::deque<int> deq;
};