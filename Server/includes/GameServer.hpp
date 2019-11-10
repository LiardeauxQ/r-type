//
// Created by alex on 11/10/19.
//

#ifndef CPP_RTYPE_2019_GAMESERVER_HPP
#define CPP_RTYPE_2019_GAMESERVER_HPP

#include "Definitions.hpp"
#include "GameRoom.hpp"
#include "Command.hpp"
#include "Client.hpp"
#include <list>

using namespace std;

class GameServer {
public:
    GameServer(short port, std::string addr);
    ~GameServer();

    void run();
private:
    list<Box<GameRoom>> m_gameRooms;
    list<Rc<Client>> m_clients;
    TcpSocket m_listener;
    short m_port;
    std::string& m_addr;
    bool m_running;
};

#endif //CPP_RTYPE_2019_GAMESERVER_HPP
