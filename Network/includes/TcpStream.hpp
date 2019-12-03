//
// Created by alex on 11/10/19.
//

#ifndef CPP_RTYPE_2019_TCPSTREAM_HPP
#define CPP_RTYPE_2019_TCPSTREAM_HPP

#include "Socket.hpp"

#ifdef WIN32
    using ssize_t = int64_t;
#endif

class TcpStream : public Socket {
public:
    explicit TcpStream(RawSocket sock);
    explicit TcpStream(const std::string& addr, short port);
    ~TcpStream() final = default;

    void connect(const std::string& addr, uint16_t port);
    void connect(const std::string& addr);
    void send(const void *data, size_t size) const;

    template<typename T>
    void receive(T *data, size_t size, ssize_t& received) const
    {
        received = ::recv(m_handle, data, size, 0);

        if (received == -1)
            throw "Error while receiving";
    }

private:
    void connectRaw();
};

#endif //CPP_RTYPE_2019_TCPSTREAM_HPP
