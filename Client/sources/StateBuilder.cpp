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
            return new EmptyState(std::move(display), textureBuilder);
        case States::LOAD:
            return new LoadState(std::move(display), textureBuilder);
        case States::MENU:
            return new MenuState(std::move(display), textureBuilder);
        case States::PAUSE:
            return new PauseState(std::move(display), textureBuilder);
        case States::GAME:
            return new GameState(std::move(display), textureBuilder);
        default:
            return new EmptyState(std::move(display), textureBuilder);
    }
}
