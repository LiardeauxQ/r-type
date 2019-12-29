/*
** EPITECH PROJECT, 2019
** GameState.cpp
** File description:
** GameState implementation
*/

#include "states/GameState.hpp"
#include <iostream>

GameState::GameState(std::shared_ptr<GameData> gameData)
    : State(std::move(gameData))
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

void GameState::onPause()
{
    m_isPaused = true;
}

void GameState::onResume()
{
    m_isPaused = false;
}

Transition GameState::update()
{
    if (m_isPaused)
        return Transition::NONE;
    for (auto &bullet : m_gameData->getBullets()) {
        m_window->draw(*bullet.second);
        bullet.second->update(*m_deltaTime);
    }
    for (auto &enemy : m_gameData->getEnemies()) {
        enemy.second->move(enemy.second->getPosition());
        m_window->draw(*enemy.second);
    }
    for (auto &player : m_gameData->getPlayers()) {
        player.second->move(player.second->getPosition());
        m_window->draw(*player.second);
    }
    return Transition::NONE;
}

Transition GameState::handleEvent(sf::Event &event)
{
    while (m_window->pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                return Transition::QUIT;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape)
                    return Transition::QUIT;
//                if (event.key.code == sf::Keyboard::Num1)
//                    m_players.front()->setShotPatern(ShotPatern::SINGLE);
//                if (event.key.code == sf::Keyboard::Num2)
//                    m_players.front()->setShotPatern(ShotPatern::DOUBLE);
//                if (event.key.code == sf::Keyboard::Num3)
//                    m_players.front()->setShotPatern(ShotPatern::TRIPLE);
                break;
            case sf::Event::Resized:
                m_window->setView(sf::View(sf::FloatRect(0, 0, static_cast<float>(event.size.width), static_cast<float>(event.size.height))));
            default:
                break;
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        m_udpHandler->playerShot();
    sf::Vector2f offset(0.0, 0.0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        offset += sf::Vector2f(0.0, -320 * (*m_deltaTime));
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        offset += sf::Vector2f(-200 * (*m_deltaTime), 0.0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        offset += sf::Vector2f(0.0, 320 * (*m_deltaTime));
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        offset += sf::Vector2f(200 * (*m_deltaTime), 0.0);
    m_udpHandler->playerMove(offset.x, offset.y);
    return Transition::NONE;
}
