//
// Created by Quentin Liardeaux on 12/17/19.
//

#ifndef R_TYPE_PACKETDISPATCHER_HPP
#define R_TYPE_PACKETDISPATCHER_HPP

#include "protocol.hpp"
#include "TcpStream.hpp"
#include "Protocol/JoinGame.hpp"
#include "Protocol/CreateGame.hpp"

class PacketDispatcher {
public:
    PacketDispatcher(uint16_t port, std::string addr);
    ~PacketDispatcher() = default;

    void run();

    void sendCreateGame(std::string& name, std::string& password, std::string& nickname);
    void sendJoinGame(std::string& name, std::string& password, std::string& nickname);
private:
    packet_header_t headerReader();
    std::unique_ptr<Message> createMessage(packet_header_t &hdr);
    void dispatch();

    TcpStream m_stream;
    std::string m_addr;
};

#endif //R_TYPE_PACKETDISPATCHER_HPP