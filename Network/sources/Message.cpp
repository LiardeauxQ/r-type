//
// Created by Quentin Liardeaux on 12/17/19.
//

#include "includes/Message.hpp"

std::vector<uint8_t> Message::createHeader(uint8_t id, uint16_t packet_size) {
    packet_header_t hdr{MAGIC_NUMBER, id, packet_size};
    std::vector<uint8_t> data;

    for (size_t i = 0; i < PACKET_HDR_SIZE; i++)
        data.push_back(*(reinterpret_cast<uint8_t *>(&hdr) + i));
    return data;
}