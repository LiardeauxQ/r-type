/*
** EPITECH PROJECT, 2019
** LoadState.cpp
** File description:
** LoadState implementation
*/

#include "states/LoadState.hpp"
#include <iostream>

LoadState::LoadState(std::shared_ptr<ClientPacketDispatcher> display, TextureBuilder &textureBuilder)
    : State(std::move(display), textureBuilder)
{
    this->onStart();
}

LoadState::~LoadState()
{
    this->onStop();
}

void LoadState::onStart()
{
    std::cout << "Entering LoadState..." << std::endl;
}

void LoadState::onStop()
{
    std::cout << "Leaving LoadState..." << std::endl;
}

void LoadState::onPause()
{
    m_isPaused = true;
}

void LoadState::onResume()
{
    m_isPaused = false;
}

void LoadState::update()
{
    if (m_isPaused)
        return;
}

Transition LoadState::handleEvent(sf::Event &event)
{
    switch (event.type) {
        case sf::Event::Closed:
            return Transition::QUIT;
        default:
            return Transition::NONE;
    }
}
