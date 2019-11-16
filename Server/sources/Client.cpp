//
// Created by alex on 11/10/19.
//

#include "Client.hpp"

Client::Client(const TcpStream& socket)
    : m_name()
    , m_id()
    , m_socket(socket)
{
    uint8_t name[256];
    ssize_t receivedSize = 0;

    socket.receive<uint8_t>(name, 256, receivedSize);
    m_name = reinterpret_cast<const char*>(name);
    MD5(name, 256, m_id);
}

bool Client::operator==(const Client& rhs) const
{
    return rhs.m_socket == m_socket;
}
