#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{
}

PmergeMe::~PmergeMe()
{
}

void PmergeMe::print_vec(std::string const &state)
{
    std::cout << state << ": ";
    for (std::vector<int>::const_iterator it = vec.begin(); it != vec.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
}

void PmergeMe::print_deq(std::string const &state)
{
    std::cout << state << ": ";
    for (std::deque<int>::const_iterator it = deq.begin(); it != deq.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
}

void PmergeMe::vec_insertion_sort(std::vector<int>::iterator left, std::vector<int>::iterator right)
{
    for (std::vector<int>::iterator it = left + 1; it != right; ++it)
    {
        std::vector<int>::iterator it2 = it;
        while (it2 != left && *(it2 - 1) > *it2)
        {
            std::swap(*it2, *(it2 - 1));
            --it2;
        }
    }
}

void PmergeMe::deq_insertion_sort(std::deque<int>::iterator left, std::deque<int>::iterator right)
{
    for (std::deque<int>::iterator it = left + 1; it != right; ++it)
    {
        std::deque<int>::iterator it2 = it;
        while (it2 != left && *(it2 - 1) > *it2)
        {
            std::swap(*it2, *(it2 - 1));
            --it2;
        }
    }
}

void PmergeMe::merge_vec(std::vector<int>::iterator left, std::vector<int>::iterator mid, std::vector<int>::iterator right)
{
    std::vector<int> temp(right - left);
    std::vector<int>::iterator i = left;
    std::vector<int>::iterator j = mid;

    for (std::vector<int>::iterator k = temp.begin(); k != temp.end(); ++k)
    {
        if (j == right || *i < *j)
            *k = *i++;
        else
            *k = *j++;
    }
    std::copy(temp.begin(), temp.end(), left);
}

void PmergeMe::merge_deq(std::deque<int>::iterator left, std::deque<int>::iterator mid, std::deque<int>::iterator right)
{
    std::deque<int> temp(right - left);
    std::deque<int>::iterator i = left;
    std::deque<int>::iterator j = mid;

    for (std::deque<int>::iterator k = temp.begin(); k != temp.end(); ++k)
    {
        if (j == right || *i < *j)
            *k = *i++;
        else
            *k = *j++;
    }
    std::copy(temp.begin(), temp.end(), left);
}

void PmergeMe::sort_vector(std::vector<int> &vec, std::vector<int>::iterator left, std::vector<int>::iterator right)
{
    if (right - left > 42)
    {
        std::vector<int>::iterator mid = left + (right - left) / 2;
        sort_vector(vec, left, mid);
        sort_vector(vec, mid, right);
        merge_vec(left, mid, right);
    }
    else
    {
        vec_insertion_sort(left, right);
    }
}

void PmergeMe::sort_deque(std::deque<int> &deq, std::deque<int>::iterator left, std::deque<int>::iterator right)
{
    if (right - left > 42)
    {
        std::deque<int>::iterator mid = left + (right - left) / 2;
        sort_deque(deq, left, mid);
        sort_deque(deq, mid, right);
        merge_deq(left, mid, right);
    }
    else
    {
        deq_insertion_sort(left, right);
    }
}

bool PmergeMe::isNumeric(std::string const &s)
{
    for (std::string::const_iterator it = s.begin(); it != s.end(); ++it)
    {
        if (isdigit(*it) == 0)
            return false;
    }
    return true;
}

void PmergeMe::parse(int ac, char **av)
{
    for (int i = 1; i < ac; ++i)
    {
        if (isNumeric(av[i]))
        {
            vec.push_back(atoi(av[i]));
            deq.push_back(atoi(av[i]));
        }
        else
        {
            throw std::runtime_error("Error: Invalid argument");
        }
        
    }
}

void PmergeMe::runVector()
{
    timeval startTime, endTime;
    print_vec("Before");
    gettimeofday(&startTime, NULL);
    sort_vector(vec, vec.begin(), vec.end());
    gettimeofday(&endTime, NULL);
    long elapsedTime = (endTime.tv_sec - startTime.tv_sec) * 1000000L + (endTime.tv_usec - startTime.tv_usec);
    double ms = static_cast<double>(elapsedTime);
    print_vec("After");
    std::cout << "Time to process a range of " << vec.size() <<  " elements with std::vector : " << std::fixed << std::setprecision(5) << ms << " us" << std::endl;  
}

void PmergeMe::runDeque()
{
    timeval startTime, endTime;
    print_deq("Before");
    gettimeofday(&startTime, NULL);
    sort_deque(deq, deq.begin(), deq.end());
    gettimeofday(&endTime, NULL);
    long elapsedTime = (endTime.tv_sec - startTime.tv_sec) * 1000000L + (endTime.tv_usec - startTime.tv_usec);
    double ms = static_cast<double>(elapsedTime);
    print_deq("After");
    std::cout << "Time to process a range of " << deq.size() <<  " elements with std::deque : " << std::fixed << std::setprecision(5) << ms << " us" << std::endl;  
}

void PmergeMe::run()
{
    runVector();
    runDeque();
}