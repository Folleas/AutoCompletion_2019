/*
** EPITECH PROJECT, 2020
** SYN_autoCompletion_2019
** File description:
** AddressBook
*/

#ifndef ADDRESSBOOK_HPP_
#define ADDRESSBOOK_HPP_

#include "Miscellaneous/Parser.hpp"

namespace AutoCompletion {

typedef struct Occurence_s {
    std::size_t count;
    char letter;
    std::string city;
    std::string associatedStreet;
    std::string associatedCity;
}Occurence;

class AddressBook {
    public:
        AddressBook(std::vector<std::shared_ptr<Address>> addresses);
        ~AddressBook();

        std::vector<std::shared_ptr<Address>> searchAddressCity(std::shared_ptr<Address> &searchedAddress);
        std::vector<std::shared_ptr<Address>> searchAddressStreet(std::shared_ptr<Address> &searchedAddress);

        bool checkOccurences(std::vector<Occurence> &occurences, char &c);
        void searchAddressVector(std::shared_ptr<Address> elem, std::vector<Occurence> &occurences, std::string &validatedLetter, std::size_t &pos);
        void searchAddressStreetNameVector(std::shared_ptr<Address> elem, std::vector<Occurence> &occurences, std::string validatedCity, std::string &validatedLetter, std::size_t &pos);
        bool processEmptyAddressVector(std::vector<Occurence> &occurences, std::string &validatedLetter);
        bool processEmptyAddressStreetNameVector(std::vector<Occurence> &occurences, std::string &validatedLetter);

        std::vector<Occurence> getCityOccurences(std::string &validatedLetter, std::size_t &pos);
        std::vector<Occurence> getStreetNameOccurences(std::string validatedCity, std::string &validatedLetter, std::size_t pos);
        bool isOccurence(std::vector<Occurence> occurences, Occurence elem);

        void setAddresses(std::vector<std::shared_ptr<Address>> value);

    private:
        std::vector<std::shared_ptr<Address>> _addresses;
};

};

#endif /* !ADDRESSBOOK_HPP_ */