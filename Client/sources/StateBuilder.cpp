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

State *StateBuilder::createState(States stateName, TextureBuilder &textureBuilder)
{
    switch (stateName) {
        case States::EMPTY:
            return new EmptyState(textureBuilder);
        case States::LOAD:
            return new LoadState(textureBuilder);
        case States::MENU:
            return new MenuState(textureBuilder);
        case States::PAUSE:
            return new PauseState(textureBuilder);
        case States::GAME:
            return new GameState(textureBuilder);
        default:
            return new EmptyState(textureBuilder);
    }
}
