//
// Created by Quentin Liardeaux on 12/24/19.
//

#ifndef R_TYPE_SERVERHANDLER_HPP
#define R_TYPE_SERVERHANDLER_HPP

#include <memory>
#include <boost/asio.hpp>

#include "Protocol/Packet.hpp"
#include "UserData.hpp"

template <class T>
class ServerHandler {
public:
    ServerHandler(const UserData& userData, T& socket)
    : m_userData(userData)
    , m_socket(socket) {}
    ~ServerHandler() = default;

    std::unique_ptr<Message> receiveMessage() {
        packet_header_t hdr = receiveHeader();

        return createMessage(hdr);
    }
    void sendMessage(const Message& msg) {
        auto data = new unsigned char[msg.getSize()];
        auto serializedMsg = msg.serialize();

        for (size_t i = 0 ; i < msg.getSize() ; i++)
            data[i] = serializedMsg[i];
        try {
            boost::asio::write(m_socket,
                               boost::asio::buffer(data, msg.getSize()));
        } catch (const boost::exception& e) {
            std::cerr << "Unable to send data with tcp." << std::endl;
        }
        delete[] data;
    }

private:
    packet_header_t receiveHeader() {
        packet_header_t hdr = {};
        ssize_t receivedSize = 0;

        boost::asio::read(m_socket, boost::asio::buffer(&hdr, PACKET_HDR_SIZE));
        return hdr;
    }

    std::unique_ptr<Message> createMessage(packet_header_t &hdr) {
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

    const UserData& m_userData;
    T& m_socket;
};

//template ServerHandler<boost::asio::ip::tcp>;
//template ServerHandler<boost::asio::ip::udp>;

#endif //R_TYPE_SERVERHANDLER_HPP
