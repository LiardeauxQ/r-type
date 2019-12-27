//
// Created by Quentin Liardeaux on 12/25/19.
//

#include "GameData.hpp"

GameData::GameData(UserData userData)
        : m_gameRunning(false)
        , m_entityBuilder()
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
    auto it = m_players.find(playerId);
    if (it == m_players.end())
        m_players[playerId] = static_cast<Ship *>(m_entityBuilder.create(EntityType::SHIP));
}

void GameData::removePlayer(size_t playerId) {
    auto it = m_players.find(playerId);
    if (it != m_players.end())
        m_players.erase(it);
}

void GameData::updateRoomInfo(size_t idGame, uint8_t maxPlayers) {
    m_idGame = idGame;
    m_maxPlayers = maxPlayers;
}
