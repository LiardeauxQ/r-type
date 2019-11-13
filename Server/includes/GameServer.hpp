//
// Created by alex on 11/10/19.
//

#ifndef CPP_RTYPE_2019_GAMESERVER_HPP
#define CPP_RTYPE_2019_GAMESERVER_HPP

#include "Definitions.hpp"
#include "GameRoom.hpp"
#include "Command.hpp"
#include "MessageFactory.hpp"
#include "Client.hpp"
#include "TcpListener.hpp"
#include "TcpStream.hpp"
#include <list>

using namespace std;

class GameServer {
public:
    explicit GameServer(uint16_t port);
    ~GameServer();

    int run();
    void acceptClients();
private:
    list<Box<GameRoom>> m_gameRooms;
    list<Rc<Client>> m_clients;
    TcpListener m_listener;
    bool m_running;
};

#endif //CPP_RTYPE_2019_GAMESERVER_HPP
