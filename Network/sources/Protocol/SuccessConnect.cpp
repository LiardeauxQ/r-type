//
// Created by Quentin Liardeaux on 12/23/19.
//

#include "Protocol/SuccessConnect.hpp"

SuccessConnect::SuccessConnect(void *data) : Message(SUCCESS_CONNECT) {
    auto pkt = reinterpret_cast<success_connect_t*>(data);

    m_id = pkt->id_player;
}

std::vector<uint8_t> SuccessConnect::serialize() const {
    std::vector<uint8_t> data = Message::createHeader(m_id, SUCCESS_CONNECT_SIZE);
    client_connect_t pkt = {m_idPlayer};

    return data;
}