//
// Created by Quentin Liardeaux on 12/29/19.
//

#ifndef R_TYPE_SPAWNER_HPP
#define R_TYPE_SPAWNER_HPP

#include <map>
#include <tuple>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>

#include "Enemy.hpp"
#include "IdProvider.hpp"

#define BOX_SIZE 30

class Spawner: public Entity {
public:
    explicit Spawner(Position position, Position velocity = Position(300, 0), size_t id = 0);
    ~Spawner() override = default;

    void update(float elapsedTime);
    void stop();

    std::tuple<bool, size_t> isCollideWith(const Position& pos);

    [[nodiscard]] const std::map<size_t, Enemy*>& getEnemies() const { return m_enemies; }
private:
    void createEnemy(const boost::system::error_code& ec);

    boost::asio::io_service m_service;
    boost::asio::deadline_timer m_timer;
    bool m_isRunning;
    std::map<size_t, Enemy*> m_enemies;
    boost::thread m_thread;
};


#endif //R_TYPE_SPAWNER_HPP
