//
// Created by Quentin Liardeaux on 12/18/19.
//

#ifndef R_TYPE_CLIENTPACKETDISPATCHER_HPP
#define R_TYPE_CLIENTPACKETDISPATCHER_HPP

#include "Protocol/PacketDispatcher.hpp"
#include <thread>

class ClientPacketDispatcher {
public:
    ClientPacketDispatcher() = default;
    ClientPacketDispatcher(uint16_t port, std::string addr);
    ~ClientPacketDispatcher();

    void run();
    void stop();

    void sendCreateGame(std::string& name, std::string& password, std::string& nickname);
    void sendJoinGame(std::string &name, std::string& password, std::string& nickname);
    packet_header_t headerReader();
    std::unique_ptr<Message> createMessage(packet_header_t &hdr);

private:
    void dispatch();

    uint16_t m_port;
    std::string m_addr;
    bool m_isRunning;
    TcpStream m_stream;
    std::thread m_dispatcherThread;
};

#endif //R_TYPE_CLIENTPACKETDISPATCHER_HPP
