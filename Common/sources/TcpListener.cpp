//
// Created by alex on 11/10/19.
//

#include "TcpListener.hpp"
#include <iostream>

TcpStream TcpListener::accept() const
{
    socklen_t s = sizeof(sockaddr);
    RawSocket newConnection =::accept(m_handle, const_cast<sockaddr*>(&m_addr), &s);

    if (newConnection == -1)
        throw "Error while connecting";
    return TcpStream(newConnection);
}

void TcpListener::listen(int32_t nbClientMax) const
{
    cout << "Listening" << endl;
    ::listen(m_handle, nbClientMax);
}

TcpListener::TcpListener(uint16_t port)
    : Socket(TCP, "0.0.0.0", port)
{}
