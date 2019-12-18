//
// Created by Quentin Liardeaux on 12/18/19.
//

#include "includes/Protocol/GameStart.hpp"

GameStart::GameStart(void *data) : Message(GAME_START) {
    auto pkt = reinterpret_cast<game_start_t*>(data);

    m_udp_port = pkt->udp_port;
}

std::vector<uint8_t> GameStart::serialize() const {
    std::vector<uint8_t> data = Message::createHeader(m_id, GAME_START_SIZE);
    game_start_t pkt = {m_udp_port};

    for (size_t i = 0; i < GAME_START_SIZE; i++)
        data.push_back(*(reinterpret_cast<uint8_t *>(&pkt) + i));
    return data;
}