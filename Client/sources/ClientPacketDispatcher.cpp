//
// Created by Quentin Liardeaux on 12/18/19.
//

#include "ClientPacketDispatcher.hpp"

ClientPacketDispatcher::ClientPacketDispatcher(uint16_t port, std::string addr)
        : m_port(port)
        , m_addr(std::move(addr))
        , m_isRunning(false)
        , m_stream(m_addr, port) {
}

ClientPacketDispatcher::~ClientPacketDispatcher() {
    m_stream.close();
}

void ClientPacketDispatcher::run() {
    m_stream.connect(m_addr, m_port);
    m_isRunning = true;
    //m_dispatcherThread = std::thread(&ClientPacketDispatcher::dispatch, this);
}

void ClientPacketDispatcher::stop() {
    m_isRunning = false;
    m_dispatcherThread.join();
}

void ClientPacketDispatcher::sendCreateGame(std::string& name, std::string& password, std::string& nickname) {
    auto message = CreateGame(name, password, nickname);

    m_stream.send(message.serialize().data(), message.getSize());
}

void ClientPacketDispatcher::sendJoinGame(std::string &name, std::string& password, std::string& nickname) {
    auto message = JoinGame(name, password, nickname);

    m_stream.send(message.serialize().data(), message.getSize());
}

packet_header_t ClientPacketDispatcher::headerReader() {
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

void ClientPacketDispatcher::dispatch() {
    while (m_isRunning) {
        packet_header_t hdr = headerReader();
        auto msg = createMessage(hdr);
    }
}
