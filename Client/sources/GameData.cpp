//
// Created by Quentin Liardeaux on 12/25/19.
//

#include "GameData.hpp"

GameData::GameData(UserData userData)
        : m_gameRunning(false)
        , m_userData(userData)
        , m_idGame(0)
        , m_maxPlayers(0) {}

std::shared_ptr<GameData> GameData::from(const InputOptionsHandler& inputs) {
    try {
        UserData userData(inputs.getServerPort(), inputs.getClientPort(),
                          "0.0.0.0", inputs.getNickname(), inputs.getPassword(),
                          inputs.getSessionName());

        return std::make_shared<GameData>(userData);
    } catch (std::logic_error &error) {
        return nullptr;
    }
}

void GameData::addPlayer(size_t playerId) {
    m_players.push_back(playerId);
}

void GameData::removePlayer(size_t playerId) {
    for (auto it = m_players.begin() ; it != m_players.end() ; it++) {
        if (*it == playerId) {
            m_players.erase(it);
            break;
        }
    }
}

void GameData::updateRoomInfo(size_t idGame, uint8_t maxPlayers) {
    m_idGame = idGame;
    m_maxPlayers = maxPlayers;
}