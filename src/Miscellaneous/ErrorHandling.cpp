/*
** EPITECH PROJECT, 2020
** SYN_autoCompletion_2019
** File description:
** ErrorHandling
*/

#include "Miscellaneous/ErrorHandling.hpp"
#include "Miscellaneous/Exception.hpp"

ErrorHandling::ErrorHandling(int ac, char **av)
{
    handleArgs(ac, av);
}

void ErrorHandling::handleArgs(int ac, char **av)
{
    if (ac != 2)
        throw MyException("Invalid argument");
}