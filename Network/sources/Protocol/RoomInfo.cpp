//
// Created by Quentin Liardeaux on 12/18/19.
//

#include "Protocol/RoomInfo.hpp"

RoomInfo::RoomInfo(void *data) : Message(ROOM_INFO) {
    auto pkt = reinterpret_cast<room_info_t*>(data);

    m_idGame = pkt->id_game;
    m_name = std::string(reinterpret_cast<char*>(pkt->name));
    m_nbPlayers = pkt->nb_players;
    m_maxPlayers = pkt->max_players;
    m_idPlayer = pkt->id_player;
}

std::vector<uint8_t> RoomInfo::serialize() const {
    std::vector<uint8_t> data = Message::createHeader(m_id, ROOM_INFO_SIZE);
    room_info_t pkt = {m_idGame, {0}, m_nbPlayers, m_maxPlayers, m_idPlayer};

    for (size_t i = 0; i < m_name.size() && i < MAX_BUFFER_SIZE; i++)
        pkt.name[i] = static_cast<uint8_t>(*(m_name.c_str() + i));
    for (size_t i = 0; i < ROOM_INFO_SIZE; i++)
        data.push_back(*(reinterpret_cast<uint8_t *>(&pkt) + i));
    return data;
}