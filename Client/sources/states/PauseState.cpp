/*
** EPITECH PROJECT, 2019
** PauseState.cpp
** File description:
** PauseState implementation
*/

#include "states/PauseState.hpp"
#include <iostream>

PauseState::PauseState(): State()
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

void PauseState::onPause() {}

void PauseState::onResume() {}

void PauseState::update() {}

void PauseState::handleEvent() {}
