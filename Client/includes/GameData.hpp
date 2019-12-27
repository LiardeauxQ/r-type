//
// Created by Quentin Liardeaux on 12/25/19.
//

#ifndef R_TYPE_GAMEDATA_HPP
#define R_TYPE_GAMEDATA_HPP

#include <list>
#include <memory>

#include "UserData.hpp"
#include "InputOptionsHandler.hpp"

class GameData {
public:
    explicit GameData(UserData userData);
    ~GameData() = default;

    static std::shared_ptr<GameData> from(const InputOptionsHandler& inputs);

    void addPlayer(size_t playerId);
    void removePlayer(size_t playerId);
    void updateRoomInfo(size_t idGame, uint8_t maxPlayers);

    void setUserId(size_t userId) { m_userData.m_id = userId; }
    [[nodiscard]] size_t getUserId() const { return m_userData.m_id; }
    [[nodiscard]] const UserData& getUserData() const { return m_userData; }
    [[nodiscard]] size_t getNumberPlayers() const { return m_players.size(); }

    bool m_gameRunning;
private:
    UserData m_userData;
    std::list<size_t> m_players;
    std::list<size_t> m_enemy;
    size_t m_idGame;
    uint8_t m_maxPlayers;
};


#endif //R_TYPE_GAMEDATA_HPP
