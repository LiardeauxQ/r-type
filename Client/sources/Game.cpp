/*
** EPITECH PROJECT, 2019
** Game.cpp
** File description:
** Game implementation
*/

#include "Game.hpp"

Game::Game(int ac, char **av)
    : m_input(ac, av)
    , m_dispatcher(nullptr)
    , m_stateBuilder()
    , m_states()
    , m_isRunning(false)
    , m_window(nullptr) {
}

Game::~Game() {
    delete m_dispatcher;
    while (!m_states.empty())
        m_states.pop();
}

void Game::run() {
    if (m_input.isAskingForHelp()) {
        displayHelp();
        return;
    }
    try {
        m_dispatcher = new ClientPacketDispatcher(8678, 0, "0.0.0.0");
        m_dispatcher->run();
        gameConnection();
        m_window = std::make_shared<sf::RenderWindow>(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "test");
        m_states.push(m_stateBuilder.createState(States::GAME));
        m_states.top()->linkWindow(m_window);
        m_isRunning = true;
        //this->loop();
    } catch (const char *s) {
        std::cout << s << std::endl;
    }
}

void Game::gameConnection() {
    auto sessionName = m_input.getSessionName();
    auto password = m_input.getPassword();
    auto nickname = m_input.getNickname();
    std::cout << "connect" << std::endl;
    if (m_input.isCreateSession())
        m_dispatcher->sendCreateGame(sessionName, password, nickname);
    else
        m_dispatcher->sendJoinGame(sessionName, password, nickname);
}

void Game::loop()
{
    while (m_isRunning && m_window->isOpen()) {
        m_window->clear();
        m_states.top()->handleEvent();
        m_states.top()->update();
        m_window->display();
    }
}

void Game::displayHelp() {
    std::cout << "R-TYPE help:" << std::endl;
    std::cout << "\t-c\t --createSession" << std::endl;
    std::cout << "\t-s\t --name $NAME" << std::endl;
    std::cout << "\t-w\t --password $PASSWORD" << std::endl;
    std::cout << "\t-n\t --nickname $NICKNAME" << std::endl;
    std::cout << "\t-p1\t --serverPort $PORT" << std::endl;
    std::cout << "\t-p2\t --clientPort $PORT" << std::endl;
    std::cout << "\t-h\t --help" << std::endl;
}
