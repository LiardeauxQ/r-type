//
// Created by Quentin Liardeaux on 12/18/19.
//

#ifndef R_TYPE_SERVERPACKETDISPATCHER_HPP
#define R_TYPE_SERVERPACKETDISPATCHER_HPP

#include "Protocol/PacketDispatcher.hpp"

class ServerPacketDispatcher {
public:
    ServerPacketDispatcher(uint16_t port, std::string addr);
    ~ServerPacketDispatcher();


    ServerPacketDispatcher(const ServerPacketDispatcher& dispatcher) = default;
    ServerPacketDispatcher& operator=(const ServerPacketDispatcher& dispatcher) = default;

    void run();

    packet_header_t headerReader();
    std::unique_ptr<Message> createMessage(packet_header_t &hdr);
    void sendJoinGame(std::string &name, std::string& password, std::string& nickname);
    void sendCreateGame(std::string& name, std::string& password, std::string& nickname);

private:
    void dispatch();

    uint16_t m_port;
    std::string m_addr;
    bool m_isRunning;
    TcpListener m_listener;
    TcpStream m_stream;
};


#endif //R_TYPE_SERVERPACKETDISPATCHER_HPP
