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

State *StateBuilder::createState(States stateName, std::shared_ptr<ClientPacketDispatcher> display, TextureBuilder &textureBuilder)
{
    switch (stateName) {
        case States::EMPTY:
            return new EmptyState(display, textureBuilder);
        case States::LOAD:
            return new LoadState(display, textureBuilder);
        case States::MENU:
            return new MenuState(display, textureBuilder);
        case States::PAUSE:
            return new PauseState(display, textureBuilder);
        case States::GAME:
            return new GameState(display, textureBuilder);
        default:
            return new EmptyState(display, textureBuilder);
    }
}
