//
// Created by alex on 11/10/19.
//

#include "Socket.hpp"

Socket::Socket(Socket::Type type, RawSocket handle)
    : m_handle(handle)
    , m_type(type)
    , m_addr{}
{}

Socket::Socket(Socket::Type type, const string& addr)
    : m_handle(-1)
    , m_type(type)
    , m_addr()
{
    sockaddr_in in = parseStringAddr(addr);
    memcpy(&m_addr, &in, sizeof(in));
}

Socket::~Socket()
{
    close(m_handle);
}

bool Socket::operator==(const Socket& socket)
{
    return m_handle == socket.m_handle;
}

Socket::Type Socket::getTypeFromUnix(int32_t type)
{
    switch (type) {
    case SOCK_DGRAM:
        return UDP;
    case SOCK_STREAM:
        return TCP;
    default:
        return RAW;
    }
}

Socket::Socket(int32_t domain, int32_t type, int32_t protocol)
    : m_handle(socket(domain, type, protocol))
    , m_type(getTypeFromUnix(type))
{
    if (m_handle == -1)
        throw "Cannot create socket";
}
sockaddr_in Socket::parseStringAddr(const string& addr)
{
    size_t pos = addr.find(':');

    sockaddr_in addrIn = {
        AF_INET,
        0,
        { 0 },
        { 0 },
    };

    if (pos == string::npos) {
        auto port = static_cast<uint16_t>(std::stoi(addr.c_str() + pos));
        auto newAddr = string(addr);
        newAddr[pos] = 0;
        addrIn.sin_port = htons(port);
        addrIn.sin_addr.s_addr = inet_addr(newAddr.c_str());
    } else {
        addrIn.sin_addr.s_addr = inet_addr(addr.c_str());
    }

    return addrIn;
}

Socket::Socket(uint8_t base0, uint8_t base1, uint8_t base2, uint8_t base3, uint8_t port1, uint8_t port2)
{

}
