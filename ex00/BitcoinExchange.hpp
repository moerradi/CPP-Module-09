#pragma once
#include <iostream>
#include <map>
#include <fstream>
#include <cstdlib>
#include <sstream>


class BitcoinExchange {
    public:
        BitcoinExchange();
        BitcoinExchange(std::string const &filename);
        ~BitcoinExchange();
        BitcoinExchange(BitcoinExchange const &other);
        BitcoinExchange &operator=(BitcoinExchange const &other);

        void parsecsv(std::string const &filename);
        void run();
        enum ValueError {
            ENAN,
            ETOOBIG,
            ENEGATIVE,
            NONE
        };
    private:
        double stringToDouble(const std::string& str);
        bool isDouble(const std::string& str);
        bool isNumber(const std::string& str);
        bool isLeapYear(int year);
        bool isValidDate(const std::string& str);
        ValueError IsValidValue(std::string const &value);

        std::map<std::string, double> _prices; 
        std::ifstream _file;
};