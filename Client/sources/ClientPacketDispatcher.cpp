//
// Created by Quentin Liardeaux on 12/18/19.
//

#include "ClientPacketDispatcher.hpp"

ClientPacketDispatcher::ClientPacketDispatcher(uint16_t serverPort, uint16_t  userPort, std::string addr)
        : m_serverPort(serverPort)
        , m_userPort(userPort)
        , m_addr(std::move(addr))
        , m_isRunning(false)
        , m_stream(m_addr, serverPort) {
}

ClientPacketDispatcher::~ClientPacketDispatcher() {
    m_stream.close();
}

void ClientPacketDispatcher::run() {
    m_stream.connect(m_addr, m_serverPort);
    m_isRunning = true;
    m_dispatcherThread = std::thread(&ClientPacketDispatcher::dispatch, this);
}

void ClientPacketDispatcher::stop() {
    m_isRunning = false;
    m_dispatcherThread.join();
}

void ClientPacketDispatcher::sendCreateGame(std::string& name, std::string& password, std::string& nickname) {
    auto message = CreateGame(0, name, password, nickname);

    m_stream.send(message.serialize().data(), message.getSize());
}

void ClientPacketDispatcher::sendJoinGame(std::string &name, std::string& password, std::string& nickname) {
    auto message = JoinGame(0, name, password, nickname);

    m_stream.send(message.serialize().data(), message.getSize());
}

void ClientPacketDispatcher::connectToServer(uint16_t port, std::string &addr) {
    auto message = ClientConnect(port, addr);

    m_stream.send(message.serialize().data(), message.getSize());

    auto result = dynamic_cast<RoomInfo*>(receiveMessage().get());
}

packet_header_t ClientPacketDispatcher::receiveHeader() {
    packet_header_t hdr = {};
    ssize_t receivedSize = 0;

    m_stream.receive(&hdr, PACKET_HDR_SIZE, receivedSize);
    return hdr;
}

std::unique_ptr<Message> ClientPacketDispatcher::createMessage(packet_header_t &hdr) {
    auto data = new uint8_t[hdr.packet_size];
    ssize_t receivedSize = 0;
    std::unique_ptr<Message> msg;

    m_stream.receive(data, hdr.packet_size, receivedSize);
    switch (hdr.packet_id) {
        case CREATE_GAME:
            msg = std::make_unique<Message>(CreateGame(data));
            break;
        case JOIN_GAME:
            msg = std::make_unique<Message>(JoinGame(data));
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
        packet_header_t hdr = receiveHeader();
        std::cout << hdr.packet_id << std::endl;
        //auto msg = createMessage(hdr);
    }
}
