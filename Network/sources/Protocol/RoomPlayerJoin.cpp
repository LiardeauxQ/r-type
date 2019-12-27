//
// Created by Quentin Liardeaux on 12/18/19.
//

#include "Protocol/RoomPlayerJoin.hpp"
#include <iostream>

std::unique_ptr<Message> RoomPlayerJoin::from(void *data) {
    auto pkt = reinterpret_cast<room_player_join_t*>(data);
    auto msg = std::make_unique<RoomPlayerJoin>(
            pkt->id_player,
            std::string(reinterpret_cast<char *>(pkt->nickname)),
            pkt->is_ready);

    return msg;
}

std::vector<uint8_t> RoomPlayerJoin::serialize() const {
    std::vector<uint8_t> data = Message::createHeader(m_id, ROOM_PLAYER_JOIN_SIZE);
    room_player_join_t pkt = {m_idPlayer, {0}, m_isReady};

    std::cout << "nickname " << m_nickname << std::endl;
    for (size_t i = 0; i < m_nickname.size() && i < MAX_BUFFER_SIZE; i++)
        pkt.nickname[i] = static_cast<uint8_t>(*(m_nickname.c_str() + i));
    for (size_t i = 0; i < ROOM_PLAYER_JOIN_SIZE; i++)
        data.push_back(*(reinterpret_cast<uint8_t *>(&pkt) + i));
    return data;
}