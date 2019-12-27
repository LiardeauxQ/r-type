/*
** EPITECH PROJECT, 2019
** MenuState.cpp
** File description:
** MenuState implementation
*/

#include "states/MenuState.hpp"
#include <iostream>

MenuState::MenuState(std::shared_ptr<GameData> gameData)
    : State(gameData)
{
    this->onStart();
}

MenuState::~MenuState()
{
    this->onStop();
}

void MenuState::onStart()
{
    std::cout << "Entering MenuState..." << std::endl;
}

void MenuState::onStop()
{
    std::cout << "Leaving MenuState..." << std::endl;
}

void MenuState::onPause()
{
    m_isPaused = true;
}

void MenuState::onResume()
{
    m_isPaused = false;
}

void MenuState::update()
{
    if (m_isPaused)
        return;
}

Transition MenuState::handleEvent(sf::Event &event)
{
    switch (event.type) {
        case sf::Event::Closed:
            return Transition::QUIT;
        default:
            return Transition::NONE;
    }
}
