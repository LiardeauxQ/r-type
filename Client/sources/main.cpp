/*
** EPITECH PROJECT, 2019
** main.cpp
** File description:
** Main file.
*/

#ifndef VERSION
#define VERSION "NOT DEFINED"
#endif

#include <iostream>

#include "Game.hpp"

int main(int ac, char **av) {
    Game game(ac, av);

    game.run();
    return 0;
}