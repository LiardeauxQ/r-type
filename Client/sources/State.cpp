/*
** EPITECH PROJECT, 2019
** State.cpp
** File description:
** State implementation
*/

#include "State.hpp"

State::State() {}
State::~State() {}

EmptyState::EmptyState(): State() {}
EmptyState::~EmptyState() {}
void EmptyState::onStart() {}
void EmptyState::onStop() {}
void EmptyState::onPause() {}
void EmptyState::onResume() {}
void EmptyState::update() {}
void EmptyState::handleEvent() {}

LoadState::LoadState(): State() {}
LoadState::~LoadState() {}
void LoadState::onStart() {}
void LoadState::onStop() {}
void LoadState::onPause() {}
void LoadState::onResume() {}
void LoadState::update() {}
void LoadState::handleEvent() {}

MenuState::MenuState(): State() {}
MenuState::~MenuState() {}
void MenuState::onStart() {}
void MenuState::onStop() {}
void MenuState::onPause() {}
void MenuState::onResume() {}
void MenuState::update() {}
void MenuState::handleEvent() {}

PauseState::PauseState(): State() {}
PauseState::~PauseState() {}
void PauseState::onStart() {}
void PauseState::onStop() {}
void PauseState::onPause() {}
void PauseState::onResume() {}
void PauseState::update() {}
void PauseState::handleEvent() {}

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
