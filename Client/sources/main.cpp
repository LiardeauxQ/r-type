/*
** EPITECH PROJECT, 2019
** main.cpp
** File description:
** Main file.
*/

#include <iostream>

#ifndef VERSION
    #define VERSION "NOT DEFINED"
#endif

#include "StateMachine.hpp"
#include "MainMenuState.hpp"

int main(void) {
    StateMachine states(unique_ptr<AbstractState>(new MainMenuState()));

    states.run();
    return 0;
}
