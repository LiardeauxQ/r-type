/*
** EPITECH PROJECT, 2019
** GameState.cpp
** File description:
** GameState implementation
*/

#include "states/GameState.hpp"
#include <iostream>

GameState::GameState(): State()
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

void GameState::handleEvent()
{
    while (m_window->pollEvent(m_event)) {
        switch (m_event.type) {
            case sf::Event::Closed:
                m_window->close();
                break;
            case sf::Event::KeyPressed:
                if (m_event.key.code == sf::Keyboard::Escape)
                    m_window->close();
                break;
            default:
                break;
        }
    }
}
