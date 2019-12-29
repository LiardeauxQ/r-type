//
// Created by Quentin Liardeaux on 12/18/19.
//

#ifndef R_TYPE_TCPCOMMUNICATION_HPP
#define R_TYPE_TCPCOMMUNICATION_HPP

#include <queue>

#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/enable_shared_from_this.hpp>

#include "Protocol/Packet.hpp"
#include "ServerHandler.hpp"
#include "GameData.hpp"

typedef boost::asio::ip::tcp BoostTcp;

class TcpCommunication: public boost::enable_shared_from_this<TcpCommunication> {
public:
    static boost::shared_ptr<TcpCommunication> create(std::shared_ptr<GameData> gameData);
    ~TcpCommunication() = default;

    void start();
    void stop();
    void update();

    void askServerConnection(bool isCreateRoom);
private:
    explicit TcpCommunication(std::shared_ptr<GameData> gameData);

    void sendCreateGame(size_t id, const std::string& name, const std::string& password, const std::string& nickname);
    void sendJoinGame(size_t id, const std::string &name, const std::string& password, const std::string& nickname);
    void connectToServer(uint16_t port, const std::string &addr);

    void checkServerPackets();
    void handlePacket(const Message& msg);
    void roomInfo(const RoomInfo& msg);
    void successConnection(const SuccessConnect& msg);
    void playerHasJoin(const RoomPlayerJoin& msg);
    void playerHasQuit(const RoomPlayerQuit& msg);
    void getPlayerState(const RoomPlayerState& msg);
    void startGame(const GameStart& msg);

    std::queue<std::unique_ptr<Message>> getServerResponses();

    void dispatch();

    volatile bool m_isRunning;
    bool m_isCreateRoom;
    std::shared_ptr<GameData> m_gameData;

    std::queue<std::unique_ptr<Message>> m_responses;

    boost::asio::io_context m_context;
    BoostTcp::socket m_socket;
    boost::thread m_responsesThread;
    boost::mutex m_mutex;

    ServerHandler<BoostTcp::socket> m_handler;
};

#endif //R_TYPE_TCPCOMMUNICATION_HPP
