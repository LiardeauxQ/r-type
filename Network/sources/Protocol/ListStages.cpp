//
// Created by Quentin Liardeaux on 12/18/19.
//

#include "Protocol/ListStages.hpp"

std::unique_ptr<Message> ListStages::from(void *data) {
    auto msg = std::make_unique<ListStages>();

    return msg;
}

std::vector<uint8_t> ListStages::serialize() const {
    std::vector<uint8_t> data = Message::createHeader(m_id, LIST_STAGES_SIZE);
    list_stages_t pkt = {0};

    for (size_t i = 0; i < LIST_STAGES_SIZE; i++)
        data.push_back(*(reinterpret_cast<uint8_t *>(&pkt) + i));
    return data;
}