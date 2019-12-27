//
// Created by Quentin Liardeaux on 12/18/19.
//

#include "Protocol/PlayerInfo.hpp"

std::unique_ptr<Message> PlayerInfo::from(void *data) {
    auto pkt = reinterpret_cast<player_info_t*>(data);
    auto msg = std::make_unique<PlayerInfo>(
            pkt->id_player,
            std::string(reinterpret_cast<char *>(pkt->nickname)),
            pkt->is_ready);

    return msg;
}

std::vector<uint8_t> PlayerInfo::serialize() const {
    std::vector<uint8_t> data = Message::createHeader(m_id, PLAYER_INFO_SIZE);
    player_info_t pkt = {m_idPlayer, {0}, m_isReady};

    for (size_t i = 0; i < m_nickname.size() && i < MAX_BUFFER_SIZE; i++)
        pkt.nickname[i] = static_cast<uint8_t>(*(m_nickname.c_str() + i));
    for (size_t i = 0; i < PLAYER_INFO_SIZE; i++)
        data.push_back(*(reinterpret_cast<uint8_t *>(&pkt) + i));
    return data;
}