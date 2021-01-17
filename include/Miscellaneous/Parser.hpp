/*
** EPITECH PROJECT, 2020
** SYN_autoCompletion_2019
** File description:
** Parser
*/

#ifndef PARSER_HPP_
#define PARSER_HPP_

#include <vector>
#include <regex>
#include <iostream>
#include <fstream>
#include <memory>

#include "Core/Address.hpp"

namespace AutoCompletion {
    class Parser {
        public:
            Parser() = default;
            ~Parser();

            std::vector<std::shared_ptr<Address>> run(void);
            bool isValidAddress(const std::string &str) const;

            void findFileStream(const std::string &filePath);
        protected:
            std::unique_ptr<std::ifstream> _fileStream;
            std::vector<std::shared_ptr<Address>> _addresses;
    };
}

#endif /* !PARSER_HPP_ */
