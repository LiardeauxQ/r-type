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
    GameData(UserData userData);
    ~GameData() = default;

    static GameData from(const InputOptionsHandler& inputs);

    void addPlayer(uint8_t playerId);
    void removePlayer(uint8_t playerId);

    void setUserId(uint8_t userId) { m_userData.m_id = userId; }
    [[nodiscard]] const UserData& getUserData() const { return m_userData; }

    bool m_gameRunning;
private:
    UserData m_userData;
    std::list<uint8_t> m_players;
    std::list<uint8_t> m_enemy;
};


#endif //R_TYPE_GAMEDATA_HPP
