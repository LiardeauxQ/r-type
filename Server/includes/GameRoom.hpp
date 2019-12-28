//
// Created by Quentin Liardeaux on 12/19/19.
//

#ifndef R_TYPE_GAMEROOM_HPP
#define R_TYPE_GAMEROOM_HPP

#include <memory>
#include <list>
#include <iostream>
#include <thread>

#include <boost/shared_ptr.hpp>

#include "Client.hpp"

#define MIN_PLAYERS 2

class Client;

class GameRoom : public ClientHandler {
public:
    GameRoom(size_t id, std::string name, uint8_t maxPLayers)
            : ClientHandler(), m_id(id), m_name(std::move(name)), m_maxPlayers(maxPLayers) {}
    ~GameRoom() final = default;

    void addPlayer(const boost::shared_ptr<Client> &newClient);

    void removePlayer(size_t idPlayer);

    void run();

    void stop();

    [[nodiscard]] size_t getId() const { return m_id; }

    [[nodiscard]] const std::string &getName() const { return m_name; }

    [[nodiscard]] size_t getPlayerCount() const { return m_clients.size(); }

    [[nodiscard]] size_t getMaxPlayers() const { return m_maxPlayers; }

private:
    size_t m_id;
    std::string m_name;
    uint8_t m_maxPlayers;
    bool m_isRunning;
    std::thread m_thread;
};

#endif //R_TYPE_GAMEROOM_HPP
