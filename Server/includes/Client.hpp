//
// Created by Quentin Liardeaux on 12/19/19.
//

#ifndef R_TYPE_CLIENT_HPP
#define R_TYPE_CLIENT_HPP

#include <string>
#include <optional>
#include <queue>

#include "protocol.hpp"
#include "Message.hpp"
#include "Protocol/Packet.hpp"
#include "ClientHandler.hpp"
#include "GameRoom.hpp"
#include "Lobby.hpp"
#include "IdProvider.hpp"
#include "Position.hpp"

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/enable_shared_from_this.hpp>

typedef boost::asio::ip::tcp BoostTcp;
typedef boost::asio::ip::udp BoostUdp;

class ClientHandler;
class GameRoom;
class Lobby;

class Client : public boost::enable_shared_from_this<Client> {
public:
    static boost::shared_ptr<Client> create(boost::asio::io_context &context);

    void start();
    void stop();
    void update();

    BoostTcp::socket &getSocket() { return m_tcpSocket; }
    size_t getId() const { return m_id; }
    const std::string& getNickname() const { return m_nickname; }

    void setHandler(boost::shared_ptr<ClientHandler> handler) { m_handler = handler; }
    void setUdpSocket(uint16_t port) { m_udpPort = port; }

    const Position& getPosition() const { return m_position; }
    const Position& getVelocity() const { return m_velocity; }

    void sendPlayerJoinGame(size_t playerId, std::string nickname);
    void sendPlayerQuitGame(size_t playerId);
    void sendPlayerState();
    void sendFriendState(size_t id, const Position& position, const Position& velocity);
    void sendEntityState(size_t id, const Position& position, const Position& velocity, EntityType type);
    void triggerCollision(size_t firstEntity, EntityType firstType,
            size_t secondEntity, EntityType secondType, const Position& pos);
    void startGame();

    ~Client();

private:
    explicit Client(boost::asio::io_context &context);

    void waitHeader(const boost::system::error_code &ec);
    void receivePacket(const boost::system::error_code &ec);
    void receiveBody(const boost::system::error_code &ec);
    std::unique_ptr<Message> handleRequest(uint8_t *data, uint16_t packetId);
    void dispatchPackets(const Message* msg);
    void sendTcpMessage(const Message& msg);
    void sendUdpMessage(const Message& msg);

    void connectClient(const ClientConnect *msg);
    void createGame(const CreateGame *msg);
    void joinGame(const JoinGame *msg);

    void dispatchUdpPackets();
    void receiveUdpPackets();
    std::queue<std::unique_ptr<Message>> getServerResponses();
    void handlePacket(const Message& msg);

    void movePlayer(const DirectionState& msg);
    void fireEntity(const FireEntity& msg);

    boost::asio::io_service m_ioService;
    BoostTcp::socket m_tcpSocket;
    packet_header_t m_packetHeader;
    uint8_t *m_packetData;
    uint8_t *m_writePacketData;
    boost::shared_ptr<ClientHandler> m_handler;
    size_t m_id;
    std::string m_nickname;
    uint16_t m_udpPort;
    std::string m_ipAddress;
    std::optional<BoostUdp::endpoint> m_remoteEndpoint;
    std::optional<BoostUdp::socket> m_udpSocket;
    bool m_isUdpRunning;
    Position m_velocity;
    Position m_position;
    boost::thread m_thread;
    std::queue<std::unique_ptr<Message>> m_udpResponses;
    boost::mutex m_responsesMutex;
};

#endif //R_TYPE_CLIENT_HPP
