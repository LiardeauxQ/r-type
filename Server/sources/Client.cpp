//
// Created by Quentin Liardeaux on 12/19/19.
//

#include "Client.hpp"

static size_t MAX_ID = 0;

boost::shared_ptr<Client> Client::create(boost::asio::io_context &context) {
    return boost::shared_ptr<Client>(new Client(context));
}

Client::Client(boost::asio::io_context& context)
    : m_socket(context)
    , m_packetHeader()
    , m_packetData(nullptr)
    , m_id(MAX_ID++) {}

Client::~Client() {}

void Client::run() {
    waitHeader(boost::system::error_code());
}

void Client::waitHeader(const boost::system::error_code& ec) {
    boost::asio::async_read(
        m_socket,
        boost::asio::buffer(&m_packetHeader, PACKET_HDR_SIZE),
        boost::bind(&Client::receivePacket, shared_from_this(), boost::asio::placeholders::error));
}

void Client::receivePacket(const boost::system::error_code& ec) {
    if (ec)
        return;
    std::cout << "Receive packet" << std::endl;
    if (m_packetData != nullptr)
        delete[] m_packetData;
    m_packetData = new uint8_t[m_packetHeader.packet_size];
    boost::asio::async_read(
            m_socket,
            boost::asio::buffer(m_packetData, m_packetHeader.packet_size),
            boost::bind(&Client::receiveBody, shared_from_this(), boost::asio::placeholders::error));
}

void Client::receiveBody(const boost::system::error_code& ec) {
    std::cout << "Receive body" << std::endl;
    handleRequest(m_packetData, m_packetHeader.packet_id);
    std::cout << "Handle request" << std::endl;
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
}

void Client::createGame(const CreateGame *msg) {
    auto lobby = dynamic_cast<Lobby*>(m_handler.get());

    if (lobby == nullptr)
        return;
    std::cout << msg->getName() << std::endl;
    lobby->createGameRoom(msg->getName(), 10);
}

void Client::joinGame(const JoinGame *msg) {
    auto lobby = dynamic_cast<Lobby*>(m_handler.get());

    if (lobby == nullptr)
        return;
    try {
        std::cout << msg->getName() << std::endl;
        auto roomId = lobby->getRoomId(msg.getName());
        std::cout << roomId << std::endl;
        lobby->joinGameRoom(msg->getPlayerId(), roomId);
        std::cout << "has join" << std::endl;
        sendMessage(lobby->getRoomInfo(msg->getName(), msg->getPlayerId()));
        std::cout << "msg" << std::endl;
    } catch (const char *str) {
        std::cerr << str << std::endl; //TODO
    }
}

void Client::sendMessage(const Message& msg) {
    std::cout << "send " << msg.getSize() << std::endl;
    boost::asio::async_write(
            m_socket,
            boost::asio::buffer(msg.serialize().data(), msg.getSize()),
            boost::bind(&Client::waitHeader, shared_from_this(), boost::asio::placeholders::error));
}