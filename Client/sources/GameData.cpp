//
// Created by Quentin Liardeaux on 12/25/19.
//

#include "GameData.hpp"

GameData::GameData(UserData userData)
        : m_gameRunning(false)
        , m_userData(userData) {}

GameData GameData::from(const InputOptionsHandler& inputs) {
    UserData userData(inputs.getServerPort(), inputs.getClientPort(),
            "0.0.0.0", inputs.getNickname(), inputs.getPassword(),
            inputs.getSessionName());

    return GameData(userData);
}

void GameData::addPlayer(uint8_t playerId) {
    m_players.push_back(playerId);
}

void GameData::removePlayer(uint8_t playerId) {
    for (auto it = m_players.begin() ; it != m_players.end() ; it++) {
        if (*it == playerId) {
            m_players.erase(it);
            break;
        }
    }
}