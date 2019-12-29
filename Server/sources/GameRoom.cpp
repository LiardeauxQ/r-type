//
// Created by Quentin Liardeaux on 12/19/19.
//

#include "GameRoom.hpp"

void GameRoom::addPlayer(const boost::shared_ptr<Client>& newClient) {
    for (auto& client : m_clients) {
        client->sendPlayerJoinGame(newClient->getId(), newClient->getNickname());
        newClient->sendPlayerJoinGame(client->getId(), client->getNickname());
    }
    m_clients.push_back(newClient);
    if (m_clients.size() == MIN_PLAYERS)
        start();
}

void GameRoom::removePlayer(size_t idPlayer) {
    for (auto it = m_clients.begin() ; it != m_clients.end() ; it++) {
        if ((*it)->getId() == idPlayer) {
            m_clients.erase(it);
            break;
        }
    }
    for (auto& client : m_clients)
        client->sendPlayerQuitGame(idPlayer);
}

void GameRoom::start() {
    for (auto& client : m_clients)
        client->startGame();
    m_spawners.emplace_back(Position(1000, 250));
    m_spawners.emplace_back(Position(1000, 750));
    m_isRunning = true;
    m_thread = std::thread(&GameRoom::run, this);
}

void GameRoom::run() {
    while (m_isRunning) {
        updateEntities();
        for (auto& client : m_clients)
            sendEntitiesState(*client);
    }
}

void GameRoom::updateEntities() {
    for (auto& client : m_clients)
        client->update();
    for (auto& spawner : m_spawners) {
        spawner.update();
    }
}

void GameRoom::sendEntitiesState(Client& client) {
    client.sendPlayerState();
    for (auto& other : m_clients) {
        if (client.getId() != other->getId())
            client.sendFriendState(other->getId(), other->getPosition(), other->getVelocity());
    }
    for (auto& spawner : m_spawners) {
        for (auto& enemy : spawner.getEnemies()) {
            client.sendEntityState(enemy.second->getId(),
                                   enemy.second->getPosition(),
                                   enemy.second->getVelocity(),
                                   EntityType::ENEMY);
        }
    }
}

void GameRoom::stop() {
    for (auto& spawner : m_spawners)
        spawner.stop();
    m_isRunning = false;
    m_thread.join();
}