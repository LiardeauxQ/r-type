/*
** EPITECH PROJECT, 2019
** PauseState.cpp
** File description:
** PauseState implementation
*/

#include "states/PauseState.hpp"
#include <iostream>

PauseState::PauseState(std::shared_ptr<GameData> gameData)
    : State(gameData)
{
    this->onStart();
}

PauseState::~PauseState()
{
    this->onStop();
}

void PauseState::onStart()
{
    std::cout << "Entering PauseState..." << std::endl;
}

void PauseState::onStop()
{
    std::cout << "Leaving PauseState..." << std::endl;
}

void PauseState::onPause()
{
    m_isPaused = true;
}

void PauseState::onResume()
{
    m_isPaused = false;
}

void PauseState::update()
{
    if (m_isPaused)
        return;
}

Transition PauseState::handleEvent(sf::Event &event)
{
    switch (event.type) {
        case sf::Event::Closed:
            return Transition::QUIT;
        default:
            return Transition::NONE;
    }
}
