/*
** EPITECH PROJECT, 2019
** EmptyState.cpp
** File description:
** EmptyState implementation
*/

#include "states/EmptyState.hpp"
#include <iostream>

EmptyState::EmptyState(std::shared_ptr<GameData> gameData)
    : State(gameData)
{
    this->onStart();
}

EmptyState::~EmptyState()
{
    this->onStop();
}

void EmptyState::onStart()
{
    std::cout << "Entering EmptyState..." << std::endl;
}

void EmptyState::onStop()
{
    std::cout << "Leaving EmptyState..." << std::endl;
}

void EmptyState::onPause()
{
    m_isPaused = true;
}

void EmptyState::onResume()
{
    m_isPaused = false;
}

Transition EmptyState::update()
{
    if (m_isPaused)
        return Transition::NONE;
    return Transition::NONE;
}

Transition EmptyState::handleEvent(sf::Event &event)
{
    switch (event.type) {
        case sf::Event::Closed:
            return Transition::QUIT;
        default:
            return Transition::NONE;
    }
}
