//
// Created by Quentin Liardeaux on 12/27/19.
//

#include "Protocol/DirectionState.hpp"

std::unique_ptr<Message> DirectionState::from(void *data) {
    auto pkt = reinterpret_cast<move_t*>(data);
    auto msg = std::make_unique<DirectionState>(pkt->dir);

    return msg;
}

std::vector<uint8_t> DirectionState::serialize() const {
    std::vector<uint8_t> data = Message::createHeader(m_id, MOVE_SIZE);
    move_t pkt = {m_direction};

    for (size_t i = 0; i < MOVE_SIZE; i++)
        data.push_back(*(reinterpret_cast<uint8_t *>(&pkt) + i));
    return data;
}