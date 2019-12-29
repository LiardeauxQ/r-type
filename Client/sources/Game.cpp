/*
** EPITECH PROJECT, 2019
** Game.cpp
** File description:
** Game implementation
*/

#include <iostream>
#include <SFML/System/Clock.hpp>
#include "Game.hpp"

Game::Game(int ac, char **av)
    : m_input(ac, av)
    , m_tcpHandler()
    , m_gameData(GameData::from(m_input))
    , m_entityBuilder()
    , m_stateBuilder()
    , m_states()
    , m_isRunning(false)
    , m_window(nullptr)
    , m_event()
    , m_deltaTime(0.0)
{
}

Game::~Game()
{
    if (m_tcpHandler != nullptr)
        m_tcpHandler->stop();
    while (!m_states.empty()) {
        delete m_states.top();
    }
}

void Game::run()
{
    if (m_input.isAskingForHelp() || m_gameData == nullptr) {
        Game::displayHelp();
        return;
    }
    try {
        m_tcpHandler = TcpCommunication::create(m_gameData);
        m_udpHandler = UdpCommunication::create(m_gameData);
        m_tcpHandler->start();
        m_tcpHandler->askServerConnection(m_input.isCreateSession());
        m_window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_NAME);
        m_window->setVerticalSyncEnabled( true );
        m_states.push(m_stateBuilder.createState(States::GAME, m_gameData));
        m_states.top()->linkToGame(m_udpHandler, m_window, &m_deltaTime);
        m_isRunning = true;
        this->loop();
    } catch (std::logic_error& error) {
        std::cout << error.what() << std::endl;
    }
}

void Game::handleTransition(Transition transition)
{
    switch (transition) {
        case Transition::QUIT:
            m_tcpHandler->stop();
            m_udpHandler->stop();
            m_window->close();
            break;
        default:
            break;
    }
}

void Game::loop()
{
    sf::Clock clock;
    while (m_isRunning && m_window->isOpen()) {
        m_window->clear();
        m_deltaTime = clock.getElapsedTime().asSeconds();
        clock.restart();
        m_tcpHandler->update();
        checkGameStatus();
        m_udpHandler->update();
        handleTransition(m_states.top()->handleEvent(m_event));
        if (m_window->isOpen()) {
            handleTransition(m_states.top()->update());
            m_window->display();
        }
    }
}

void Game::checkGameStatus() {
    if (m_gameData->m_gameRunning)
        m_udpHandler->start();
}

void Game::displayHelp()
{
    std::cout << "R-TYPE help:" << std::endl;
    std::cout << "\t-c\t --create-session" << std::endl;
    std::cout << "\t-s\t --name $NAME" << std::endl;
    std::cout << "\t-w\t --password $PASSWORD" << std::endl;
    std::cout << "\t-n\t --nickname $NICKNAME" << std::endl;
    std::cout << "\t-p1\t --server-port $PORT" << std::endl;
    std::cout << "\t-p2\t --client-port $PORT" << std::endl;
    std::cout << "\t-l\t --local-address $ADDRESS" << std::endl;
    std::cout << "\t-r\t --remote-address $ADDRESS" << std::endl;
    std::cout << "\t-h\t --help" << std::endl;
}
