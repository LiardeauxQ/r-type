//
// Created by Quentin Liardeaux on 12/25/19.
//

#ifndef R_TYPE_GAMEDATA_HPP
#define R_TYPE_GAMEDATA_HPP

#include <map>
#include <list>
#include <memory>

#include "EntityBuilder.hpp"
#include "UserData.hpp"
#include "InputOptionsHandler.hpp"

class GameData {
public:
    explicit GameData(UserData userData);
    ~GameData() = default;

    static std::shared_ptr<GameData> from(const InputOptionsHandler& inputs);

    void addPlayer(size_t playerId);
    void removePlayer(size_t playerId);
    std::map<size_t, Ship *> &getPlayers() { return m_players; };

    void addEnemy(size_t enemyId);
    void removeEnemy(size_t enemyId);
    std::map<size_t, Enemy *> &getEnemies() { return m_enemies; };

    void addBullet(size_t bulletId);
    void removeBullet(size_t bulletId);
    std::map<size_t, Bullet *> &getBullets() { return m_bullets; };

    void addExplosion(const pos_t &position);
    void removeExplosions();
    std::list<Explosion *> &getExplosions() { return m_explosions; };

    void updateRoomInfo(size_t idGame, uint8_t maxPlayers);

    void setUserId(size_t userId) { m_userData.m_id = userId; }
    void setRemoteEndpoint(uint16_t port);

    [[nodiscard]] size_t getUserId() const { return m_userData.m_id; }
    [[nodiscard]] const UserData& getUserData() const { return m_userData; }
    [[nodiscard]] size_t getNumberPlayers() const { return m_players.size(); }
    [[nodiscard]] const std::optional<BoostUdp::endpoint>& getRemoteEndpoint() { return m_userData.m_remoteEndpoint; }

    bool m_gameRunning;
private:
    EntityBuilder m_entityBuilder;
    UserData m_userData;
    std::map<size_t, Ship *> m_players;
    std::map<size_t, Enemy *> m_enemies;
    std::map<size_t, Bullet *> m_bullets;
    std::list<Explosion *> m_explosions;
    size_t m_idGame;
    uint8_t m_maxPlayers;
};


#endif //R_TYPE_GAMEDATA_HPP
