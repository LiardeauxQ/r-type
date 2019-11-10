//
// Created by alex on 11/10/19.
//

#ifndef CPP_RTYPE_2019_CLIENT_HPP
#define CPP_RTYPE_2019_CLIENT_HPP

#include <cstdint>
#include <string>

using namespace std;

using ClientId = uint32_t;

class Client {
public:
    Client(TcpSocket socket);
    Client(const Client& client) = delete;
    Client operator=(const Client& client) = delete;

    bool operator==(const Client& rhs);

private:
    TcpSocket m_socket;
    ClientId m_id;
    string m_name;
};

#endif //CPP_RTYPE_2019_CLIENT_HPP
