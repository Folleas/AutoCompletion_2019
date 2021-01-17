/*
** EPITECH PROJECT, 2020
** SYN_autoCompletion_2019
** File description:
** Parser
*/

#include "Miscellaneous/Parser.hpp"

using namespace std::string_literals;

namespace AutoCompletion {

Parser::~Parser()
{

}

std::vector<std::shared_ptr<Address>> Parser::run(void)
{
    std::string buffer;
    std::regex address_regex("^([\\w\\s]*), ([\\d]+) (quai|rue|place|square|allée|impasse|rue|chemin|boulevard|avenue) ([\\w(\\s|’)àâçéèêëîïôûùüÿñæœ'-]+)$");
    std::smatch matches;

    while (getline(*(_fileStream.get()), buffer)) {
        if (regex_search(buffer, matches, address_regex)) {
            std::shared_ptr<Address> address = std::make_shared<Address>();
            address->setAddress(matches[1].str(), matches[2].str(), matches[3].str(), matches[4].str());
            _addresses.push_back(address);
        }
        else {
            std::cerr << buffer << std::endl;
        }
    }
    return (_addresses);
}

void Parser::findFileStream(const std::string &filePath)
{
    this->_fileStream = std::make_unique<std::ifstream>(filePath);
    if (this->_fileStream == nullptr || _fileStream->fail() || _fileStream->bad() || Utils::isEmpty(*_fileStream.get())) {
        throw MyException("Invalid argument");
    }
}

bool Parser::isValidAddress(const std::string& address) const
{
    return (false);
};

};