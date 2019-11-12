//
// Created by alex on 11/10/19.
//

#include "Client.hpp"
#include "Command.hpp"

Client::Client(const TcpStream& socket)
    : m_socket(socket)
    , m_id()
    , m_name()
{
}

bool Client::operator==(const Client& rhs) const
{
    return rhs.m_socket == m_socket;
}
