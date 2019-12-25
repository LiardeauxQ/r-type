//
// Created by Quentin Liardeaux on 12/25/19.
//

#ifndef R_TYPE_UDPCOMMUNICATION_HPP
#define R_TYPE_UDPCOMMUNICATION_HPP

#include <queue>

#include <boost/asio.hpp>
#include <boost/thread.hpp>

#include "Protocol/Packet.hpp"
#include "ServerHandler.hpp"
#include "GameData.hpp"

typedef boost::asio::ip::udp BoostUdp;

class UdpCommunication {
public:
    explicit UdpCommunication(std::shared_ptr<GameData> gameData);
    ~UdpCommunication() = default;

    void start();
    void stop();
    void update();

private:
    void checkServerPackets();
    void handlePacket(const Message& msg);

    std::queue<std::unique_ptr<Message>> getServerResponses();

    void dispatch();

    bool m_isRunning;
    std::shared_ptr<GameData> m_gameData;

    std::queue<std::unique_ptr<Message>> m_responses;

    boost::asio::io_context m_context;
    BoostUdp::socket m_socket;
    boost::thread m_responsesThread;
    boost::mutex m_mutex;

    //ServerHandler<BoostUdp::socket> m_handler;
};

#endif //R_TYPE_UDPCOMMUNICATION_HPP
