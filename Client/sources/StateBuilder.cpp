/*
** EPITECH PROJECT, 2019
** StateBuilder.cpp
** File description:
** StateBuilder implementation
*/

#include "StateBuilder.hpp"

StateBuilder::StateBuilder() {}

State *StateBuilder::createState(States stateName)
{
    switch (stateName) {
        case States::EMPTY:
            return new EmptyState();
        case States::LOAD:
            return new LoadState();
        case States::MENU:
            return new MenuState();
        case States::PAUSE:
            return new PauseState();
        case States::GAME:
            return new GameState();
        default:
            return new EmptyState();
    }
}
