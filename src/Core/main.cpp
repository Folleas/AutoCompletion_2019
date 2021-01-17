/*
** EPITECH PROJECT, 2020
** SYN_autoCompletion_2019
** File description:
** main
*/

#include "Core/Engine.hpp"
#include "Core/Input.hpp"
#include "Miscellaneous/ErrorHandling.hpp"

int main(int ac, char **av)
{
    try {
        ErrorHandling error(ac, av);
        AutoCompletion::Engine engine(av[1]);
        engine.run();
    }
    catch (const MyExit &e) {
        return (0);
    }
    catch (const MyException &e) {
        std::cerr << e.what() << std::endl;
        return (84);
    }
    catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return (84);
    }
    return (0);
}