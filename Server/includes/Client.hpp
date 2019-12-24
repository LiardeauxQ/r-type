//
// Created by Quentin Liardeaux on 12/19/19.
//

#ifndef R_TYPE_CLIENT_HPP
#define R_TYPE_CLIENT_HPP

#include <string>

#include "protocol.hpp"
#include "Message.hpp"
#include "Protocol/Packet.hpp"
#include "ClientHandler.hpp"
#include "GameRoom.hpp"
#include "Lobby.hpp"

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>

typedef boost::asio::ip::tcp BoostTcp;

class ClientHandler;
class GameRoom;
class Lobby;

class Client : public boost::enable_shared_from_this<Client> {
public:
    static boost::shared_ptr<Client> create(boost::asio::io_context &context);

    void waitHeader(const boost::system::error_code &ec);

    void receivePacket(const boost::system::error_code &ec);

    void receiveBody(const boost::system::error_code &ec);

    std::unique_ptr<Message> handleRequest(uint8_t *data, uint16_t packetId);
    void dispatchPackets(const Message* msg);

    void sendMessage(const Message& msg);

    void run();

    void connectClient(const ClientConnect* msg);

    void createGame(const CreateGame* msg);

    void joinGame(const JoinGame* msg);

    BoostTcp::socket &getSocket() { return m_socket; }

    size_t getId() const { return m_id; }

    void setHandler(boost::shared_ptr<ClientHandler> handler) { m_handler = handler; }

    ~Client();

private:
    explicit Client(boost::asio::io_context &context);

    BoostTcp::socket m_socket;
    packet_header_t m_packetHeader;
    uint8_t *m_packetData;
    boost::shared_ptr<ClientHandler> m_handler;
    size_t m_id;
};

#endif //R_TYPE_CLIENT_HPP
