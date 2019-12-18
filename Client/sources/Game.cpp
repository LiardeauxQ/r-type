/*
** EPITECH PROJECT, 2019
** Game.cpp
** File description:
** Game implementation
*/

#include "Game.hpp"
#include <iostream>

Game::Game()
    : m_stateBuilder()
    , m_states()
    , m_isRunning(false)
{
    m_states.push(m_stateBuilder.createState(States::EMPTY));
}

Game::~Game()
{
    while (!m_states.empty())
        m_states.pop();
}

void Game::run()
{
    m_isRunning = true;
    m_states.push(m_stateBuilder.createState(States::GAME));
    this->loop();
}

void Game::loop()
{
    while (m_isRunning) {
        m_states.top()->handleEvent();
        m_states.top()->update();
    }
}
