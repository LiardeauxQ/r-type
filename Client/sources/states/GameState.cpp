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

void GameState::onPause() {}

void GameState::onResume() {}

void GameState::update() {}

void GameState::handleEvent() {}
