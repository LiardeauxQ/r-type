//
// Created by alex on 11/10/19.
//

#include "Socket.hpp"

Socket::Socket()
    : m_handle(FAILED_SOCKET)
    , m_type(TCP)
    , m_addr()
    , m_blocking(false)
{}

Socket::Socket(Socket::Type type, RawSocket handle)
    : m_handle(handle)
    , m_type(type)
    , m_addr{}
{}

Socket::Socket(Socket::Type type, const std::string& addr)
    : Socket(type, parseStringAddr(addr))
{}

Socket::Socket(Socket::Type type, sockaddr_in addr)
    : m_handle(FAILED_SOCKET)
    , m_type(type)
    , m_addr()
{
    memcpy(&m_addr, &addr, sizeof(addr));

    m_handle = ::socket(AF_INET, getUnixFromType(m_type), 0);
    if (m_handle == FAILED_SOCKET)
        throw "Error while creating socket.";
}

bool Socket::operator==(const Socket& socket) const
{
    return m_handle == socket.m_handle;
}

void Socket::bind() {
    if (::bind(m_handle, &m_addr, sizeof(m_addr)) < 0) {
        perror("bind");
        throw "Error while binding.";
    }
}

void Socket::close() {
    #ifdef WIN32
        closesocket(m_handle);
            WSACleanup();
    #else
        std::cout << "Close socket " << m_handle << std::endl;
        ::close(m_handle);
    #endif
}

int32_t Socket::getUnixFromType(Socket::Type type)
{
    switch (type) {
    case UDP:
        return SOCK_DGRAM;
    case TCP:
        return SOCK_STREAM;
    case RAW:
        return SOCK_RAW;
    default:
        return SOCK_RAW;
    }
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
    if (m_handle == FAILED_SOCKET)
        throw "Cannot create socket";
}
sockaddr_in Socket::parseStringAddr(const std::string& addr, uint16_t port)
{
    size_t pos = addr.find(':');

    sockaddr_in addrIn;

    if (pos != std::string::npos) {
        auto newPort = static_cast<uint16_t>(std::stoi(addr.c_str() + pos));
        auto newAddr = std::string(addr);
        newAddr[pos] = 0;
        std::cout << "Filling sockaddr with: " << newAddr.c_str() << " " << newPort << std::endl;
        addrIn.sin_port = htons(newPort);
        addrIn.sin_addr.s_addr = inet_addr(newAddr.c_str());
    } else {
        std::cout << "Filling sockaddr with: " << addr.c_str() << " " << port << std::endl;
        addrIn.sin_addr.s_addr = inet_addr(addr.c_str());
        addrIn.sin_port = htons(port);
    }
    addrIn.sin_family = AF_INET;
    return addrIn;
}

Socket::Socket(uint8_t base0, uint8_t base1, uint8_t base2, uint8_t base3, uint8_t port1, uint8_t port2)
{

}

Socket::Socket(Socket::Type type, const std::string& addr, uint16_t port)
    : Socket(type, parseStringAddr(addr, port))
{}

int Socket::setNonBlocking(bool active)
{
    #ifdef WIN32
        u_long flags = active ? 0 : 1;
        return ioctlsocket(m_handle, FIONBIO, &flags);
    #else
        return ::fcntl(m_handle, F_SETFL, active ? O_NONBLOCK : ~O_NONBLOCK);
    #endif
}
