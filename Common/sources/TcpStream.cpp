//
// Created by alex on 11/10/19.
//

#include "TcpStream.hpp"

TcpStream::TcpStream(RawSocket sock)
    : Socket(TCP, sock)
{}

void TcpStream::connectRaw() {
    socklen_t size = sizeof(sockaddr);

    if (::connect(m_handle, static_cast<sockaddr *>(&m_addr), size) == -1)
        throw "Error cannot connect !";
}

void TcpStream::connect(const string& addr, uint16_t port)
{
    sockaddr_in addrIn = Socket::parseStringAddr(addr);
    addrIn.sin_port = htons(port);
    memcpy(&m_addr, &addrIn, sizeof(sockaddr));

    connectRaw();
}

void TcpStream::connect(const string& addr)
{
    sockaddr_in addrIn = Socket::parseStringAddr(addr);
    memcpy(&m_addr, &addrIn, sizeof(sockaddr));

    connectRaw();
}

void TcpStream::send(const void* data, size_t size) const
{
    if (::send(m_handle, data, size, 0) == -1)
        throw "Error while sending.";
}

template <typename T>
void TcpStream::receive(T& data, size_t size, ssize_t& received) const
{
    received = ::recv(m_handle, &data, size, 0);

    if (received == -1)
        throw "Error while receiving";
}
