//
// Created by Quentin Liardeaux on 12/18/19.
//

#include "TcpCommunication.hpp"

boost::shared_ptr<TcpCommunication> TcpCommunication::create(std::shared_ptr<GameData> gameData) {
    return boost::shared_ptr<TcpCommunication>(new TcpCommunication(std::move(gameData)));
}

TcpCommunication::TcpCommunication(std::shared_ptr<GameData> gameData)
        : m_isRunning(false)
        , m_isCreateRoom(false)
        , m_gameData(std::move(gameData))
        , m_responses()
        , m_context()
        , m_socket(m_context)
        , m_mutex()
        , m_handler(m_gameData->getUserData(), m_socket) {
}

void TcpCommunication::start() {
    m_socket.connect(BoostTcp::endpoint(
            boost::asio::ip::address::from_string(
                    m_gameData->getUserData().getRemoteIpAddress()),
                    m_gameData->getUserData().getServerPort()));
    m_isRunning = true;
    m_responsesThread = boost::thread(&TcpCommunication::dispatch, this);
}

void TcpCommunication::stop() {
    m_isRunning = false;
    try {
        m_socket.shutdown(m_socket.shutdown_both);
    } catch (const boost::exception& e) {
        m_socket.close();
    }
    m_responsesThread.join();
}

void TcpCommunication::update() {
   checkServerPackets();
}

void TcpCommunication::askServerConnection(bool isCreateRoom) {
    std::cout << "is create " << isCreateRoom << std::endl;
    m_isCreateRoom = isCreateRoom;
    connectToServer(m_gameData->getUserData().getUserPort(),
            m_gameData->getUserData().getLocalIpAddress());
}

void TcpCommunication::sendCreateGame(size_t id, const std::string& name, const std::string& password, const std::string& nickname) {
    auto message = CreateGame(id, name, password, nickname);

    std::cout << "send create" << std::endl;
    m_handler.sendMessage(message);
}

void TcpCommunication::sendJoinGame(size_t id, const std::string &name, const std::string& password, const std::string& nickname) {
    auto message = JoinGame(id, name, password, nickname);

    std::cout << "send join" << std::endl;
    m_handler.sendMessage(message);
}

void TcpCommunication::connectToServer(uint16_t port, const std::string &addr) {
    auto message = ClientConnect(port, addr);

    m_handler.sendMessage(message);
}

void TcpCommunication::dispatch() {
    while (m_isRunning) {
        try {
            auto msg = m_handler.receiveMessage();
            if (msg == nullptr)
                continue;
            m_mutex.lock();
            m_responses.push(std::move(msg));
            m_mutex.unlock();
        } catch (const boost::exception& e) {
            std::cerr << "Error while receiving message." << std::endl;
        }
    }
}

std::queue<std::unique_ptr<Message>> TcpCommunication::getServerResponses() {
    m_mutex.lock();

    auto queue = std::move(m_responses);

    m_responses = std::queue<std::unique_ptr<Message>>();
    m_mutex.unlock();
    return queue;
}

void TcpCommunication::checkServerPackets()
{
    auto responses = getServerResponses();

    while (!responses.empty()) {
        auto response = responses.front().get();

        handlePacket(*response);
        responses.pop();
    }
}

void TcpCommunication::handlePacket(const Message& msg)
{
    switch (msg.getId()) {
        case ROOM_INFO:
            roomInfo(dynamic_cast<const RoomInfo&>(msg));
            break;
        case SUCCESS_CONNECT:
            successConnection(dynamic_cast<const SuccessConnect&>(msg));
            break;
        case ERROR:
            break;
        case ROOM_PLAYER_JOIN:
            playerHasJoin(dynamic_cast<const RoomPlayerJoin&>(msg));
            break;
        case ROOM_PLAYER_QUIT:
            playerHasQuit(dynamic_cast<const RoomPlayerQuit&>(msg));
            break;
        case ROOM_PLAYER_STATE:
            getPlayerState(dynamic_cast<const RoomPlayerState&>(msg));
            break;
        case GAME_START:
            startGame(dynamic_cast<const GameStart&>(msg));
            break;
        default:
            break;
    }
}

void TcpCommunication::roomInfo(const RoomInfo& msg) {
    std::cout << "Room info " << msg.getIdPlayer() << " " << m_gameData->getUserId() << std::endl;
    if (msg.getIdPlayer() != m_gameData->getUserId())
        return;
    m_gameData->addPlayer(msg.getIdPlayer());
    m_gameData->updateRoomInfo(msg.getIdGame(), msg.getMaxPlayers());
}

void TcpCommunication::successConnection(const SuccessConnect& msg) {
    auto sessionName = m_gameData->getUserData().getRoomName();
    auto password = m_gameData->getUserData().getPassword();
    auto nickname = m_gameData->getUserData().getNickname();

    m_gameData->setUserId(msg.getId());
    std::cout << "Success connect " << (int)(msg.getId()) << "<-" << std::endl;
    if (m_isCreateRoom) {
        sendCreateGame(msg.getId(), sessionName, password, nickname);
    } else {
        sendJoinGame(msg.getId(), sessionName, password, nickname);
    }
}

void TcpCommunication::playerHasJoin(const RoomPlayerJoin &msg) {
    std::cout << "Join player " << msg.getNickname() << msg.getSize() << std::endl;
    m_gameData->addPlayer(msg.getIdPlayer());
}

void TcpCommunication::playerHasQuit(const RoomPlayerQuit &msg) {
    std::cout << "Quit player " << msg.getNickname() << std::endl;
    m_gameData->removePlayer(msg.getIdPlayer());
}

void TcpCommunication::getPlayerState(const RoomPlayerState &msg) {}

void TcpCommunication::startGame(const GameStart &msg) {
    std::cout << "Start game" << std::endl;
    m_gameData->setRemoteEndpoint(msg.getUdpPort());
    m_gameData->m_gameRunning = true;
}

