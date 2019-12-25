//
// Created by Quentin Liardeaux on 12/18/19.
//

#include "ClientPacketDispatcher.hpp"

ClientPacketDispatcher::ClientPacketDispatcher(uint16_t serverPort, uint16_t  userPort, std::string addr)
        : m_serverPort(serverPort)
        , m_userPort(userPort)
        , m_addr(std::move(addr))
        , m_isRunning(false)
        , m_responses()
        , m_context()
        , m_socket(m_context)
        , m_mutex() {
}

void ClientPacketDispatcher::start() {
    m_socket.connect(BoostTcp::endpoint(
            boost::asio::ip::address::from_string(m_addr), m_serverPort));
    m_isRunning = true;
    m_responsesThread = boost::thread(&ClientPacketDispatcher::dispatch, this);
}

void ClientPacketDispatcher::stop() {
    m_isRunning = false;
    m_responsesThread.join();
    m_socket.close();
}

void ClientPacketDispatcher::sendCreateGame(uint8_t id, const std::string& name, const std::string& password, const std::string& nickname) {
    auto message = CreateGame(id, name, password, nickname);

    boost::asio::write(m_socket,
            boost::asio::buffer(message.serialize().data(), message.getSize()));
}

void ClientPacketDispatcher::sendJoinGame(uint8_t id, const std::string &name, const std::string& password, const std::string& nickname) {
    auto message = JoinGame(id, name, password, nickname);

    boost::asio::write(m_socket,
            boost::asio::buffer(message.serialize().data(), message.getSize()));
}

void ClientPacketDispatcher::connectToServer(uint16_t port, const std::string &addr) {
    auto message = ClientConnect(port, addr);

    boost::asio::write(m_socket,
                       boost::asio::buffer(message.serialize().data(), message.getSize()));
}



void ClientPacketDispatcher::dispatch() {
    while (m_isRunning) {
        auto msg = receiveMessage();
        m_mutex.lock();
        m_responses.push(std::move(msg));
        m_mutex.unlock();
    }
}

std::queue<std::unique_ptr<Message>> ClientPacketDispatcher::getServerResponses() {
    m_mutex.lock();

    auto queue = std::move(m_responses);

    m_responses = std::queue<std::unique_ptr<Message>>();
    m_mutex.unlock();
    return queue;
}
