//
// Created by Quentin Liardeaux on 12/17/19.
//

#include "Protocol/PacketDispatcher.hpp"

PacketDispatcher::PacketDispatcher()
    : m_isRunning(false)
    , m_listener()
    , m_addr()
{}

PacketDispatcher::PacketDispatcher(uint16_t port, std::string addr)
    : m_isRunning(false)
    , m_listener(port)
    , m_addr(std::move(addr))
{
}

void PacketDispatcher::run() {
    std::cout << "will run" << std::endl;
    m_listener.listen(0);
    std::cout << "listen" << std::endl;
    m_stream = m_listener.accept();
    std::cout << "is accepted" << std::endl;
    m_stream.connect(m_addr);
    std::cout << "is connected" << std::endl;
    m_isRunning = true;
    dispatch();
}

void PacketDispatcher::sendCreateGame(std::string& name, std::string& password, std::string& nickname) {
    auto message = CreateGame(name, password, nickname);

    m_stream.send(message.serialize().data(), message.getSize());
}

void PacketDispatcher::sendJoinGame(std::string &name, std::string& password, std::string& nickname) {
    auto message = JoinGame(name, password, nickname);

    m_stream.send(message.serialize().data(), message.getSize());
}

packet_header_t PacketDispatcher::headerReader() {
    packet_header_t hdr = {};
    ssize_t receivedSize = 0;

    m_stream.receive(&hdr, PACKET_HDR_SIZE, receivedSize);
    return hdr;
}

std::unique_ptr<Message> PacketDispatcher::createMessage(packet_header_t &hdr) {
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