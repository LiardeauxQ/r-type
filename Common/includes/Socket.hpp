//
// Created by alex on 11/10/19.
//

#ifndef CPP_RTYPE_2019_SOCKET_HPP
#define CPP_RTYPE_2019_SOCKET_HPP

using namespace std;

#if defined(WINDOWS)
    using RawSocket = int;
#else
    using RawSocket = int;
#endif /* SYSTEM */

class Socket {
public:
    enum Type {
        UDP,
        TCP,
        RAW
    };

    Socket(Type type, RawSocket socket);
    Socket(Type type, const string& addr);

    Socket(const Socket& sock) = delete;
    Socket& operator=(const Socket& sock) = delete;

    virtual ~Socket();

    bool operator==(const Socket& socket);

    RawSocket getHandle() noexcept const;
    Type getType() noexcept const;
protected:
    RawSocket m_handle;
    Type m_type;
};

#endif //CPP_RTYPE_2019_SOCKET_HPP
