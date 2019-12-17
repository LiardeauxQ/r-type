/*
** EPITECH PROJECT, 2019
** StateBuilder.cpp
** File description:
** StateBuilder implementation
*/

#include "StateBuilder.hpp"
#include "states/EmptyState.hpp"
#include "states/LoadState.hpp"
#include "states/MenuState.hpp"
#include "states/PauseState.hpp"
#include "states/GameState.hpp"

StateBuilder::StateBuilder() {}

std::unique_ptr<State> StateBuilder::createState(States stateName)
{
    switch (stateName) {
        case States::EMPTY:
            return std::make_unique<EmptyState>();
        case States::LOAD:
            return std::make_unique<LoadState>();
        case States::MENU:
            return std::make_unique<MenuState>();
        case States::PAUSE:
            return std::make_unique<PauseState>();
        case States::GAME:
            return std::make_unique<GameState>();
        default:
            return std::make_unique<EmptyState>();
    }
}
