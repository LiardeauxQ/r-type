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
    , m_writePacketData(nullptr)
    , m_id(IdProvider::instance()->getNextId())
    , m_udpPort(0)
    , m_ipAddress()
    , m_isUdpRunning(false)
    , m_velocity(20, 20)
    , m_position(100, 100) {}

Client::~Client() {}

void Client::start() {
    waitHeader(boost::system::error_code());
}

void Client::stop() {
    m_isUdpRunning = false;
    m_thread.join();
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

void Client::sendTcpMessage(const Message& msg) {
    auto serializedData = msg.serialize();
    if (m_writePacketData != nullptr)
        delete[] m_writePacketData;
    m_writePacketData = new uint8_t[msg.getSize()];
    for (size_t i = 0 ; i < msg.getSize() ; i++)
        m_writePacketData[i] = serializedData[i];
    boost::asio::async_write(
            m_tcpSocket,
            boost::asio::buffer(m_writePacketData, msg.getSize()),
            boost::bind(&Client::waitHeader, shared_from_this(), boost::asio::placeholders::error));
}

void Client::sendUdpMessage(const Message& msg) {
    auto serializedData = msg.serialize();
    uint8_t *data = new uint8_t[msg.getSize()];

    for (size_t i = 0 ; i < msg.getSize() ; i++)
        data[i] = serializedData[i];
    m_udpSocket->send_to(boost::asio::buffer(data, PACKET_HDR_SIZE), *m_remoteEndpoint);
    m_udpSocket->send_to(boost::asio::buffer(data + PACKET_HDR_SIZE, msg.getSize() - PACKET_HDR_SIZE), *m_remoteEndpoint);
    delete[] data;
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
    sendTcpMessage(SuccessConnect(m_id));
}

void Client::createGame(const CreateGame *msg) {
    auto lobby = dynamic_cast<Lobby*>(m_handler.get());

    if (lobby == nullptr)
        return;
    std::cout << "Create " << msg->getNickname() << std::endl;
    m_nickname = msg->getNickname();
    auto roomId = lobby->createGameRoom(msg->getName(), 10);
    sendTcpMessage(lobby->getRoomInfo(msg->getName(), msg->getPlayerId()));
    lobby->joinGameRoom(msg->getPlayerId(), roomId);
}

void Client::joinGame(const JoinGame *msg) {
    auto lobby = dynamic_cast<Lobby*>(m_handler.get());

    if (lobby == nullptr)
        return;
    try {
        std::cout << "Join " << msg->getNickname() << std::endl;
        auto roomId = lobby->getRoomId(msg->getName());
        m_nickname = msg->getNickname();
        sendTcpMessage(lobby->getRoomInfo(msg->getName(), msg->getPlayerId()));
        lobby->joinGameRoom(msg->getPlayerId(), roomId);
    } catch (const char *str) {
        std::cerr << str << std::endl; //TODO
    }
}

void Client::sendPlayerJoinGame(size_t playerId, std::string nickname) {
    std::cout << "join player" << std::endl;
    sendTcpMessage(RoomPlayerJoin(playerId, std::move(nickname), true));
}

void Client::sendPlayerQuitGame(size_t playerId) {
    std::cout << "quit player" << std::endl;
    sendTcpMessage(RoomPlayerQuit(playerId, "unknown", true));
}

void Client::sendPlayerState() {
    sendFriendState(m_id, m_position, m_velocity);
}

void Client::sendFriendState(size_t id, const Position& position, const Position& velocity) {
    sendEntityState(id, position, velocity, EntityType::SHIP);
}

void Client::sendEntityState(size_t id, const Position &position, const Position &velocity, EntityType type) {
    pos_t pos = {position.m_x, position.m_y};
    pos_t vel = {velocity.m_x, velocity.m_y};

    sendUdpMessage(EntityState(id, pos, vel, 0, type));
}

void Client::triggerCollision(size_t firstEntity, EntityType firstType,
        size_t secondEntity, EntityType secondType, const Position& pos) {
    pos_t updatePosition = {pos.m_x, pos.m_y};

    sendUdpMessage(CollisionTrigger(firstEntity, firstType, secondEntity, secondType, updatePosition));
}

void Client::startGame() {
    auto localEndpoint = BoostUdp::endpoint(boost::asio::ip::address_v4::any(), m_udpPort);

    std::cout << "start game " << m_udpPort << std::endl;
    sendTcpMessage(GameStart(m_udpPort));
    m_udpSocket = BoostUdp::socket(m_ioService, localEndpoint.protocol());
    m_udpSocket->bind(localEndpoint);
    m_isUdpRunning = true;
    m_thread = boost::thread(&Client::dispatchUdpPackets, shared_from_this());
}

void Client::dispatchUdpPackets() {
    while (m_isUdpRunning)
        receiveUdpPackets();
}

void Client::receiveUdpPackets() {
    packet_header_t hdr = {0, 0, 0};
    uint8_t *data = nullptr;

    m_udpSocket->receive_from(boost::asio::buffer(&hdr, PACKET_HDR_SIZE), *m_remoteEndpoint);
    if (hdr.magic_number != MAGIC_NUMBER || hdr.packet_size == 0)
        return;
    data = new uint8_t[hdr.packet_size];
    m_udpSocket->receive_from(boost::asio::buffer(data, hdr.packet_size), *m_remoteEndpoint);
    m_responsesMutex.lock();
    switch (hdr.packet_id) {
        case FIRE_ENTITY:
            m_udpResponses.push(FireEntity::from(data));
            break;
        case MOVE:
            m_udpResponses.push(DirectionState::from(data));
            break;
        default:
            break;
    }
    m_responsesMutex.unlock();
    delete[] data;
}

std::queue<std::unique_ptr<Message>> Client::getServerResponses() {
    m_responsesMutex.lock();

    auto queue = std::move(m_udpResponses);

    m_udpResponses = std::queue<std::unique_ptr<Message>>();
    m_responsesMutex.unlock();
    return queue;
}

void Client::update() {
    if (!m_isUdpRunning)
        return;

    auto responses = getServerResponses();
    while (!responses.empty()) {
        auto response = responses.front().get();

        handlePacket(*response);
        responses.pop();
    }
}

void Client::handlePacket(const Message& msg) {
    switch (msg.getId()) {
        case FIRE_ENTITY:
            fireEntity(dynamic_cast<const FireEntity&>(msg));
            break;
        case MOVE:
            movePlayer(dynamic_cast<const DirectionState&>(msg));
        default:
            break;
    }
}

void Client::movePlayer(const DirectionState& msg) {
    switch (msg.getDirection()) {
        case RIGHT:
            m_position.m_x += m_velocity.m_x;
            break;
        case LEFT:
            m_position.m_x -= m_velocity.m_x;
            break;
        case TOP:
            m_position.m_y += m_velocity.m_y;
            break;
        case BOTTOM:
            m_position.m_y -= m_velocity.m_y;
            break;
        default:
            break;
    }
}

void Client::fireEntity(const FireEntity& msg) {
    auto gameRoom = dynamic_cast<GameRoom*>(m_handler.get());

    if (gameRoom == nullptr)
        return;
    gameRoom->addBullet(msg.getEntityId(), m_position);
}
