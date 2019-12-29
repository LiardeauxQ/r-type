//
// Created by Quentin Liardeaux on 12/29/19.
//

#include "Protocol/ErrorPacket.hpp"

std::unique_ptr<Message> ErrorPacket::from(void *data) {
    auto pkt = reinterpret_cast<server_error_t*>(data);
    auto msg = std::make_unique<ErrorPacket>(static_cast<ERROR_CODE>(pkt->error_code));

    return msg;
}

std::vector<uint8_t> ErrorPacket::serialize() const {
    std::vector<uint8_t> data = Message::createHeader(m_id, ERROR_SIZE);
    server_error_t pkt = {0, static_cast<uint8_t>(m_code)};

    for (size_t i = 0; i < ERROR_SIZE; i++)
        data.push_back(*(reinterpret_cast<uint8_t *>(&pkt) + i));
    return data;
}