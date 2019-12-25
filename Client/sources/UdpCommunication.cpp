//
// Created by Quentin Liardeaux on 12/25/19.
//

#include "UdpCommunication.hpp"

UdpCommunication::UdpCommunication(std::shared_ptr<GameData> gameData)
        : m_isRunning(false)
        , m_gameData(std::move(gameData))
        , m_responses()
        , m_context()
        , m_socket(m_context)
        , m_mutex() {
}

void UdpCommunication::start() {
    if (m_isRunning)
        return;
    m_socket.connect(BoostUdp::endpoint(
            boost::asio::ip::address::from_string(
                    m_gameData->getUserData().getIpAddress()),
            m_gameData->getUserData().getServerPort()));
    m_isRunning = true;
    m_responsesThread = boost::thread(&UdpCommunication::dispatch, this);
}

void UdpCommunication::stop() {
    m_isRunning = false;
    m_responsesThread.join();
    m_socket.close();
}

void UdpCommunication::update() {
    checkServerPackets();
}

void UdpCommunication::dispatch() {
    /*while (m_isRunning) {
        auto msg = m_handler.receiveMessage();
        m_mutex.lock();
        m_responses.push(std::move(msg));
        m_mutex.unlock();
    }*/
}

std::queue<std::unique_ptr<Message>> UdpCommunication::getServerResponses() {
    m_mutex.lock();

    auto queue = std::move(m_responses);

    m_responses = std::queue<std::unique_ptr<Message>>();
    m_mutex.unlock();
    return queue;
}

void UdpCommunication::checkServerPackets()
{
    auto responses = getServerResponses();

    while (!responses.empty()) {
        auto response = responses.front().get();

        handlePacket(*response);
        responses.pop();
    }
}

void UdpCommunication::handlePacket(const Message& msg)
{
    switch (msg.getId()) {

        default:
            break;
    }
}
