//
// Created by Quentin Liardeaux on 12/17/19.
//

#ifndef R_TYPE_PACKETDISPATCHER_HPP
#define R_TYPE_PACKETDISPATCHER_HPP

#include "protocol.hpp"
#include "TcpListener.hpp"
#include "Protocol/JoinGame.hpp"
#include "Protocol/CreateGame.hpp"

class PacketDispatcher {
public:
    PacketDispatcher();
    PacketDispatcher(uint16_t port, std::string addr);
    virtual ~PacketDispatcher() = default;

    PacketDispatcher(const PacketDispatcher& dispatcher) = default;
    PacketDispatcher& operator=(const PacketDispatcher& dispatcher) = default;

    void run();

    void sendCreateGame(std::string& name, std::string& password, std::string& nickname);
    void sendJoinGame(std::string& name, std::string& password, std::string& nickname);

protected:
    std::unique_ptr<Message> createMessage(packet_header_t &hdr);
    packet_header_t headerReader();

    virtual void dispatch() {};

    bool m_isRunning;
private:
    TcpListener m_listener;
    TcpStream m_stream;
    std::string m_addr;
};

#endif //R_TYPE_PACKETDISPATCHER_HPP