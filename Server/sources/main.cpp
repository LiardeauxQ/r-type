/*
** EPITECH PROJECT, 2019
** main.cpp
** File description:
** Main file.
*/

#include <iostream>
#include "Application.hpp"

int main(int ac, char **av) {
    Application app(ac, av);

    app.run();
    return 0;
}