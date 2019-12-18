//
// Created by Quentin Liardeaux on 12/18/19.
//

#include "includes/Protocol/PlayerInfo.hpp"

PlayerInfo::PlayerInfo(void *data) {

}

std::vector<uint8_t> PlayerInfo::serialize() const {
    return Message::serialize();
}
CreateGame::CreateGame(void *data) : Message(CREATE_GAME) {
    auto pkt = reinterpret_cast<create_game_t*>(data);

    m_name = std::string(reinterpret_cast<char*>(pkt->name));
    m_password = std::string(reinterpret_cast<char *>(pkt->password));
    m_nickname = std::string(reinterpret_cast<char *>(pkt->nickname));
}

std::vector<uint8_t> CreateGame::serialize() const {
    std::vector<uint8_t> data = Message::createHeader(m_id, CREATE_GAME_SIZE);
    create_game_t pkt = {{0}, {0}, {0}};

    for (size_t i = 0; i < m_name.size() && i < MAX_BUFFER_SIZE; i++)
        pkt.name[i] = static_cast<uint8_t>(*(m_name.c_str() + i));
    for (size_t i = 0; i < m_password.size() && i < MAX_BUFFER_SIZE; i++)
        pkt.password[i] = static_cast<uint8_t>(*(m_password.c_str() + i));
    for (size_t i = 0; i < m_nickname.size() && i < MAX_BUFFER_SIZE; i++)
        pkt.nickname[i] = static_cast<uint8_t>(*(m_nickname.c_str() + i));
    for (size_t i = 0; i < JOIN_GAME_SIZE; i++)
        data.push_back(*(reinterpret_cast<uint8_t *>(&pkt) + i));
    return data;
}