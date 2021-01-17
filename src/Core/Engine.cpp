/*
** EPITECH PROJECT, 2020
** SYN_autoCompletion_2019
** File description:
** Engine
*/

#include "Core/Engine.hpp"

AutoCompletion::Engine::Engine(const std::string &path)
{
    Parser parser;

    parser.findFileStream(path);
    _addressBook = std::make_unique<AddressBook>(parser.run());
}

AutoCompletion::Engine::~Engine()
{
}

void AutoCompletion::Engine::run()
{
    std::shared_ptr<Address> searchedAddress = std::make_shared<Address>();
    std::size_t nbValidatedLetters = 0;
    std::string validatedLetters;
    bool addressFound = false;
    bool cityFound = false;
    bool elemFound = false;

    std::vector<Occurence> tmp = _addressBook->getCityOccurences(validatedLetters, nbValidatedLetters);
    printMostProbableCityChoice(validatedLetters, tmp);
    while (!addressFound) {
        char input = this->getUserInput();
        for (Occurence elem : tmp) {
            if (std::toupper(elem.letter) == std::toupper(input)) {
                validatedLetters.push_back(std::toupper(elem.letter));
                nbValidatedLetters++;
                elemFound = true;
            }
        }
        if (!elemFound)
            throw MyException("");
        else
            elemFound = false;
        if (!cityFound) {
            tmp = _addressBook->getCityOccurences(validatedLetters, nbValidatedLetters);
            if (checkOccurences(tmp)) {
                searchedAddress->setCity(tmp.at(0).city);
                searchedAddress->setCityAssociated(tmp.at(0).associatedCity);
                cityFound = true;
                validatedLetters.clear();
                nbValidatedLetters = 0;
                std::vector<std::shared_ptr<Address>> found = manageCityChoices(searchedAddress);
                if (!found.empty() && found.size() != 1) {
                    char input;
                    std::cin >> input;
                    for (std::size_t i = 0; i != found.size(); i++) {
                        if (i + 1 == static_cast<char>(input - '0'))
                            searchedAddress->setCity(found.at(i)->getCity());
                    }
                }
            }
            else {
                printMostProbableCityChoice(validatedLetters, tmp);
            }
        }
        if (cityFound) {
            tmp = _addressBook->getStreetNameOccurences(searchedAddress->getCity(), validatedLetters, nbValidatedLetters);
            if (checkOccurences(tmp)) {
                searchedAddress->setStreetName(tmp.at(0).city);
                searchedAddress->setStreetNameAssociated(tmp.at(0).associatedStreet);
                addressFound = true;
                continue;
            }
            printMostProbableStreetChoice(searchedAddress->getCity(), validatedLetters, tmp);
        }
    }
    std::vector<std::shared_ptr<Address>> found = manageStreetChoices(searchedAddress);
    if (!found.empty() && found.size() != 1) {
        char input;
        std::cin >> input;
        for (std::size_t i = 0; i != found.size(); i++) {
            if (i + 1 == static_cast<char>(input - '0'))
                found.at(i)->print();
        }
    }
    else {
        found.at(0)->print();
    }
}

std::vector<std::shared_ptr<AutoCompletion::Address>> AutoCompletion::Engine::manageCityChoices(std::shared_ptr<Address> searchedAddress)
{
    std::vector<std::shared_ptr<Address>> find = this->_addressBook->searchAddressCity(searchedAddress);
    if (!find.empty() && find.size() == 1) {
        return find;
    }
    std::string tmp = find.at(0)->getCity();
    bool check = false;
    for (std::shared_ptr<Address> elem : find) {
        if (!Utils::isSameWord(elem->getCity(), tmp))
            check = true;
    }
    if (!check) {
        std::shared_ptr<Address> tmp = find.at(0);
        find.clear();
        find.push_back(tmp);
        return find;
    }
    sortAddressVector(find);
    for (std::size_t i = 0; i != find.size(); i++) {
        std::string foundCityElem;
        std::size_t parsCity = 0;
        std::vector<std::string> cityVector = find.at(i)->getCityVector();
        for (std::string elem : cityVector) {
            if (Utils::isSameWord(elem, searchedAddress->getCityAssociated())) {
                foundCityElem = elem;
                for (auto & c: foundCityElem) c = toupper(c);
                break;
            }
            parsCity++;
        }
        std::cout << "{" << i + 1 << " : ";
        for (std::size_t y = 0; y != cityVector.size(); y++) {
            if (y == parsCity)
                std::cout << foundCityElem;
            else
                std::cout << find.at(i)->getCityVector().at(y);
            if (y != cityVector.size() - 1)
                std::cout << " ";
        }
        std::cout << "}";
        if (i < find.size() - 1)
            std::cout << " ";
    }
    std::cout << std::endl;
    return (find);
}

std::vector<std::shared_ptr<AutoCompletion::Address>> AutoCompletion::Engine::manageStreetChoices(std::shared_ptr<Address> searchedAddress)
{
    std::vector<std::shared_ptr<Address>> find = this->_addressBook->searchAddressStreet(searchedAddress);
    if (!find.empty() && find.size() == 1) {
        return find;
    }
    sortAddressVector(find);
    for (std::size_t i = 0; i != find.size(); i++) {
        std::string foundCityElem;
        std::string foundStreetElem;
        std::size_t parsStreet = 0;
        std::size_t parsCity = 0;
        std::vector<std::string> cityVector = find.at(i)->getCityVector();
        std::vector<std::string> streetVector = find.at(i)->getStreetNameVector();
        for (std::string elem : cityVector) {
            if (Utils::isSameWord(elem, searchedAddress->getCity())) {
                foundCityElem = elem;
                foundCityElem = Utils::upper(foundCityElem);
                break;
            }
            parsCity++;
        }
        for (std::string elem : streetVector) {
            if (Utils::isSameWord(elem, searchedAddress->getStreetNameAssociated())) {
                foundStreetElem = elem;
                foundStreetElem = Utils::upper(foundStreetElem);
                break;
            }
            parsStreet++;
        }
        std::cout << "{" << i + 1 << " : ";
        for (std::size_t y = 0; y != cityVector.size(); y++) {
            if (y == parsCity)
                std::cout << foundCityElem;
            else
                std::cout << find.at(i)->getCityVector().at(y);
            if (y != cityVector.size() - 1)
                std::cout << " ";
        }
        std::cout << ", " << find.at(i)->getNumber() << " " << find.at(i)->getStreetType() << " ";
        std::size_t o = 0;
        for (std::size_t y = 0; y != streetVector.size(); y++) {
            if (y == parsStreet) {
                std::cout << foundStreetElem;
                o += foundStreetElem.size();
            }
            else {
                std::string str(find.at(i)->getStreetNameVector().at(y));
                std::cout << str;
                o += str.size();
            }
            if (o + y < find.at(i)->getStreetName().size() && find.at(i)->getStreetName().at(o + y) == '-')
                std::cout << "-";
            else if (y != streetVector.size() - 1)
                std::cout << " ";
        }
        std::cout << "}";
        if (i < find.size() - 1)
            std::cout << " ";
    }
    std::cout << std::endl;
    return (find);
}

void AutoCompletion::Engine::sortAddressVector(std::vector<std::shared_ptr<Address>> &addresses)
{
    bool isSorted = false;

    while (!isSorted) {
        isSorted = true;
        for (std::size_t i = 0; i != addresses.size() - 1; i++) {
            if (addresses.at(i)->getCity() != addresses.at(i + 1)->getCity()) {
                if (!Utils::isSorted(addresses.at(i)->getCity(), addresses.at(i + 1)->getCity())) {
                    std::iter_swap(addresses.begin() + i, addresses.begin() + i + 1);
                    isSorted = true;
                    break;
                }
            }
            else {
                if (addresses.at(i)->getNumber() != addresses.at(i + 1)->getNumber()) {
                    if (addresses.at(i)->getNumber() > addresses.at(i + 1)->getNumber()) {
                        std::iter_swap(addresses.begin() + i, addresses.begin() + i + 1);
                        isSorted = true;
                        break;
                    }
                }
                else {
                    if (addresses.at(i)->getStreetType() != addresses.at(i + 1)->getStreetType()) {
                        if (!Utils::isSorted(addresses.at(i)->getStreetType(), addresses.at(i + 1)->getStreetType())) {
                            std::iter_swap(addresses.begin() + i, addresses.begin() + i + 1);
                            isSorted = true;
                            break;
                        }
                    }
                    else {
                        if (addresses.at(i)->getStreetName() != addresses.at(i + 1)->getStreetName()) {
                            if (!Utils::isSorted(addresses.at(i)->getStreetName(), addresses.at(i + 1)->getStreetName())) {
                                std::iter_swap(addresses.begin() + i, addresses.begin() + i + 1);
                                isSorted = true;
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
}

bool AutoCompletion::Engine::checkOccurences(std::vector<Occurence> tmp)
{
    if (tmp.size() == 1)
        return true;
    if (!tmp.empty()) {
        std::string city = tmp.at(0).city;
        for (Occurence elem : tmp) {
            if (city != elem.city)
                return false;
        }
        return true;
    }
    return false;
}

std::pair<std::size_t, std::size_t> AutoCompletion::Engine::findHighestOccurence(std::vector<Occurence> &occurences)
{
    std::pair<std::size_t, std::size_t> ret = {0, 0};

    for (std::size_t i = 0; i != occurences.size(); i++) {
        if (occurences.at(i).count > ret.second) {
            ret.second = occurences.at(i).count;
            ret.first = i;
        }
    }
    return ret;
}

bool AutoCompletion::Engine::isSorted(std::vector<Occurence> &occurences)
{
    std::size_t tmp = 0;

    for (std::size_t i = 0; i != occurences.size() - 1; i++) {
        if (occurences.at(i).count < occurences.at(i + 1).count)
            return false;
    }
    return true;
}

std::vector<AutoCompletion::Occurence> AutoCompletion::Engine::sortOccurences(std::vector<Occurence> occurences)
{
    std::vector<Occurence> tmp;

    while (!occurences.empty()) {
        std::size_t highest = findHighestOccurence(occurences).first;
        tmp.push_back(occurences.at(highest));
        occurences.erase(occurences.begin() + highest);
    }
    for (std::size_t i = 0; i != tmp.size(); i++) {
        for (std::size_t j = i + 1; j != tmp.size(); j++) {
            if (tmp.at(j).count == tmp.at(i).count && tmp.at(j).letter < tmp.at(i).letter) {
                Occurence temp = tmp.at(j);
                tmp.erase(tmp.begin() + j);
                tmp.insert(tmp.begin() + i, temp);
            }
        }
    }
    return tmp;
}

void AutoCompletion::Engine::printMostProbableCityChoice(std::string validatedLetters, std::vector<Occurence> occurences)
{
    std::size_t tmp = 0;
    std::vector<Occurence> sortedOccurences = sortOccurences(occurences);

    for (std::size_t i = 0; i < 5 && i < sortedOccurences.size(); i++) {
        std::cout << "{" << validatedLetters << static_cast<char>(std::tolower(sortedOccurences.at(i).letter)) << "}";
        if (i < sortedOccurences.size() - 1 && i < 4)
            std::cout << " ";
    }
    std::cout << std::endl;
}

void AutoCompletion::Engine::printMostProbableStreetChoice(std::string validatedCity, std::string validatedLetters, std::vector<Occurence> occurences)
{
    std::size_t tmp = 0;
    std::vector<Occurence> sortedOccurences = sortOccurences(occurences);

    for (std::size_t i = 0; i < 5 && i < sortedOccurences.size(); i++) {
        std::cout << "{" << validatedCity << ", " << validatedLetters << static_cast<char>(std::tolower(sortedOccurences.at(i).letter)) << "}";
        if (i < sortedOccurences.size() - 1 && i < 4)
            std::cout << " ";
    }
    std::cout << std::endl;
}