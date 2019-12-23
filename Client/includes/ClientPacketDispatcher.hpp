//
// Created by Quentin Liardeaux on 12/18/19.
//

#ifndef R_TYPE_CLIENTPACKETDISPATCHER_HPP
#define R_TYPE_CLIENTPACKETDISPATCHER_HPP

#include <thread>

#include "Protocol/CreateGame.hpp"
#include "Protocol/JoinGame.hpp"
#include "Protocol/ClientConnect.hpp"
#include "Protocol/RoomInfo.hpp"
#include "TcpStream.hpp"
#include "TcpListener.hpp"

class ClientPacketDispatcher {
public:
    ClientPacketDispatcher() = default;
    ClientPacketDispatcher(uint16_t serverPort, uint16_t userPort, std::string addr);
    ~ClientPacketDispatcher();

    void run();
    void stop();

    void sendCreateGame(std::string& name, std::string& password, std::string& nickname);
    void sendJoinGame(std::string &name, std::string& password, std::string& nickname);
    void connectToServer(uint16_t port, std::string &addr);
    std::unique_ptr<Message> receiveMessage();

private:
    packet_header_t receiveHeader();
    std::unique_ptr<Message> createMessage(packet_header_t &hdr);

    void dispatch();

    uint16_t m_serverPort;
    uint16_t m_userPort;
    std::string m_addr;
    bool m_isRunning;
    TcpStream m_stream;
    std::thread m_dispatcherThread;
};

#endif //R_TYPE_CLIENTPACKETDISPATCHER_HPP
