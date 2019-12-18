/*
** EPITECH PROJECT, 2019
** LoadState.cpp
** File description:
** LoadState implementation
*/

#include "states/LoadState.hpp"
#include <iostream>

LoadState::LoadState(): State()
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

void LoadState::handleEvent() {}
