#include <exception>
#include <iostream>

class MyException : public std::exception
{
    public:
        MyException(const std::string &str) {
            _str = str;
        }
        const char *what() const noexcept {
            return _str.c_str();
        }

    private:
        std::string _str;
};

class MyExit : public std::exception
{
    public:
        MyExit(const std::string &str) {
            _str = str;
        }
        const char *what() const noexcept {
            return _str.c_str();
        }

    private:
        std::string _str;
};