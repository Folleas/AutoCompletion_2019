/*
** EPITECH PROJECT, 2020
** SYN_autoCompletion_2019
** File description:
** Input
*/

#include "Core/Input.hpp"
#include "Miscellaneous/Exception.hpp"

namespace AutoCompletion {

char Input::getUserInput()
{
    std::string str;

    if (this->_buffer.empty())
        std::cin >> str;
    if (std::cin.eof() || str == "ABORT") {
        throw MyExit("toto");
    }
    this->_buffer.append(str);
    char tmp = this->_buffer.at(0);
    this->_buffer.erase(this->_buffer.begin());
    return tmp;
}

};