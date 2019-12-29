//
// Created by Quentin Liardeaux on 12/19/19.
//

#ifndef R_TYPE_GAMEROOM_HPP
#define R_TYPE_GAMEROOM_HPP

#include <memory>
#include <list>
#include <iostream>
#include <thread>
#include <chrono>

#include <boost/shared_ptr.hpp>

#include "Client.hpp"
#include "Bullet.hpp"
#include "Spawner.hpp"

#define MIN_PLAYERS 2
#define MAX_X 3000

class Client;

class GameRoom : public ClientHandler {
public:
    GameRoom(size_t id, std::string name, uint8_t maxPLayers)
            : ClientHandler()
            , m_id(id)
            , m_name(std::move(name))
            , m_maxPlayers(maxPLayers)
            , m_elapsedTime(0) {}
    ~GameRoom() final = default;

    void addPlayer(const boost::shared_ptr<Client> &newClient);
    void addBullet(size_t id, const Position& startPos);
    void removePlayer(size_t idPlayer);

    void stop();

    [[nodiscard]] size_t getId() const { return m_id; }
    [[nodiscard]] const std::string &getName() const { return m_name; }
    [[nodiscard]] size_t getPlayerCount() const { return m_clients.size(); }
    [[nodiscard]] size_t getMaxPlayers() const { return m_maxPlayers; }
    [[nodiscard]] float getElapsedTime() const { return m_elapsedTime; }

private:
    void start();
    void run();
    void updateEntities();
    void checkCollision();
    void sendEntitiesState(Client& client);

    size_t m_id;
    std::string m_name;
    uint8_t m_maxPlayers;
    bool m_isRunning;
    std::thread m_thread;
    std::map<size_t, Bullet*> m_bullets;
    std::list<Spawner> m_spawners;
    float m_elapsedTime;
};

#endif //R_TYPE_GAMEROOM_HPP
