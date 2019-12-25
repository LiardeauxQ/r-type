//
// Created by Quentin Liardeaux on 12/18/19.
//

#ifndef R_TYPE_CLIENTPACKETDISPATCHER_HPP
#define R_TYPE_CLIENTPACKETDISPATCHER_HPP

#include <queue>

#include <boost/asio.hpp>
#include <boost/thread.hpp>

#include "Protocol/Packet.hpp"

typedef boost::asio::ip::tcp BoostTcp;

class TcpCommunicationHandler {
public:
    TcpCommunicationHandler() = default;
    TcpCommunicationHandler(uint16_t serverPort, uint16_t userPort, std::string addr);
    ~TcpCommunicationHandler() = default;

    void start();
    void stop();

    void sendCreateGame(uint8_t id, const std::string& name, const std::string& password, const std::string& nickname);
    void sendJoinGame(uint8_t id, const std::string &name, const std::string& password, const std::string& nickname);
    void connectToServer(uint16_t port, const std::string &addr);

    std::queue<std::unique_ptr<Message>> getServerResponses();

private:

    void dispatch();

    std::queue<std::unique_ptr<Message>> m_responses;

    boost::asio::io_context m_context;
    BoostTcp::socket m_socket;
    boost::thread m_responsesThread;
    boost::mutex m_mutex;
    bool m_isRunning;
};

#endif //R_TYPE_CLIENTPACKETDISPATCHER_HPP
