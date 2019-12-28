//
// Created by Quentin Liardeaux on 12/17/19.
//

#include "Application.hpp"

static uint16_t udpPort = 9500;

Application::Application(int ac, char **av)
    : m_context()
    , m_acceptor(m_context, BoostTcp::endpoint(BoostTcp::v4(), 8678))
    , m_lobby(boost::shared_ptr<Lobby>(new Lobby()))
    {
    accept();
}

void Application::run() {
    m_context.run();
}

void Application::accept() {
    auto client = Client::create(m_context);

    client->setHandler(m_lobby);
    client->setUdpSocket(udpPort++);
    m_clients.push_back(client);
    m_lobby->addClient(client);
    m_acceptor.async_accept(
            client->getSocket(),
            boost::bind(&Application::handleAccept,
                    this,
                    client,
                    boost::asio::placeholders::error));
}

void Application::handleAccept(const boost::shared_ptr<Client>& client,
        const boost::system::error_code& ec) {
    if (!ec)
        client->start();
    accept();
}