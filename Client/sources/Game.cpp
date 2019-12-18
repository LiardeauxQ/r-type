//
// Created by Quentin Liardeaux on 12/17/19.
//

#include "Game.hpp"

Game::Game(int ac, char **av)
    : m_input(ac, av)
    , m_dispatcher(nullptr) {
}

Game::~Game() {
    delete m_dispatcher;
}

void Game::run() {
    if (m_input.isAskingForHelp()) {
        displayHelp();
        return;
    }
    try {
        m_dispatcher = new ClientPacketDispatcher(8678, "0.0.0.0");
        m_dispatcher->run();
        gameConnection();
    } catch (const char *s) {
        std::cout << s << std::endl;
    }
}

void Game::gameConnection() {
    std::cout << "connect" << std::endl;
    if (m_input.isCreateSession()) {
        std::cout << "Create session" << std::endl;
        m_dispatcher->sendCreateGame(m_input.getSessionName(),
                                     m_input.getPassword(), m_input.getNickname());
    } else {
        m_dispatcher->sendJoinGame(m_input.getSessionName(),
                                   m_input.getPassword(), m_input.getNickname());
    }
}

void Game::displayHelp() {
    std::cout << "R-TYPE help:" << std::endl;
    std::cout << "\t-c\t --createSession" << std::endl;
    std::cout << "\t-s\t --name $NAME" << std::endl;
    std::cout << "\t-w\t --password $PASSWORD" << std::endl;
    std::cout << "\t-n\t --nickname $NICKNAME" << std::endl;
    std::cout << "\t-p\t --port $PORT" << std::endl;
    std::cout << "\t-h\t --help" << std::endl;
}
