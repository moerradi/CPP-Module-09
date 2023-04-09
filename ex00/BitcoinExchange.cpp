#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {
    std::cout << "Error: could not open file." << std::endl;
    std::exit(1);
}

BitcoinExchange::BitcoinExchange(std::string const &filename) {
    _file.open(filename);
    if (!_file.is_open()) {
        std::cout << "Error: could not open file." << std::endl;
        std::exit(1);
    }
}

BitcoinExchange::~BitcoinExchange() {
    if (_file.is_open()) {
        _file.close();
    }
}

BitcoinExchange::BitcoinExchange(BitcoinExchange const &other) {
    *this = other;
}

BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange const &other) {
    if (this != &other) {
        _prices = other._prices;
    }
    return *this;
}

double BitcoinExchange::stringToDouble(const std::string& str) {
    std::istringstream iss(str);
    double value;
    iss >> value;
    return value;
}

bool BitcoinExchange::isDouble(const std::string& str) {
    std::string::const_iterator it = str.begin();
    if (*it == '-') ++it;
    while (it != str.end() && std::isdigit(*it)) ++it;
    if (it == str.end()) return true;
    if (*it == '.') {
        ++it;
        while (it != str.end() && std::isdigit(*it)) ++it;
        return !str.empty() && it == str.end();
    }
    return false;
}

bool BitcoinExchange::isNumber(const std::string& str) {
    std::string::const_iterator it = str.begin();
    while (it != str.end() && std::isdigit(*it)) ++it;
    return !str.empty() && it == str.end();
}

bool BitcoinExchange::isLeapYear(int year) {
    if (year % 4 != 0) {
        return false;
    } else if (year % 100 != 0) {
        return true;
    } else if (year % 400 != 0) {
        return false;
    } else {
        return true;
    }
}
bool BitcoinExchange::isValidDate(const std::string& str) {
    if (str.length() != 10) return false;
    if (str[4] != '-' || str[7] != '-') return false;
    std::string year = str.substr(0, 4);
    std::string month = str.substr(5, 2);
    std::string day = str.substr(8, 2);
    if (!isNumber(year) || !isNumber(month) || !isNumber(day)) return false;
    int y = std::stoi(year);
    int m = std::stoi(month);
    int d = std::stoi(day);
    if (y < 0 || m < 0 || d < 0) return false;
    if (m > 12) return false;
    if (d > 31) return false;
    if (m == 2 && d > 29) return false;
    if (m == 2 && d == 29 && !isLeapYear(y)) return false;
    if (m == 4 && d > 30) return false;
    if (m == 6 && d > 30) return false;
    if (m == 9 && d > 30) return false;
    if (m == 11 && d > 30) return false;
    return true;
}

BitcoinExchange::ValueError BitcoinExchange::IsValidValue(std::string const &value) {
    // std::cout << "number is " << ">" << value << "<" << std::endl;
    if (!isDouble(value)) {
        return ENAN;
    }
    double d = stringToDouble(value);
    if (d > 1000) {
        return ETOOBIG;
    }
    else if (d < 0) {
        return ENEGATIVE;
    }
    return NONE;
}

void BitcoinExchange::parsecsv(std::string const &filename) {
    std::ifstream csv_file(filename);
    std::string line;
    getline(csv_file, line);
    while (getline(csv_file, line)) {
        std::string date = line.substr(0, 10);
        std::string price = line.substr(11);
        _prices[date] = stringToDouble(price);
    }
}

void BitcoinExchange::run() {
    std::string line;
    getline(_file, line);
    while (getline(_file, line)) {
        size_t pos = line.find(" | ");
        if (pos == std::string::npos) {
            std::cout << "Error: Wrong Input Format" << std::endl;
            continue;
        }
        std::string date = line.substr(0, pos);
        std::string price_str = line.substr(pos + 3);
        if (!isValidDate(date)) {
            std::cout << "Error: bad input => " << date << std::endl;
            continue;
        }
        ValueError error = IsValidValue(price_str);
        if (error != NONE) {
            if (error == ENAN) 
                std::cout << "Error: not a number." << std::endl;
            else if (error == ETOOBIG) 
                std::cout << "Error: too large a number." << std::endl;
            else if (error == ENEGATIVE) 
                std::cout << "Error: not a positive number." << std::endl;
            continue;
        }
        double price_double = stringToDouble(price_str);
        std::map<std::string, double>::const_iterator it = _prices.lower_bound(date);
        if ((*it).first != date && it != _prices.begin())
            it--;
        std::cout << date << " => " << price_str << " = " << (*it).second * price_double<< std::endl;
    }
}