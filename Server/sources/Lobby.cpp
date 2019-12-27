//
// Created by Quentin Liardeaux on 12/19/19.
//

#include "Lobby.hpp"

void Lobby::addClient(const boost::shared_ptr<Client>& client) {
    m_clients.push_back(client);
}

size_t Lobby::createGameRoom(std::string name, uint8_t maxPlayers) {
    size_t id = m_maxRoomId;

    m_rooms.push_back(boost::shared_ptr<GameRoom>(new GameRoom(m_maxRoomId, std::move(name), maxPlayers)));
    m_maxRoomId += 1;
    return id;
}

void Lobby::runGameRoom(size_t id) {
    for (auto& room : m_rooms) {
        if (room->getId() == id) {
            room->run();
            break;
        }
    }
}

void Lobby::joinGameRoom(size_t idPlayer, size_t idRoom) {
    for (auto& room : m_rooms) {
        std::cout << "name:" << room->getName() << std::endl;
        for (auto it = m_clients.begin() ; it != m_clients.end() ; it++) {
            if ((*it)->getId() == idPlayer && room->getId() == idRoom) {
                (*it)->setHandler(room);
                room->addPlayer((*it));
                m_clients.erase(it);
                return;
            }
        }
    }
    throw "Cannot find room";
}

void Lobby::quitGameRoom(size_t idPlayer, size_t idRoom) {
    for (auto& room : m_rooms) {
        if (room->getId() == idRoom) {
            room->removePlayer(idPlayer);
            break;
        }
    }
}

size_t Lobby::getRoomId(const std::string &name) const {
    for (auto& room : m_rooms) {
        std::cout << "find " << room->getName() << " - " << name << std::endl;
        if (room->getName() == name)
            return room->getId();
    }
    throw "Unknown room";
}

RoomInfo Lobby::getRoomInfo(const std::string &name, size_t idPlayer) {
    for (auto& room : m_rooms) {
        if (room->getName() == name) {
            return RoomInfo(room->getId(), room->getName(),
                    room->getPlayerCount(), room->getMaxPlayers(), idPlayer);
        }
    }
    throw "Unknown room";
}

