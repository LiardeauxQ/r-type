//
// Created by Quentin Liardeaux on 12/19/19.
//

#ifndef R_TYPE_LOBBY_HPP
#define R_TYPE_LOBBY_HPP

#include <memory>
#include <list>
#include <string>

#include <boost/shared_ptr.hpp>

#include "Client.hpp"

#include "Protocol/RoomInfo.hpp"

class Client;
class GameRoom;

class Lobby : public ClientHandler {
public:
    Lobby() = default;
    ~Lobby() final = default;

    void addClient(const boost::shared_ptr<Client> &client);

    size_t createGameRoom(std::string name, uint8_t maxPlayers);

    void runGameRoom(size_t id);

    void joinGameRoom(uint16_t idPlayer, size_t idRoom);

    void quitGameRoom(uint16_t idPlayer, size_t idRoom);

    size_t getRoomId(const std::string &name) const;
    RoomInfo getRoomInfo(const std::string &name, uint16_t idPlayer);

private:
    std::list<boost::shared_ptr<GameRoom>> m_rooms;
    size_t m_maxClientId;
    size_t m_maxRoomId;
};

#endif //R_TYPE_LOBBY_HPP
