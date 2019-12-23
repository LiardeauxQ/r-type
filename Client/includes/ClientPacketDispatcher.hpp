//
// Created by Quentin Liardeaux on 12/18/19.
//

#ifndef R_TYPE_CLIENTPACKETDISPATCHER_HPP
#define R_TYPE_CLIENTPACKETDISPATCHER_HPP

#include <queue>

#include <boost/asio.hpp>
#include <boost/thread.hpp>

#include "Protocol/CreateGame.hpp"
#include "Protocol/JoinGame.hpp"
#include "Protocol/ClientConnect.hpp"
#include "Protocol/RoomInfo.hpp"
#include "Protocol/SuccessConnect.hpp"
#include "Protocol/RoomPlayerJoin.hpp"
#include "Protocol/RoomPlayerQuit.hpp"
#include "Protocol/RoomPlayerState.hpp"
#include "TcpStream.hpp"
#include "TcpListener.hpp"

typedef boost::asio::ip::tcp BoostTcp;

class ClientPacketDispatcher {
public:
    ClientPacketDispatcher() = default;
    ClientPacketDispatcher(uint16_t serverPort, uint16_t userPort, std::string addr);
    ~ClientPacketDispatcher() = default;

    void start();
    void stop();

    void sendCreateGame(std::string& name, std::string& password, std::string& nickname);
    void sendJoinGame(std::string &name, std::string& password, std::string& nickname);
    void connectToServer(uint16_t port, std::string &addr);

    std::queue<std::unique_ptr<Message>> getServerResponses();

private:
    std::unique_ptr<Message> receiveMessage();
    packet_header_t receiveHeader();
    std::unique_ptr<Message> createMessage(packet_header_t &hdr);

    void dispatch();

    uint16_t m_serverPort;
    uint16_t m_userPort;
    std::string m_addr;
    bool m_isRunning;
    std::queue<std::unique_ptr<Message>> m_responses;

    boost::asio::io_context m_context;
    BoostTcp::socket m_socket;
    boost::thread m_responsesThread;
    boost::mutex m_mutex;
};

#endif //R_TYPE_CLIENTPACKETDISPATCHER_HPP
