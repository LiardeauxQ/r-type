//
// Created by Quentin Liardeaux on 12/18/19.
//

#include "Protocol/ClientConnect.hpp"

std::unique_ptr<Message> ClientConnect::from(void *data) {
    auto pkt = reinterpret_cast<client_connect_t*>(data);
    auto msg = std::make_unique<ClientConnect>(pkt->port,
            std::string(reinterpret_cast<char *>(pkt->address)));

    return msg;
}

std::vector<uint8_t> ClientConnect::serialize() const {
    std::vector<uint8_t> data = Message::createHeader(m_id, CLIENT_CONNECT_SIZE);
    client_connect_t pkt = {m_port, {0}};

    for (size_t i = 0; i < m_addr.size() && i < PORT_SIZE; i++)
        pkt.address[i] = static_cast<uint8_t>(*(m_addr.c_str() + i));
    for (size_t i = 0; i < JOIN_GAME_SIZE; i++)
        data.push_back(*(reinterpret_cast<uint8_t *>(&pkt) + i));
    return data;
}