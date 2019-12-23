//
// Created by Quentin Liardeaux on 12/17/19.
//

#ifndef R_TYPE_APPLICATION_HPP
#define R_TYPE_APPLICATION_HPP

#include "TcpListener.hpp"
#include "TcpStream.hpp"
#include "Lobby.hpp"

#include <boost/asio.hpp>
#include <boost/bind.hpp>

typedef boost::asio::ip::tcp BoostTcp;

class Application {
public:
    Application(int ac, char **av);

    ~Application() = default;

    void run();

private:
    void accept();

    void handleAccept(const boost::shared_ptr<Client> &client, const boost::system::error_code &ie);

    boost::asio::io_context m_context;
    BoostTcp::acceptor m_acceptor;
    std::list<boost::shared_ptr<Client>> m_clients;
    boost::shared_ptr<Lobby> m_lobby;
};

#endif //R_TYPE_APPLICATION_HPP
