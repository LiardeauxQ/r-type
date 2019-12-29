//
// Created by Quentin Liardeaux on 12/25/19.
//

#include "UdpCommunication.hpp"

boost::shared_ptr<UdpCommunication> UdpCommunication::create(std::shared_ptr<GameData> gameData) {
    return boost::shared_ptr<UdpCommunication>(new UdpCommunication(std::move(gameData)));
}

UdpCommunication::UdpCommunication(std::shared_ptr<GameData> gameData)
        : m_isRunning(false)
        , m_gameData(std::move(gameData))
        , m_responses()
        , m_ioService()
        , m_socket(m_ioService)
        , m_mutex() {
}

void UdpCommunication::start() {
    if (m_isRunning)
        return;
    m_socket.open(BoostUdp::v4());
    m_socket.bind(m_gameData->getUserData().getLocalEndpoint());
    m_isRunning = true;

    m_responsesThread = boost::thread(&UdpCommunication::dispatch, shared_from_this());
}

void UdpCommunication::stop() {
    m_isRunning = false;
    m_socket.close();
    m_responsesThread.join();
}

void UdpCommunication::update() {
    checkServerPackets();
}

void UdpCommunication::dispatch() {
    while (m_isRunning) {
        try {
            auto msg = receiveMessage();
            if (msg == nullptr)
                continue;
            m_mutex.lock();
            m_responses.push(std::move(msg));
            m_mutex.unlock();
        } catch (const boost::exception& e) {
            std::cerr << "Error while receiving udp packet." << std::endl;
        }
    }
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
        case STATE_ENTITY:
            receiveEntityState(dynamic_cast<const EntityState&>(msg));
            break;
        case SYNC_DIST:
            receiveSyncDistance(dynamic_cast<const SyncDistance&>(msg));
            break;
        case COLLISION_TRIGGER:
            handleCollision(dynamic_cast<const CollisionTrigger&>(msg));
        default:
            break;
    }
}

void UdpCommunication::receiveSyncDistance(const SyncDistance& msg) {
    std::cout << "receive sync distance" << std::endl;
}

void UdpCommunication::receiveEntityState(const EntityState &msg) {
    switch (msg.getType()) {
        case SHIP:
            handlePlayerState(msg);
            break;
        case ENEMY:
            handleEnemyState(msg);
            break;
        case BULLET:
            handleBulletState(msg);
            break;
        default:
            break;
    }
}

void UdpCommunication::handlePlayerState(const EntityState& msg) {
    auto pos = msg.getPosition();

    try {
        auto player = m_gameData->getPlayers().at(msg.getEntityId());

        player->m_position.x = static_cast<float>(pos.x);
        player->m_position.y = static_cast<float>(pos.y);
    } catch (const std::out_of_range& e) {
        std::cerr << "Cannot find player with id " << msg.getEntityId() << std::endl;
    }
}

void UdpCommunication::handleEnemyState(const EntityState& msg) {
    auto pos = msg.getPosition();

    std::cout << "receive enemy " << pos.x << " " << pos.y << std::endl;
    try {
        auto enemy = m_gameData->getEnemies().at(msg.getEntityId());

        enemy->m_position.x = static_cast<float>(pos.x);
        enemy->m_position.y = static_cast<float>(pos.y);
    } catch (const std::out_of_range& e) {
        m_gameData->addEnemy(msg.getEntityId());
        handleEnemyState(msg);
    }
}

void UdpCommunication::handleBulletState(const EntityState& msg) {
    auto pos = msg.getPosition();

    try {
        auto bullet = m_gameData->getBullets().at(msg.getEntityId());

        bullet->m_position.x = static_cast<float>(pos.x);
        bullet->m_position.y = static_cast<float>(pos.y);
        bullet->setPosition(bullet->m_position);
    } catch (const std::out_of_range& e) {
        std::cerr << "Cannot find bullet with id " << msg.getEntityId() << std::endl;
    }
}

void UdpCommunication::handleCollision(const CollisionTrigger &msg) {}

void UdpCommunication::playerMove(float x, float y) {
    Direction dir = RIGHT;

    if (x == 0 && y == 0)
        return;
    if (x < 0) {
        dir = LEFT;
    } else if (y < 0) {
        dir = BOTTOM;
    } else if (y > 0) {
        dir = TOP;
    }
    sendMessage(DirectionState(dir));
}

void UdpCommunication::playerShot() {
    if (!m_gameData->getPlayers()[m_gameData->getUserId()]->isShotReady())
        return;
    auto bulletId = IdProvider::instance()->getNextId();
    m_gameData->addBullet(bulletId);
    sendMessage(FireEntity(bulletId,FireType::NORMAL));
}

void UdpCommunication::sendMessage(const Message& msg) {
    if (auto endpoint = m_gameData->getRemoteEndpoint()) {
        uint8_t *data = new uint8_t[msg.getSize()];
        auto serializedData = msg.serialize();

        for (size_t i = 0; i < msg.getSize(); i++)
            data[i] = serializedData[i];
        try {
            m_socket.send_to(boost::asio::buffer(data, PACKET_HDR_SIZE), *endpoint);
            m_socket.send_to(boost::asio::buffer(data + PACKET_HDR_SIZE, msg.getSize() - PACKET_HDR_SIZE), *endpoint);
        } catch (const boost::exception& e) {
            std::cerr << "Error while sending udp packet." << std::endl;
        }
        delete[] data;
    }
}

std::unique_ptr<Message> UdpCommunication::createMessage() {
    boost::asio::ip::udp::endpoint endpoint;
    packet_header_t hdr = {0, 0, 0};
    uint8_t *data = nullptr;
    std::unique_ptr<Message> msg = nullptr;

    m_socket.receive_from(boost::asio::buffer(&hdr, PACKET_HDR_SIZE), endpoint);
    if (hdr.magic_number != MAGIC_NUMBER || hdr.packet_size == 0)
        return nullptr;
    data = new uint8_t[hdr.packet_size];
    m_socket.receive_from(boost::asio::buffer(data, hdr.packet_size), endpoint);
    switch (hdr.packet_id) {
        case STATE_ENTITY:
            msg = EntityState::from(data);
            break;
        case SYNC_DIST:
            msg = SyncDistance::from(data);
            break;
        case COLLISION_TRIGGER:
            msg = CollisionTrigger::from(data);
            break;
        default:
            break;
    }
    delete[] data;
    return msg;
}

std::unique_ptr<Message> UdpCommunication::receiveMessage() {
    return createMessage();
}
