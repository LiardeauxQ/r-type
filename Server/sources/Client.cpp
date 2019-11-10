//
// Created by alex on 11/10/19.
//

#include "Client.hpp"
#include "Command.hpp"

Client::Client(TcpSocket socket)
    : m_socket(socket)
    , m_id(socket)
    , m_name()
{
    auto information = Command();
    socket.send();
}
bool Client::operator==(const Client& rhs)
{
    return rhs.m_socket == m_socket;
}
