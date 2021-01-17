/*
** EPITECH PROJECT, 2020
** SYN_autoCompletion_2019
** File description:
** AddressBook
*/

#include "Core/AddressBook.hpp"

namespace AutoCompletion {

AddressBook::AddressBook(std::vector<std::shared_ptr<Address>> addresses)
{
    setAddresses(addresses);
}

AddressBook::~AddressBook()
{
}

void AddressBook::setAddresses(std::vector<std::shared_ptr<Address>> value)
{
    this->_addresses = value;
}

bool AddressBook::isOccurence(std::vector<Occurence> occurences, Occurence elem)
{
    for (Occurence e : occurences) {
        if (e.count == elem.count && e.letter == elem.letter)
            return true;
    }
    return false;
}

bool AddressBook::checkOccurences(std::vector<Occurence> &occurences, char &c)
{
    for (Occurence &occurence : occurences) {
        if (std::toupper(occurence.letter) == std::toupper(c)) {
            occurence.count += 1;
            return true;
        }
    }
    return false;
}

void AddressBook::searchAddressVector(std::shared_ptr<Address> elem, std::vector<Occurence> &occurences, std::string &validatedLetter, std::size_t &pos)
{
    for (std::string elemCity : elem->getCityVector()) {
        for (auto & c: elemCity) c = toupper(c);
        if (!validatedLetter.empty() && elemCity.compare(validatedLetter) != elemCity.size() - validatedLetter.size()) {
            continue;
        }
        if (elemCity.size() - 1 < pos) {
            continue;
        }
        if (!checkOccurences(occurences, elemCity.at(pos)) && !(elemCity.substr(0, validatedLetter.size()).compare(validatedLetter))) {
            Occurence occurence = {1, static_cast<char>(std::toupper(elemCity.at(pos))), elem->getCity(), "", validatedLetter};
            occurences.push_back(occurence);
        }
    }
}

void AddressBook::searchAddressStreetNameVector(std::shared_ptr<Address> elem, std::vector<Occurence> &occurences, std::string validatedCity, std::string &validatedLetter, std::size_t &pos)
{
    for (std::string elemStreetName : elem->getStreetNameVector()) {
        for (auto & c: elemStreetName) c = toupper(c);
        if (!validatedLetter.empty() && elemStreetName.compare(validatedLetter) != elemStreetName.size() - validatedLetter.size()) {
            continue;
        }
        if (elemStreetName.size() - 1 < pos) {
            continue;
        }
        if (!checkOccurences(occurences, elemStreetName.at(pos)) && !(elemStreetName.substr(0, validatedLetter.size()).compare(validatedLetter))) {
            Occurence occurence = {1, static_cast<char>(std::toupper(elemStreetName.at(pos))), elem->getStreetName()};
            occurences.push_back(occurence);
        }
    }
}

bool AddressBook::processEmptyAddressVector(std::vector<Occurence> &occurences, std::string &validatedLetter)
{
    for (std::shared_ptr<Address> elem : this->_addresses) {
        for (std::string elemCity : elem->getCityVector()) {
            for (auto & c: elemCity) c = toupper(c);
            if (elemCity == validatedLetter) {
                Occurence occurence = {0, 0, elem->getCity(), "", validatedLetter};
                occurences.push_back(occurence);
                return true;
            }
        }
    }
    return false;
}

bool AddressBook::processEmptyAddressStreetNameVector(std::vector<Occurence> &occurences, std::string &validatedLetter)
{
    for (std::shared_ptr<Address> elem : this->_addresses) {
        for (std::string elemCity : elem->getStreetNameVector()) {
            for (auto & c: elemCity) c = toupper(c);
            if (elemCity == validatedLetter) {
                Occurence occurence = {0, 0, elem->getStreetName(), validatedLetter};
                occurences.push_back(occurence);
                return true;
            }
        }
    }
    return false;
}

std::vector<Occurence> AddressBook::getCityOccurences(std::string &validatedLetter, std::size_t &pos)
{
    std::vector<Occurence> occurences;

    for (std::shared_ptr<Address> elem : this->_addresses)
        searchAddressVector(elem, occurences, validatedLetter, pos);
    if (!occurences.empty() && occurences.size() == 1) {
        validatedLetter.push_back(std::toupper(occurences.at(0).letter));
        return (getCityOccurences(validatedLetter, ++pos));
    }
    else if (occurences.empty() && processEmptyAddressVector(occurences, validatedLetter))
        return occurences;
    return occurences;
}

std::vector<Occurence> AddressBook::getStreetNameOccurences(std::string validatedCity, std::string &validatedLetter, std::size_t pos)
{
    std::vector<Occurence> occurences;
    std::string upperValidatedCity = validatedCity;
    for (auto &c: upperValidatedCity) c = toupper(c);

    for (std::shared_ptr<Address> elem : this->_addresses) {
        std::string upperValidatedCity = validatedCity;
        for (auto &c: upperValidatedCity) c = toupper(c);

        std::string elemCity = elem->getCity();
        for (auto &c: elemCity) c = toupper(c);
        if (upperValidatedCity != elemCity)
            continue;
        searchAddressStreetNameVector(elem, occurences, validatedCity, validatedLetter, pos);
    }
    if (!occurences.empty() && occurences.size() == 1) {
        validatedLetter.push_back(std::toupper(occurences.at(0).letter));
        return (getStreetNameOccurences(validatedCity, validatedLetter, ++pos));
    }
    else if (occurences.empty() && processEmptyAddressStreetNameVector(occurences, validatedLetter))
        return occurences;
    return occurences;
}

std::vector<std::shared_ptr<Address>> AddressBook::searchAddressCity(std::shared_ptr<Address> &searchedAddress)
{
    std::vector<std::shared_ptr<Address>> addresses;

    if (searchedAddress->getCityAssociated().empty()) {
        for (std::shared_ptr<Address> elem : this->_addresses) {
            if (Utils::isSameWord(elem->getCity(), searchedAddress->getCity())) {
                addresses.push_back(elem);
            }
        }
    }
    for (std::shared_ptr<Address> elem : this->_addresses) {
        for (std::string city : elem->getCityVector()) {
            if (Utils::isSameWord(searchedAddress->getCityAssociated(), city)) {
                addresses.push_back(elem);
            }
        }
    }
    return addresses;
}

std::vector<std::shared_ptr<Address>> AddressBook::searchAddressStreet(std::shared_ptr<Address> &searchedAddress)
{
    std::vector<std::shared_ptr<Address>> addresses;

    if (searchedAddress->getStreetNameAssociated().empty()) {
        for (std::shared_ptr<Address> elem : this->_addresses) {
            if (Utils::isSameWord(elem->getCity(), searchedAddress->getCity())) {
                addresses.push_back(elem);
            }
        }
    }
    for (std::shared_ptr<Address> elem : this->_addresses) {
        if (elem->getCity() == searchedAddress->getCity()) {
            for (std::string street : elem->getStreetNameVector()) {
                if (Utils::isSameWord(searchedAddress->getStreetNameAssociated(), street)) {
                    addresses.push_back(elem);
                }
            }
        }
    }
    return addresses;
}

};