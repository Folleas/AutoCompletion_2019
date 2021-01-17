/*
** EPITECH PROJECT, 2020
** SYN_autoCompletion_2019
** File description:
** Address
*/

#ifndef ADDRESS_HPP_
#define ADDRESS_HPP_

#include "Miscellaneous/Utils.hpp"
#include <vector>

namespace AutoCompletion {

class Address {
    public:
        Address() = default;
        ~Address() = default;

        std::vector<std::string> formatCity(const std::string &city);
        void print(void);
        std::string format(void);

        std::size_t getNumber(void) const;
        std::vector<std::string> getCityVector(void) const;
        std::string getCity(void) const;
        std::string getStreetType(void) const;
        std::vector<std::string> getStreetNameVector(void) const;
        std::string getStreetName(void) const;
        std::string getStreetNameAssociated(void) const;
        std::string getCityAssociated(void) const;

        void setAddress(const std::string &city, const std::string &number, const std::string &streetType, const std::string &streetName);
        void setCity(const std::string &city);
        void setNumber(const std::string &number);
        void setStreetType(const std::string &streetType);
        void setStreetName(const std::string &streetName);
        void setStreetNameAssociated(const std::string &streetName);
        void setCityAssociated(const std::string &streetName);

    private:
        std::vector<std::string> _cityVector;
        std::string _cityAssociated;
        std::string _city;
        std::size_t _number;
        StreetType _streetType;
        std::vector<std::string> _streetNameVector;
        std::string _streetName;
        std::string _streetAssociated;
};

};

#endif /* !ADDRESS_HPP_ */