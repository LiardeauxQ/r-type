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

State *StateBuilder::createState(States stateName, std::shared_ptr<GameData> gameData)
{
    switch (stateName) {
        case States::EMPTY:
            return new EmptyState(gameData);
        case States::LOAD:
            return new LoadState(gameData);
        case States::MENU:
            return new MenuState(gameData);
        case States::PAUSE:
            return new PauseState(gameData);
        case States::GAME:
            return new GameState(gameData);
        default:
            return new EmptyState(gameData);
    }
}
