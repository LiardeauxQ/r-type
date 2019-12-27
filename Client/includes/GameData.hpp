//
// Created by Quentin Liardeaux on 12/25/19.
//

#ifndef R_TYPE_GAMEDATA_HPP
#define R_TYPE_GAMEDATA_HPP

#include <map>
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
    std::map<size_t, Ship *> &getPlayers() { return m_players; };
    void removePlayer(size_t playerId);
    void updateRoomInfo(size_t idGame, uint8_t maxPlayers);

    void setUserId(size_t userId) { m_userData.m_id = userId; }
    [[nodiscard]] size_t getUserId() const { return m_userData.m_id; }
    [[nodiscard]] const UserData& getUserData() const { return m_userData; }
    [[nodiscard]] size_t getNumberPlayers() const { return m_players.size(); }

    bool m_gameRunning;
private:
    EntityBuilder m_entityBuilder;
    UserData m_userData;
    std::map<size_t, Ship *> m_players;
    std::map<size_t, Enemy *> m_enemies;
    size_t m_idGame;
    uint8_t m_maxPlayers;
};


#endif //R_TYPE_GAMEDATA_HPP
