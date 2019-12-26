//
// Created by Quentin Liardeaux on 12/25/19.
//

#ifndef R_TYPE_GAMEDATA_HPP
#define R_TYPE_GAMEDATA_HPP

#include <list>

#include "UserData.hpp"
#include "InputOptionsHandler.hpp"

class GameData {
public:
    explicit GameData(UserData userData);
    ~GameData() = default;

    static std::shared_ptr<GameData> from(const InputOptionsHandler& inputs);

    void addPlayer(uint8_t playerId);
    void removePlayer(uint8_t playerId);
    void updateRoomInfo(uint32_t idGame, uint8_t maxPlayers);

    void setUserId(uint8_t userId) { m_userData.m_id = userId; }
    [[nodiscard]] uint8_t getUserId() const { return m_userData.m_id; }
    [[nodiscard]] const UserData& getUserData() const { return m_userData; }
    [[nodiscard]] size_t getNumberPlayers() const { return m_players.size(); }

    bool m_gameRunning;
private:
    UserData m_userData;
    std::list<uint8_t> m_players;
    std::list<uint8_t> m_enemy;
    uint32_t m_idGame;
    uint8_t m_maxPlayers;
};


#endif //R_TYPE_GAMEDATA_HPP
