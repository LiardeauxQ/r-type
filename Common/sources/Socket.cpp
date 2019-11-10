//
// Created by alex on 11/10/19.
//

#include "Socket.hpp"

Socket::Socket(Socket::Type type, RawSocket handle)
    : m_handle(handle)
{

}

Socket::Socket(Socket::Type type, const string& addr)
{

}

Socket::~Socket()
{
    close(m_handle);
}

Type Socket::getType() {}