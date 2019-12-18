//
// Created by Quentin Liardeaux on 12/18/19.
//

#include "ServerPacketDispatcher.hpp"

ServerPacketDispatcher::ServerPacketDispatcher(uint16_t port, std::string addr)
    : m_port(port)
    , m_addr(std::move(addr))
    , m_isRunning(false)
    , m_listener(port)
    , m_stream() {
}

ServerPacketDispatcher::~ServerPacketDispatcher() {
    m_listener.close();
    m_stream.close();
}

void ServerPacketDispatcher::run() {
    try {
        m_listener.bind();
        m_listener.listen(0);
        m_stream = std::move(m_listener.accept());
        //m_stream.connect(m_addr);
        m_isRunning = true;
        dispatch();
    } catch (const char *s) {
        std::cout << s << std::endl;
    }
}

void ServerPacketDispatcher::sendCreateGame(std::string& name, std::string& password, std::string& nickname) {
    auto message = CreateGame(name, password, nickname);

    m_stream.send(message.serialize().data(), message.getSize());
}

void ServerPacketDispatcher::sendJoinGame(std::string &name, std::string& password, std::string& nickname) {
    auto message = JoinGame(name, password, nickname);

    m_stream.send(message.serialize().data(), message.getSize());
}

packet_header_t ServerPacketDispatcher::headerReader() {
    packet_header_t hdr = {};
    ssize_t receivedSize = 0;

    m_stream.receive(&hdr, PACKET_HDR_SIZE, receivedSize);
    return hdr;
}

std::unique_ptr<Message> ServerPacketDispatcher::createMessage(packet_header_t &hdr) {
    auto data = new uint8_t[hdr.packet_size];
    ssize_t receivedSize = 0;
    std::unique_ptr<Message> msg;

    m_stream.receive(data, hdr.packet_size, receivedSize);
    switch (hdr.packet_id) {
        case CREATE_GAME:
            msg = std::make_unique<CreateGame>(CreateGame(data));
            break;
        case JOIN_GAME:
            msg = std::make_unique<JoinGame>(JoinGame(data));
            break;
        default:
            msg = nullptr;
            break;
    }
    delete[] data;
    return msg;
}

void ServerPacketDispatcher::dispatch() {
    while (m_isRunning) {
        packet_header_t hdr = headerReader();
        auto msg = createMessage(hdr);

        if (msg != nullptr) {
            printf("%d %d\n", hdr.packet_id, msg->getSize());
        }
    }
}