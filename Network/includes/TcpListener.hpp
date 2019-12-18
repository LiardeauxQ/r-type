//
// Created by alex on 11/10/19.
//

#ifndef CPP_RTYPE_2019_TCPLISTENER_HPP
#define CPP_RTYPE_2019_TCPLISTENER_HPP

#include "Socket.hpp"
#include "TcpStream.hpp"
#include <iostream>
#include <optional>

class TcpListener : public Socket {
public:
    explicit TcpListener(uint16_t port);

    [[nodiscard]] TcpStream accept() const;
    void listen(int32_t nbConnection = 0) const;
    [[nodiscard]] std::optional<TcpStream> acceptNonBlocking() const;
};

#endif //CPP_RTYPE_2019_TCPLISTENER_HPP