//
// Created by alex on 11/10/19.
//

#include "GameServer.hpp"
#include <algorithm>
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
    for_each(m_clients.begin(), m_clients.end(), [](auto &c) { cout << c->m_name << " " << c->m_id << endl; });
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
