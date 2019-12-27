//
// Created by Quentin Liardeaux on 12/27/19.
//

#include "Protocol/EntityState.hpp"

std::unique_ptr<Message> EntityState::from(void *data) {
    auto pkt = reinterpret_cast<state_entity_t*>(data);
    auto msg = std::make_unique<EntityState>(pkt->id_entity, pkt->position,
            pkt->velocity, pkt->angle);

    return msg;
}

std::vector<uint8_t> EntityState::serialize() const {
    std::vector<uint8_t> data = Message::createHeader(m_id, STATE_ENTITY_SIZE);
    state_entity_t pkt = {m_entityId, m_position, m_velocity, m_angle};

    for (size_t i = 0; i < STATE_ENTITY_SIZE; i++)
        data.push_back(*(reinterpret_cast<uint8_t *>(&pkt) + i));
    return data;
}