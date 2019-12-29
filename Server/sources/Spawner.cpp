//
// Created by Quentin Liardeaux on 12/29/19.
//

#include "Spawner.hpp"

Spawner::Spawner(Position position, Position velocity, size_t id)
    : Entity(id, position, velocity)
    , m_service()
    , m_timer(m_service, boost::posix_time::seconds(1))
    , m_isRunning(true) {
    m_timer.async_wait(boost::bind(&Spawner::createEnemy, this, boost::system::error_code()));
    m_thread = boost::thread(boost::bind(&boost::asio::io_service::run, &m_service));
}

void Spawner::update(float elapsedTime) {
    for (auto it = m_enemies.begin() ; it != m_enemies.end() ;) {
        if (it->second->getPosition().m_x < -30) {
            delete it->second;
            m_enemies.erase(it++);
        } else {
            it->second->move(LEFT, elapsedTime);
            it++;
        }
    }
}

void Spawner::stop() {
    m_isRunning = false;
    m_thread.join();
}

void Spawner::createEnemy(const boost::system::error_code& ec) {
    if (ec || !m_isRunning)
        return;
    auto id = IdProvider::instance()->getNextId();
    m_enemies[id] = new Enemy(id, m_position, m_velocity);
    m_timer.expires_at(m_timer.expires_at() + boost::posix_time::seconds(1));
    m_timer.async_wait(boost::bind(&Spawner::createEnemy, this, boost::system::error_code()));
}

std::tuple<bool, size_t> Spawner::isCollideWith(const Position& pos) {
    std::tuple<bool, size_t> result(false, 0);

    for (auto enemy = m_enemies.begin() ; enemy != m_enemies.end() ; enemy++) {
        auto otherPos = enemy->second->getPosition();
        if (pos.m_x > otherPos.m_x - BOX_SIZE && pos.m_x < otherPos.m_x + BOX_SIZE &&
            pos.m_y > otherPos.m_y - BOX_SIZE && pos.m_y < otherPos.m_y + BOX_SIZE) {
            result = std::make_tuple<bool, size_t>(true, enemy->second->getId());
            delete enemy->second;
            m_enemies.erase(enemy);
            break;
        }
    }
    return result;
}