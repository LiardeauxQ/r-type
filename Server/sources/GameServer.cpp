//
// Created by alex on 11/10/19.
//

#include "../includes/GameServer.hpp"

GameServer::GameServer(short port, std::string addr)
    : m_gameRooms()
    , m_port(port)
    , m_addr(move(addr))
    , m_running(true)
    , m_listener(m_addr, m_port)
{
}

void processCommand(const Command& cmd) noexcept
{

}

void listenToClient() noexcept const
{
    TcpSocket socket = m_listener.listen();
    m_clients.push(make_unique<Client>(socket));
}

void GameServer::run()
{
    Command cmd;

    while (m_running) {
        listenToClient(cmd);
        processCommand(cmd);
    }
}
