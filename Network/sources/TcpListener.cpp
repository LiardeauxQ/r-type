//
// Created by alex on 11/10/19.
//

#include "TcpListener.hpp"

TcpStream TcpListener::accept() const
{
    socklen_t s = sizeof(sockaddr);
    RawSocket newConnection = ::accept(m_handle, const_cast<sockaddr*>(&m_addr), &s);

    if (newConnection == FAILED_SOCKET)
        throw "Error while connecting";
    return TcpStream(newConnection);
}

std::optional<TcpStream> TcpListener::acceptNonBlocking() const
{
    socklen_t s = sizeof(sockaddr);
    RawSocket newConnection = ::accept(m_handle, const_cast<sockaddr*>(&m_addr), &s);

    return (newConnection == FAILED_SOCKET) ? std::nullopt : std::optional<TcpStream>{newConnection};
}

void TcpListener::listen(int32_t nbClientMax) const
{
    if (::listen(m_handle, nbClientMax) == -1)
        throw "Error while listening.";
}

TcpListener::TcpListener(uint16_t port)
    : Socket(TCP, "0.0.0.0", port)
{}
