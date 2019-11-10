//
// Created by alex on 11/10/19.
//

#include "TcpListener.hpp"

TcpStream TcpListener::accept() const
{
    socklen_t s = sizeof(sockaddr);
    RawSocket newConnection =::accept(m_handle, const_cast<sockaddr*>(&m_addr), &s);

    if (newConnection == -1)
        throw "Erroe while connecting";
    return TcpStream(newConnection);
}

void TcpListener::listen(int32_t nbClientMax) const
{
    ::listen(m_handle, nbClientMax);
}

TcpListener::TcpListener()
    : Socket(TCP, "0.0.0.0")
{}
