//
// Created by alex on 11/10/19.
//

#ifndef CPP_RTYPE_2019_CLIENT_HPP
#define CPP_RTYPE_2019_CLIENT_HPP

#include "Message.hpp"
#include "TcpStream.hpp"
#include <cstdint>
#include <openssl/md5.h>
#include <string>

using namespace std;

using ClientId = uint8_t[MD5_DIGEST_LENGTH];

class Client {
public:
    explicit Client(const TcpStream& socket);
    Client(const Client& client) = delete;
    Client operator=(const Client& client) = delete;

    bool operator==(const Client& rhs) const;

    string m_name;
    ClientId m_id;
private:
    TcpStream m_socket;
};

#endif //CPP_RTYPE_2019_CLIENT_HPP
