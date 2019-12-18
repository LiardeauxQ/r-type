/*
** EPITECH PROJECT, 2019
** MenuState.cpp
** File description:
** MenuState implementation
*/

#include "states/MenuState.hpp"
#include <iostream>

MenuState::MenuState(): State()
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

void MenuState::handleEvent() {}
