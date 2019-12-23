//
// Created by Quentin Liardeaux on 12/19/19.
//

#include "GameRoom.hpp"

void GameRoom::addPlayer(const boost::shared_ptr<Client>& player) {
    m_clients.push_back(player);
}

void GameRoom::removePlayer(uint16_t idPlayer) {
    for (auto it = m_clients.begin() ; it != m_clients.end() ; it++) {
        if ((*it)->getId() == idPlayer) {
            m_clients.erase(it);
            break;
        }
    }
}

void GameRoom::run() {
    while (m_isRunning) {
        std::cout << "GameRoom " << m_id << " Running" << std::endl;
    }
}

void GameRoom::stop() {
    m_isRunning = false;
}