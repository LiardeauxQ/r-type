//
// Created by Quentin Liardeaux on 12/27/19.
//

#include "Protocol/FireEntity.hpp"

std::unique_ptr<Message> FireEntity::from(void *data) {
    auto pkt = reinterpret_cast<fire_entity_t*>(data);
    auto msg = std::make_unique<FireEntity>(pkt->id_new_entity, pkt->type);

    return msg;
}

std::vector<uint8_t> FireEntity::serialize() const {
    std::vector<uint8_t> data = Message::createHeader(m_id, FIRE_ENTITY_SIZE);
    fire_entity_t pkt = {m_entityId, m_type};

    for (size_t i = 0; i < FIRE_ENTITY_SIZE; i++)
        data.push_back(*(reinterpret_cast<uint8_t *>(&pkt) + i));
    return data;
}