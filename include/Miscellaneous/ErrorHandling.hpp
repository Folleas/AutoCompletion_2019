/*
** EPITECH PROJECT, 2020
** SYN_autoCompletion_2019
** File description:
** ErrorHandling
*/

#ifndef ERRORHANDLING_HPP_
#define ERRORHANDLING_HPP_

class ErrorHandling {
    public:
        ErrorHandling(int ac, char **av);
        ~ErrorHandling() = default;

        static void handleArgs(int ac, char **av);
    private:
};

#endif /* !ERRORHANDLING_HPP_ */