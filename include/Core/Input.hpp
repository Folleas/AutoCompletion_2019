/*
** EPITECH PROJECT, 2020
** SYN_autoCompletion_2019
** File description:
** Input
*/

#ifndef INPUT_HPP_
#define INPUT_HPP_

#include <string>
#include <vector>
#include <iostream>

namespace AutoCompletion {

class Input {
    public:
        Input() = default;
        ~Input() = default;

        char getUserInput();
    protected:
        std::string _buffer;
};

};

#endif /* !INPUT_HPP_ */