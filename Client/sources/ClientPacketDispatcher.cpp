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

void ClientPacketDispatcher::sendCreateGame(std::string& name, std::string& password, std::string& nickname) {
    auto message = CreateGame(0, name, password, nickname);

    boost::asio::write(m_socket,
            boost::asio::buffer(message.serialize().data(), message.getSize()));
}

void ClientPacketDispatcher::sendJoinGame(std::string &name, std::string& password, std::string& nickname) {
    auto message = JoinGame(0, name, password, nickname);

    boost::asio::write(m_socket,
            boost::asio::buffer(message.serialize().data(), message.getSize()));
}

void ClientPacketDispatcher::connectToServer(uint16_t port, std::string &addr) {
    auto message = ClientConnect(port, addr);

    boost::asio::write(m_socket,
            boost::asio::buffer(message.serialize().data(), message.getSize()));
}

packet_header_t ClientPacketDispatcher::receiveHeader() {
    packet_header_t hdr = {};
    ssize_t receivedSize = 0;

    boost::asio::read(m_socket, boost::asio::buffer(&hdr, PACKET_HDR_SIZE));
    return hdr;
}

std::unique_ptr<Message> ClientPacketDispatcher::createMessage(packet_header_t &hdr) {
    auto data = new uint8_t[hdr.packet_size];
    std::unique_ptr<Message> msg;

    boost::asio::read(m_socket, boost::asio::buffer(data, hdr.packet_size));
    switch (hdr.packet_id) {
        case CREATE_GAME:
            msg = std::make_unique<Message>(CreateGame(data));
            break;
        case JOIN_GAME:
            msg = std::make_unique<Message>(JoinGame(data));
            break;
        case ROOM_INFO:
            msg = std::make_unique<Message>(RoomInfo(data));
            break;
        default:
            msg = nullptr;
            break;
    }
    delete[] data;
    return msg;
}

std::unique_ptr<Message> ClientPacketDispatcher::receiveMessage() {
    packet_header_t hdr = receiveHeader();

    return createMessage(hdr);
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
