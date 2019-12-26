//
// Created by Quentin Liardeaux on 12/19/19.
//

#include "Client.hpp"

boost::shared_ptr<Client> Client::create(boost::asio::io_context &context) {
    return boost::shared_ptr<Client>(new Client(context));
}

Client::Client(boost::asio::io_context& context)
    : m_ioService()
    , m_tcpSocket(context)
    , m_packetHeader()
    , m_packetData(nullptr)
    , m_id(IdProvider::instance()->getNextId())
    , m_udpPort(0)
    , m_ipAddress()
    , m_isUdpRunning(false) {}

Client::~Client() {}

void Client::start() {
    waitHeader(boost::system::error_code());
}

void Client::stop() {
    m_isUdpRunning = false;
    m_tcpSocket.close();
    m_udpSocket->close();
}

void Client::waitHeader(const boost::system::error_code& ec) {
    boost::asio::async_read(
        m_tcpSocket,
        boost::asio::buffer(&m_packetHeader, PACKET_HDR_SIZE),
        boost::bind(&Client::receivePacket, shared_from_this(), boost::asio::placeholders::error));
}

void Client::receivePacket(const boost::system::error_code& ec) {
    if (ec)
        return;
    if (m_packetData != nullptr)
        delete[] m_packetData;
    m_packetData = new uint8_t[m_packetHeader.packet_size];
    auto tmp = reinterpret_cast<unsigned char*>(&m_packetHeader);
    for (int i = 0 ; i < PACKET_HDR_SIZE ; i++) {
        printf("%d ", tmp[i]);
    }
    printf("\n");
    std::cout << "Receive packet " << m_packetHeader.packet_size << " " << (int)(m_packetHeader.packet_id) << std::endl;
    boost::asio::async_read(
            m_tcpSocket,
            boost::asio::buffer(m_packetData, m_packetHeader.packet_size),
            boost::bind(&Client::receiveBody, shared_from_this(), boost::asio::placeholders::error));
}

void Client::receiveBody(const boost::system::error_code& ec) {
    dispatchPackets(handleRequest(m_packetData, m_packetHeader.packet_id).get());
    delete[] m_packetData;
    m_packetData = nullptr;
}

std::unique_ptr<Message> Client::handleRequest(uint8_t *data, uint16_t packetId) {
    for (auto &initializer : packetInitializers) {
        if (std::get<0>(initializer) == packetId)
            return std::get<1>(initializer)(data);
    }
    return nullptr;
}

void Client::sendMessage(const Message& msg) {
    boost::asio::async_write(
            m_tcpSocket,
            boost::asio::buffer(msg.serialize().data(), msg.getSize()),
            boost::bind(&Client::waitHeader, shared_from_this(), boost::asio::placeholders::error));
}

void Client::dispatchPackets(const Message *msg) {
    switch (msg->getId()) {
        case CLIENT_CONNECT:
            connectClient(dynamic_cast<const ClientConnect*>(msg));
            break;
        case CREATE_GAME:
            createGame(dynamic_cast<const CreateGame*>(msg));
            break;
        case JOIN_GAME:
            joinGame(dynamic_cast<const JoinGame*>(msg));
            break;
        default:
            break;
    }
}

void Client::connectClient(const ClientConnect *msg) {
    auto lobby = dynamic_cast<Lobby*>(m_handler.get());

    if (lobby == nullptr)
        return;
    std::cout << "Connection " << msg->getAddr() << std::endl;
    m_ipAddress = msg->getAddr();
    m_remoteEndpoint = BoostUdp::endpoint(boost::asio::ip::address::from_string(msg->getAddr()), msg->getPort());
    std::cout << "Send success connect " << (int)(m_id) << std::endl;
    sendMessage(SuccessConnect(static_cast<uint8_t>(m_id)));
}

void Client::createGame(const CreateGame *msg) {
    auto lobby = dynamic_cast<Lobby*>(m_handler.get());

    if (lobby == nullptr)
        return;
    std::cout << "Create " << msg->getNickname() << std::endl;
    m_nickname = msg->getNickname();
    lobby->createGameRoom(msg->getName(), 10);
    sendMessage(lobby->getRoomInfo(msg->getName(), msg->getPlayerId()));
}

void Client::joinGame(const JoinGame *msg) {
    auto lobby = dynamic_cast<Lobby*>(m_handler.get());

    if (lobby == nullptr)
        return;
    try {
        std::cout << "Join " << msg->getNickname() << std::endl;
        auto roomId = lobby->getRoomId(msg->getName());
        m_nickname = msg->getNickname();
        lobby->joinGameRoom(msg->getPlayerId(), roomId);
        sendMessage(lobby->getRoomInfo(msg->getName(), msg->getPlayerId()));
    } catch (const char *str) {
        std::cerr << str << std::endl; //TODO
    }
}

void Client::sendPlayerJoinGame(uint8_t playerId, std::string nickname) {
    sendMessage(RoomPlayerJoin(playerId, std::move(nickname), true));
}

void Client::sendPlayerQuitGame(uint8_t playerId) {
    sendMessage(RoomPlayerQuit(playerId, "unknown", true));
}

void Client::startGame() {
    auto localEndpoint = BoostUdp::endpoint(boost::asio::ip::address_v4::any(), m_udpPort);

    sendMessage(GameStart(m_udpPort));
    m_udpSocket = BoostUdp::socket(m_ioService, localEndpoint.protocol());
    m_udpSocket->bind(localEndpoint);
    m_thread = boost::thread(&Client::dispatchUdpPackets, shared_from_this());
}

void Client::dispatchUdpPackets() {
    packet_header_t hdr = {0, 0, 0};
    uint8_t *data = nullptr;

    m_udpSocket->receive_from(boost::asio::buffer(&hdr, PACKET_HDR_SIZE), *m_remoteEndpoint);
    data = new uint8_t[hdr.packet_size];
    m_udpSocket->receive_from(boost::asio::buffer(data, hdr.packet_size), *m_remoteEndpoint);
    switch (hdr.packet_id) {
        case GAME_READY:
        case FIRE_ENTITY:
            fireEntity();
        case MOVE:
            movePlayer();
        default:
            break;
    }
    delete[] data;
}

void Client::movePlayer() {

}

void Client::fireEntity() {

}