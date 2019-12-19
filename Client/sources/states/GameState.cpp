/*
** EPITECH PROJECT, 2019
** GameState.cpp
** File description:
** GameState implementation
*/

#include "states/GameState.hpp"
#include <iostream>

GameState::GameState(TextureBuilder &textureBuilder)
    : State(textureBuilder)
{
    this->onStart();
}

GameState::~GameState()
{
    this->onStop();
}

void GameState::onStart()
{
    std::cout << "Entering GameState..." << std::endl;
}

void GameState::onStop()
{
    std::cout << "Leaving GameState..." << std::endl;
}

void GameState::onPause()
{
    m_isPaused = true;
}

void GameState::onResume()
{
    m_isPaused = false;
}

void GameState::update()
{
    if (m_isPaused)
        return;
}

Transition GameState::handleEvent(sf::Event &event)
{
    switch (event.type) {
        case sf::Event::Closed:
            return Transition::QUIT;
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Escape)
                return Transition::QUIT;
            return Transition::NONE;
        default:
            return Transition::NONE;
    }
}
