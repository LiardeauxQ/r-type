//
// Created by Quentin Liardeaux on 12/18/19.
//

#include "Protocol/ListGames.hpp"

std::unique_ptr<Message> ListGames::from(void *data) {
    auto msg = std::make_unique<ListGames>();

    return msg;
}

std::vector<uint8_t> ListGames::serialize() const {
    std::vector<uint8_t> data = Message::createHeader(m_id, LIST_GAMES_SIZE);
    list_games_t pkt = {0};

    for (size_t i = 0; i < LIST_GAMES_SIZE; i++)
        data.push_back(*(reinterpret_cast<uint8_t *>(&pkt) + i));
    return data;
}