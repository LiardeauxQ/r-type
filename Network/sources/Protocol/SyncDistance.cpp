//
// Created by Quentin Liardeaux on 12/27/19.
//

#include "Protocol/SyncDistance.hpp"

std::unique_ptr<Message> SyncDistance::from(void *data) {
    auto pkt = reinterpret_cast<sync_dist_t*>(data);
    auto msg = std::make_unique<SyncDistance>(pkt->dist);

    return msg;
}

std::vector<uint8_t> SyncDistance::serialize() const {
    std::vector<uint8_t> data = Message::createHeader(m_id, SYNC_DIST_SIZE);
    sync_dist_t pkt = {m_distance};

    for (size_t i = 0; i < SYNC_DIST_SIZE; i++)
        data.push_back(*(reinterpret_cast<uint8_t *>(&pkt) + i));
    return data;
}