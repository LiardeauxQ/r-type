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

State *StateBuilder::createState(States stateName, EntityBuilder &entityBuilder)
{
    switch (stateName) {
        case States::EMPTY:
            return new EmptyState(entityBuilder);
        case States::LOAD:
            return new LoadState(entityBuilder);
        case States::MENU:
            return new MenuState(entityBuilder);
        case States::PAUSE:
            return new PauseState(entityBuilder);
        case States::GAME:
            return new GameState(entityBuilder);
        default:
            return new EmptyState(entityBuilder);
    }
}
