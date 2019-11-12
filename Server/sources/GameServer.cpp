//
// Created by alex on 11/10/19.
//

#include "../includes/GameServer.hpp"
#include <iostream>

GameServer::GameServer(uint16_t port)
    : m_gameRooms()
    , m_clients()
    , m_listener(port)
    , m_running(true)
{
}

void processCommand(const Command& cmd) noexcept
{
    std::cout << "Command.id: " << cmd.m_id << std::endl;
}

void GameServer::acceptClients()
{
    TcpStream socket = m_listener.accept();
    cout << "Adding new client." << endl;
    m_clients.push_front(make_shared<Client>(socket));
}

int GameServer::run()
{
    m_listener.listen(100);
    while (m_running) {
        acceptClients();
    }
    return 0;
}
GameServer::~GameServer()
{
}
