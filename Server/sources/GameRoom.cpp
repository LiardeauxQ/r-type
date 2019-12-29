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

void GameRoom::addBullet(size_t id, const Position& startPos) {
    auto it = m_bullets.find(id);
    if (it != m_bullets.end())
        return;
    m_bullets[id] = new Bullet(id, startPos, Position(400, 0));
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
    m_spawners.emplace_back(Position(1500, 250));
    m_spawners.emplace_back(Position(1500, 750));
    m_isRunning = true;
    m_thread = std::thread(&GameRoom::run, this);
}

void GameRoom::run() {
    std::chrono::time_point<std::chrono::system_clock> start;
    std::chrono::time_point<std::chrono::system_clock> end;

    while (m_isRunning) {
        start = std::chrono::system_clock::now();
        updateEntities();
        checkCollision();
        for (auto& client : m_clients)
            sendEntitiesState(*client);
        end = std::chrono::system_clock::now();
        m_elapsedTime = std::chrono::duration<float>(end - start).count();
    }
}

void GameRoom::updateEntities() {
    for (auto& client : m_clients)
        client->update();
    for (auto& spawner : m_spawners)
        spawner.update(m_elapsedTime);
    for (auto it = m_bullets.begin() ; it != m_bullets.end() ;) {
        if (it->second->getPosition().m_x > MAX_X) {
            delete it->second;
            m_bullets.erase(it++);
        } else {
            it->second->update(m_elapsedTime);
            it++;
        }
    }
}

void GameRoom::checkCollision() {
    std::list<std::tuple<size_t, size_t, Position>> collisionsLog;

    for (auto& spawner : m_spawners) {
        /*for (auto client = m_clients.begin() ; client != m_clients.end(); client++) {
            auto collideStatus = spawner.isCollideWith((*client)->getPosition());
            if (std::get<0>(collideStatus)) {
                collisionsLog.emplace_back((*client)->getId(),
                        std::get<1>(collideStatus),
                                (*client)->getPosition());
            }
        }*/
        std::cout << "coll before" << m_bullets.size() << std::endl;
        for (auto bullet = m_bullets.begin() ; bullet != m_bullets.end();) {
            auto collideStatus = spawner.isCollideWith(bullet->second->getPosition());
            if (std::get<0>(collideStatus)) {
                collisionsLog.emplace_back(bullet->second->getId(),
                        std::get<1>(collideStatus), bullet->second->getPosition());
                delete bullet->second;
                m_bullets.erase(bullet++);
            } else {
                bullet++;
            }
        }
        std::cout << "coll after" << m_bullets.size() << std::endl;
    }
    for (auto& collision : collisionsLog) {
        for (auto& client : m_clients) {
            client->triggerCollision(
                    std::get<0>(collision),
                    EntityType::BULLET,
                    std::get<1>(collision),
                    EntityType::ENEMY,
                    std::get<2>(collision));
        }
    }
}

void GameRoom::sendEntitiesState(Client& client) {
    client.sendPlayerState();
    for (auto& other : m_clients)
        if (client.getId() != other->getId())
            client.sendFriendState(other->getId(), other->getPosition(), other->getVelocity());
    for (auto& spawner : m_spawners)
        for (auto& enemy : spawner.getEnemies())
            client.sendEntityState(enemy.second->getId(),
                                   enemy.second->getPosition(),
                                   enemy.second->getVelocity(),
                                   EntityType::ENEMY);
    std::cout << "state before" << m_bullets.size() << std::endl;
    for (auto& bullet : m_bullets)
        client.sendEntityState(bullet.second->getId(),
                               bullet.second->getPosition(),
                               bullet.second->getVelocity(),
                               EntityType::BULLET);
    std::cout << "state after" <<  m_bullets.size() << std::endl;
}

void GameRoom::stop() {
    for (auto& spawner : m_spawners)
        spawner.stop();
    for (auto bullet : m_bullets)
        delete bullet.second;
    m_isRunning = false;
    m_thread.join();
}