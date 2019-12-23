/*
** EPITECH PROJECT, 2019
** main.cpp
** File description:
** Main file.
*/

#include "Game.hpp"
#include <iostream>

int main(int ac, char **av) {
    Game game(ac, av);

    game.run();
    return 0;
}
