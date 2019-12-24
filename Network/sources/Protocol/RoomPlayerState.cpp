//
// Created by Quentin Liardeaux on 12/18/19.
//

#include "Protocol/RoomPlayerState.hpp"

std::unique_ptr<Message> RoomPlayerState::from(void *data) {
    auto pkt = reinterpret_cast<room_player_state_t*>(data);
    auto msg = std::make_unique<RoomPlayerState>(
            pkt->id_player,
            std::string(reinterpret_cast<char *>(pkt->nickname)),
            pkt->is_ready);

    return msg;
}

std::vector<uint8_t> RoomPlayerState::serialize() const {
    std::vector<uint8_t> data = Message::createHeader(m_id, ROOM_PLAYER_STATE);
    room_player_state_t pkt = {m_idPlayer, {0}, m_isReady};

    for (size_t i = 0; i < m_nickname.size() && i < MAX_BUFFER_SIZE; i++)
        pkt.nickname[i] = static_cast<uint8_t>(*(m_nickname.c_str() + i));
    for (size_t i = 0; i < JOIN_GAME_SIZE; i++)
        data.push_back(*(reinterpret_cast<uint8_t *>(&pkt) + i));
    return data;
}