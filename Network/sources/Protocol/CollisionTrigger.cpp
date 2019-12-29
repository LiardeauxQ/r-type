//
// Created by Quentin Liardeaux on 12/29/19.
//

#include "Protocol/CollisionTrigger.hpp"

std::unique_ptr<Message> CollisionTrigger::from(void *data) {
    auto pkt = reinterpret_cast<collision_trigger_t*>(data);
    auto msg = std::make_unique<CollisionTrigger>(
            pkt->first_entity, pkt->second_entity, pkt->position);

    return msg;
}

std::vector<uint8_t> CollisionTrigger::serialize() const {
    std::vector<uint8_t> data = Message::createHeader(m_id, COLLISION_TRIGGER_SIZE);
    collision_trigger_t pkt = {m_firstEntity, m_secondEntity, m_position};

    for (size_t i = 0; i < COLLISION_TRIGGER_SIZE; i++)
        data.push_back(*(reinterpret_cast<uint8_t *>(&pkt) + i));
    return data;
}