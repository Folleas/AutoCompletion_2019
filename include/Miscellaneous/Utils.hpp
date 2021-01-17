/*
** EPITECH PROJECT, 2020
** SYN_autoCompletion_2019
** File description:
** Utils
*/

#ifndef UTILS_HPP_
#define UTILS_HPP_

#include <string>
#include <unordered_map>
#include <fstream>

#include "Miscellaneous/Exception.hpp"

typedef enum StreetType_e {
    ALLEE = 0,
    AVENUE = 1,
    BOULEVARD = 2,
    CHEMIN = 3,
    IMPASSE = 4,
    PLACE = 5,
    QUAI = 6,
    RUE = 7,
    SQUARE = 8
}StreetType;

class Utils {
    public:
        Utils();
        ~Utils() = default;

        static bool isEmpty(std::ifstream& pFile);
        static std::string formatString(std::string &str);
        static bool isSameWord(const std::string &str1, const std::string &str2);
        static std::string upper(const std::string &str);

        static std::string getStreetTypeString(const StreetType &type);
        static StreetType getStreetType(const std::string &str);
        static bool isSorted(const std::string &str1, const std::string &str2);
    private:
};

#endif /* !UTILS_HPP_ */