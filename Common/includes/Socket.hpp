//
// Created by alex on 11/10/19.
//

#ifndef CPP_RTYPE_2019_SOCKET_HPP
#define CPP_RTYPE_2019_SOCKET_HPP

#include <string>

using namespace std;

#if defined(WINDOWS)
    using RawSocket = int;
#else
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <unistd.h>
    #include <arpa/inet.h>
    #include <netinet/in.h>

    using RawSocket = int;
#endif /* SYSTEM */

#include <cstring>

class Socket {
public:
    enum Type {
        UDP,
        TCP,
        RAW
    };

    Socket(Type type, RawSocket socket);
    Socket(Type type, const string& addr);
    Socket(int32_t domain, int32_t type, int32_t protocol);
    Socket(uint8_t base0, uint8_t base1, uint8_t base2, uint8_t base3, uint8_t port1, uint8_t port2);

    Socket(const Socket& sock) = delete;
    Socket& operator=(const Socket& sock) = default;

    virtual ~Socket();

    bool operator==(const Socket& socket);

protected:
    static sockaddr_in parseStringAddr(const string& addr);

    RawSocket m_handle;
    Type m_type;
    sockaddr m_addr;
private:
    static Type getTypeFromUnix(int32_t type);
};

#endif //CPP_RTYPE_2019_SOCKET_HPP
