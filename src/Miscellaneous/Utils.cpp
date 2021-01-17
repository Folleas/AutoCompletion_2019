/*
** EPITECH PROJECT, 2020
** SYN_autoCompletion_2019
** File description:
** Utils
*/

#include "Miscellaneous/Utils.hpp"

StreetType Utils::getStreetType(const std::string &str)
{
    static std::unordered_map<std::string, StreetType> map = {{"allée", StreetType::ALLEE}, {"avenue", StreetType::AVENUE}, {"boulevard", StreetType::BOULEVARD}, {"chemin", StreetType::CHEMIN}, {"impasse", StreetType::IMPASSE}, {"place", StreetType::PLACE}, {"quai", StreetType::QUAI}, {"rue", StreetType::RUE}, {"square", StreetType::SQUARE}};

    return (map[str]);
}

std::string Utils::upper(const std::string &str)
{
    std::string tmp(str);

    for (auto & c: tmp) c = toupper(c);
    return tmp;
}

std::string Utils::getStreetTypeString(const StreetType &type)
{
    static std::unordered_map<StreetType, std::string> map = {{StreetType::ALLEE, "allée"}, {StreetType::AVENUE, "avenue"}, {StreetType::BOULEVARD, "boulevard"}, {StreetType::CHEMIN, "chemin"}, {StreetType::IMPASSE, "impasse"}, {StreetType::PLACE, "place"}, {StreetType::QUAI, "quai"}, {StreetType::RUE, "rue"}, {StreetType::SQUARE, "square"}};

    return map[type];
}

bool Utils::isSameWord(const std::string &str1, const std::string &str2)
{
    std::string tmp1(str1);
    std::string tmp2(str2);
    for (auto & c: tmp1) c = toupper(c);
    for (auto & c: tmp2) c = toupper(c);
    return tmp1 == tmp2;
}

bool Utils::isEmpty(std::ifstream &pFile)
{
    return pFile.peek() == std::ifstream::traits_type::eof();
}

bool Utils::isSorted(const std::string &str1, const std::string &str2)
{
    for (std::size_t i = 0; i != str1.size() && i != str2.size(); i++) {
        if (str1.at(i) > str2.at(i))
            return false;
    }
    return true;
}