/*
** EPITECH PROJECT, 2019
** EmptyState.cpp
** File description:
** EmptyState implementation
*/

#include "states/EmptyState.hpp"
#include <iostream>

EmptyState::EmptyState(): State()
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

void EmptyState::onPause() {}

void EmptyState::onResume() {}

void EmptyState::update() {}

void EmptyState::handleEvent() {}
