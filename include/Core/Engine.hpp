/*
** EPITECH PROJECT, 2020
** SYN_autoCompletion_2019
** File description:
** Engine
*/

#ifndef ENGINE_HPP_
#define ENGINE_HPP_

#include "Core/AddressBook.hpp"
#include "Core/Input.hpp"

namespace AutoCompletion {
    class Engine : public Input {
        public:
            Engine(const std::string &path);
            ~Engine();

            void sortAddressVector(std::vector<std::shared_ptr<Address>> &addresses);
            std::vector<std::shared_ptr<AutoCompletion::Address>> manageCityChoices(std::shared_ptr<Address> searchedAddress);
            std::vector<std::shared_ptr<Address>> manageStreetChoices(std::shared_ptr<Address> searchedAddress);
            bool checkOccurences(std::vector<Occurence> tmp);
            void printMostProbableStreetChoice(std::string validatedCity, std::string validatedLetters, std::vector<Occurence> occurences);
            void printMostProbableCityChoice(std::string validatedLetters, std::vector<Occurence> occurences);
            std::vector<Occurence> sortOccurences(std::vector<Occurence> occurences);
            bool isSorted(std::vector<Occurence> &occurences);
            std::pair<std::size_t, std::size_t> findHighestOccurence(std::vector<Occurence> &occurences);

            void run();
        private:
            std::unique_ptr<AddressBook> _addressBook;
    };
};

#endif /* !ENGINE_HPP_ */