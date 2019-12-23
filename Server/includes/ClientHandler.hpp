//
// Created by Quentin Liardeaux on 12/20/19.
//

#ifndef R_TYPE_CLIENTHANDLER_HPP
#define R_TYPE_CLIENTHANDLER_HPP

#include <list>
#include <boost/shared_ptr.hpp>

#include "Client.hpp"

class Client;

class ClientHandler {
public:
    ClientHandler() = default;
    virtual ~ClientHandler() = default;
protected:
    std::list<boost::shared_ptr<Client>> m_clients;
};

#endif //R_TYPE_CLIENTHANDLER_HPP
