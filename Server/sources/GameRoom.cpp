//
// Created by Quentin Liardeaux on 12/19/19.
//

#include "GameRoom.hpp"

void GameRoom::addPlayer(const boost::shared_ptr<Client>& newClient) {
    for (auto& client : m_clients) {
        client->sendPlayerJoinGame(newClient->getId(), newClient->getNickname());
    }
    m_clients.push_back(newClient);
    if (m_clients.size() == MIN_PLAYERS) {
        for (auto& client : m_clients)
            client->startGame();
    }
        //m_clients->startGame();
}

void GameRoom::removePlayer(uint16_t idPlayer) {
    for (auto it = m_clients.begin() ; it != m_clients.end() ; it++) {
        if ((*it)->getId() == idPlayer) {
            m_clients.erase(it);
            break;
        }
    }
    for (auto& client : m_clients)
        client->sendPlayerQuitGame(idPlayer);
}

void GameRoom::run() {
    while (m_isRunning) {
        std::cout << "GameRoom " << m_id << " Running" << std::endl;
    }
}

void GameRoom::stop() {
    m_isRunning = false;
}