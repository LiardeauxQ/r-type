//
// Created by alex on 11/10/19.
//

#ifndef CPP_RTYPE_2019_SOCKET_HPP
#define CPP_RTYPE_2019_SOCKET_HPP

#include <string>

#if defined(WIN32)
    #include <WinSock2.h>
    #include <WS2tcpip.h>

    typedef SOCKET RawSocket;
    #define FAILED_SOCKET INVALID_SOCKET
#else
    #include <fcntl.h>
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <unistd.h>
    #include <arpa/inet.h>
    #include <netinet/in.h>

    typedef int RawSocket;
    #define FAILED_SOCKET -1
#endif /* SYSTEM */

#include <iostream>
#include <cstring>

class Socket {
public:
    enum Type {
        UDP,
        TCP,
        RAW
    };

    Socket();
    Socket(Type type, RawSocket socket);
    Socket(Type type, const std::string& addr);
    Socket(Type type, const std::string& addr, uint16_t port);
    Socket(int32_t domain, int32_t type, int32_t protocol);
    Socket(uint8_t base0, uint8_t base1, uint8_t base2, uint8_t base3, uint8_t port1, uint8_t port2);

    Socket(const Socket& sock) = default;
    Socket& operator=(const Socket& sock) = default;

    virtual ~Socket() = default;

    bool operator==(const Socket& socket) const;

    int setNonBlocking(bool active = true);
    void bind();

    void close();
protected:
    static sockaddr_in parseStringAddr(const std::string& addr, uint16_t port = 0);

    RawSocket m_handle;
    Type m_type;
    sockaddr m_addr;
    bool m_blocking;
private:
    Socket(Socket::Type type, sockaddr_in addr);
    static Type getTypeFromUnix(int32_t type);
    int32_t getUnixFromType(Type type);
};

#endif //CPP_RTYPE_2019_SOCKET_HPP
