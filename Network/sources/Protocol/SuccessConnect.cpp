//
// Created by Quentin Liardeaux on 12/23/19.
//

#include "Protocol/SuccessConnect.hpp"

std::unique_ptr<Message> SuccessConnect::from(void *data) {
    auto pkt = reinterpret_cast<success_connect_t*>(data);
    auto msg = std::make_unique<SuccessConnect>(pkt->id_player);

    return msg;
}

std::vector<uint8_t> SuccessConnect::serialize() const {
    std::vector<uint8_t> data = Message::createHeader(m_id, SUCCESS_CONNECT_SIZE);
    success_connect_t pkt = {m_idPlayer};

    for (size_t i = 0; i < SUCCESS_CONNECT_SIZE; i++)
        data.push_back(*(reinterpret_cast<uint8_t *>(&pkt) + i));
    return data;
}