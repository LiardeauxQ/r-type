//
// Created by Quentin Liardeaux on 12/24/19.
//

#include "ServerHandler.hpp"

std::unique_ptr<Message> TcpServerHandler::receiveMessage() {
    packet_header_t hdr = receiveHeader();

    return createMessage(hdr);
}
void TcpServerHandler::sendMessage(const Message& msg) {
    boost::asio::write(m_socket,
                       boost::asio::buffer(msg.serialize().data(), msg.getSize()));
}

packet_header_t TcpServerHandler::receiveHeader() {
    packet_header_t hdr = {};
    ssize_t receivedSize = 0;

    boost::asio::read(m_socket, boost::asio::buffer(&hdr, PACKET_HDR_SIZE));
    return hdr;
}

std::unique_ptr<Message> TcpServerHandler::createMessage(packet_header_t &hdr) {
    auto data = new uint8_t[hdr.packet_size];
    std::unique_ptr<Message> msg;

    boost::asio::read(m_socket, boost::asio::buffer(data, hdr.packet_size));
    for (auto &initialize : packetInitializers) {
        if (std::get<0>(initialize) == hdr.packet_id) {
            msg = std::get<1>(initialize)(data);
            break;
        }
    }
    delete[] data;
    return msg;
}

std::unique_ptr<Message> UdpServerHandler::receiveMessage() {
    packet_header_t hdr = receiveHeader();

    return createMessage(hdr);
}

void UdpServerHandler::sendMessage(const Message& msg) {
    unsigned char *data = msg.serialize().data();

    for (size_t i = 0 ; i < msg.getSize() ; i++) {
        printf("%c ", data[i]);
    }
    printf("\n");
    boost::asio::write(m_socket,
                       boost::asio::buffer(data, msg.getSize()));
}

packet_header_t UdpServerHandler::receiveHeader() {
    packet_header_t hdr = {};
    ssize_t receivedSize = 0;

    boost::asio::read(m_socket, boost::asio::buffer(&hdr, PACKET_HDR_SIZE));
    return hdr;
}

std::unique_ptr<Message> UdpServerHandler::createMessage(packet_header_t &hdr) {
    auto data = new uint8_t[hdr.packet_size];
    std::unique_ptr<Message> msg;

    boost::asio::read(m_socket, boost::asio::buffer(data, hdr.packet_size));
    for (auto &initialize : packetInitializers) {
        if (std::get<0>(initialize) == hdr.packet_id) {
            msg = std::get<1>(initialize)(data);
            break;
        }
    }
    delete[] data;
    return msg;
}
