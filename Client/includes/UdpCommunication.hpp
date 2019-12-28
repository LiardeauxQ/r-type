//
// Created by Quentin Liardeaux on 12/25/19.
//

#ifndef R_TYPE_UDPCOMMUNICATION_HPP
#define R_TYPE_UDPCOMMUNICATION_HPP

#include <queue>

#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/enable_shared_from_this.hpp>

#include "Protocol/Packet.hpp"
#include "ServerHandler.hpp"
#include "GameData.hpp"
#include "IdProvider.hpp"

typedef boost::asio::ip::udp BoostUdp;

class UdpCommunication: public boost::enable_shared_from_this<UdpCommunication> {
public:
    static boost::shared_ptr<UdpCommunication> create(std::shared_ptr<GameData> gameData);
    ~UdpCommunication() = default;

    void start();
    void stop();
    void update();

    void playerMove(float x, float y);
    void playerShot();

private:
    explicit UdpCommunication(std::shared_ptr<GameData> gameData);

    packet_header_t receiveHeader();
    std::unique_ptr<Message> createMessage(const packet_header_t& hdr);
    std::unique_ptr<Message> receiveMessage();
    void checkServerPackets();
    void handlePacket(const Message& msg);

    std::queue<std::unique_ptr<Message>> getServerResponses();

    void receiveSyncDistance(const SyncDistance& msg);
    void receiveEntityState(const EntityState& msg);

    void sendMessage(const Message& msg);

    void dispatch();

    bool m_isRunning;
    std::shared_ptr<GameData> m_gameData;

    std::queue<std::unique_ptr<Message>> m_responses;

    boost::asio::io_service m_ioService;
    BoostUdp::socket m_socket;
    boost::thread m_responsesThread;
    boost::mutex m_mutex;
};

#endif //R_TYPE_UDPCOMMUNICATION_HPP
