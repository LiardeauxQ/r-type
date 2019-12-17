/*
** EPITECH PROJECT, 2019
** GameState.cpp
** File description:
** GameState implementation
*/

#include "states/GameState.hpp"

GameState::GameState(): State()
{
    this->onStart();
}

GameState::~GameState()
{
    this->onStop();
}

void GameState::onStart() {}

void GameState::onStop() {}

void GameState::onPause() {}

void GameState::onResume() {}

void GameState::update() {}

void GameState::handleEvent() {}
