//
// Created by alex on 11/10/19.
//

#ifndef CPP_RTYPE_2019_TCPSTREAM_HPP
#define CPP_RTYPE_2019_TCPSTREAM_HPP

#include "Socket.hpp"

class TcpStream : public Socket {
public:
    explicit TcpStream(RawSocket sock);
    ~TcpStream() final = default;

    void connect(const string& addr, uint16_t port);
    void connect(const string& addr);
    void send(const void *data, size_t size) const;

    template<typename T>
    void receive(T& data, size_t size, ssize_t& received) const;

private:
    void connectRaw();
};

#endif //CPP_RTYPE_2019_TCPSTREAM_HPP
