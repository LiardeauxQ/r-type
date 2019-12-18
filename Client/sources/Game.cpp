//
// Created by Quentin Liardeaux on 12/17/19.
//

#include "Game.hpp"

Game::Game(int ac, char **av)
    : m_input(ac, av) {
    m_dispatcher = PacketDispatcher(m_input.getPort(), "0.0.0.0");
}

void Game::run() {
    m_dispatcher->run();
    try {
        gameConnection();
    } catch (std::exception &e) {
        std::cout << "Error" << std::endl;
    }
}

void Game::gameConnection() {
    if (m_input.isCreateSession()) {
        m_dispatcher->sendCreateGame(m_input.getSessionName(),
                                     m_input.getPassword(), m_input.getNickname());
    } else {
        m_dispatcher->sendJoinGame(m_input.getSessionName(),
                                   m_input.getPassword(), m_input.getNickname());
    }
}
