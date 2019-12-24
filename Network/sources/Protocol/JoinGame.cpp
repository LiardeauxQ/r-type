//
// Created by alex on 11/12/19.
//

#include "Protocol/JoinGame.hpp"

std::unique_ptr<Message> JoinGame::from(void *data) {
    auto pkt = reinterpret_cast<join_game_t*>(data);
    auto msg = std::make_unique<JoinGame>(
            pkt->id_player,
            std::string(reinterpret_cast<char*>(pkt->name)),
            std::string(reinterpret_cast<char *>(pkt->password)),
            std::string(reinterpret_cast<char *>(pkt->nickname)));

    return msg;
}

std::vector<uint8_t> JoinGame::serialize() const {
    std::vector<uint8_t> data = Message::createHeader(m_id, JOIN_GAME_SIZE);
    join_game_t pkt = {m_idPlayer, {0}, {0}, {0}};

    for (size_t i = 0; i < m_name.size() && i < MAX_BUFFER_SIZE; i++)
        pkt.name[i] = static_cast<uint8_t>(*(m_name.c_str() + i));
    for (size_t i = 0; i < m_password.size() && i < MAX_BUFFER_SIZE; i++)
        pkt.password[i] = static_cast<uint8_t>(*(m_password.c_str() + i));
    for (size_t i = 0; i < m_nickname.size() && i < MAX_BUFFER_SIZE; i++)
        pkt.nickname[i] = static_cast<uint8_t>(*(m_nickname.c_str() + i));
    for (size_t i = 0; i < JOIN_GAME_SIZE; i++)
        data.push_back(*(reinterpret_cast<uint8_t *>(&pkt) + i));
    return data;
}