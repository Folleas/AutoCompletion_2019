/*
** EPITECH PROJECT, 2020
** SYN_autoCompletion_2019
** File description:
** Address
*/

#include "Core/Address.hpp"

namespace AutoCompletion {

void Address::setAddress(const std::string &city, const std::string &number, const std::string &streetType, const std::string &streetName)
{
    this->_city = city;
    this->_cityVector = formatCity(city);
    this->_number = std::stoi(number);
    this->_streetType = Utils::getStreetType(streetType);
    this->_streetName = streetName;
    this->_streetNameVector = formatCity(_streetName);
}

std::vector<std::string> Address::formatCity(const std::string &city)
{
    std::vector<std::string> cityVector;
    std::size_t count = 0;
    std::string str;

    for (char c : city) {
        if (c == ' ' || c == '-') {
            cityVector.push_back(str);
            str.clear();
            count++;
            continue;
        }
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
            str.push_back(c);
    }
    cityVector.push_back(str);
    return cityVector;
}

std::vector<std::string> Address::getCityVector() const
{
    return this->_cityVector;
}

std::string Address::getCity() const
{
    return this->_city;
}

std::string Address::getStreetName() const
{
    return this->_streetName;
}

std::string Address::getStreetNameAssociated(void) const
{
    return this->_streetAssociated;
}

std::size_t Address::getNumber(void) const
{
    return this->_number;
}

std::string Address::getStreetType(void) const
{
    return Utils::getStreetTypeString(this->_streetType);
}

std::string Address::format()
{
    std::string ret(this->_city + ", " + std::to_string(this->_number) + " " + Utils::getStreetTypeString(this->_streetType) + " " + this->_streetName);
    return ret;
}

void Address::print()
{
    std::cout << "=> " << this->_city << ", " << this->_number << " " << Utils::getStreetTypeString(this->_streetType) << " " << this->_streetName << std::endl;
}

void Address::setCity(const std::string &city)
{
    this->_city = city;
}

void Address::setNumber(const std::string &number)
{
    this->_number = std::stoi(number);
}

void Address::setCityAssociated(const std::string &streetName)
{
    this->_cityAssociated = streetName;
}

std::string Address::getCityAssociated(void) const
{
    return _cityAssociated;
}

void Address::setStreetType(const std::string &streetType)
{
    this->_streetType = Utils::getStreetType(streetType);
}

void Address::setStreetName(const std::string &streetName)
{
    this->_streetName = streetName;
}

void Address::setStreetNameAssociated(const std::string &streetName)
{
    this->_streetAssociated = streetName;
}

std::vector<std::string> Address::getStreetNameVector(void) const
{
    return this->_streetNameVector;
}

};