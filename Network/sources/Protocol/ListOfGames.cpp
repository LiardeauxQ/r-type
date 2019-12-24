//
// Created by Quentin Liardeaux on 12/18/19.
//

#include "Protocol/ListOfGames.hpp"

std::unique_ptr<Message> ListOfGames::from(void *data) {
    auto pkt = reinterpret_cast<list_of_stages_t*>(data);
    auto msg = std::make_unique<ListOfGames>();

    for (size_t i = 0 ; i < pkt->nb_games ; i++) {
        auto game = pkt->games[i];

        msg->addGame(game.id_game, std::string(reinterpret_cast<char *>(game.name)),
                game.is_private, game.nb_players, game.max_players);
    }
    return msg;
}

std::vector<uint8_t> ListOfGames::serialize() const {
    uint16_t size = m_games.size() * GAME_LIST_INFO_SIZE + sizeof(uint16_t);
    std::vector<uint8_t> data = Message::createHeader(m_id, size);
    list_of_games_t pkt = {static_cast<uint32_t>(m_games.size()), nullptr};

    for (size_t i = 0; i < sizeof(pkt.nb_games); i++)
        data.push_back(*(reinterpret_cast<uint8_t *>(&pkt) + i));
    for (size_t i = 0; i < m_games.size(); i++) {
        for (size_t j = 0; j < GAME_LIST_INFO_SIZE; j++) {
            auto game = m_games[i];
            data.push_back(*(reinterpret_cast<uint8_t *>(&game) + j));
        }
    }
    return data;
}

size_t ListOfGames::getSize() const {
    return PACKET_HDR_SIZE + (m_games.size() * GAME_LIST_INFO_SIZE) + sizeof(uint16_t);
}

void ListOfGames::addGame(uint32_t idGame, const std::string& name, bool isPrivate,
                            uint8_t nbPlayers, uint8_t maxPlayers) {
    game_list_info_t info = {idGame, {0}, isPrivate, nbPlayers, maxPlayers};

    for (size_t i = 0; i < name.size() && i < MAX_BUFFER_SIZE; i++)
        info.name[i] = static_cast<uint8_t>(*(name.c_str() + i));
    m_games.push_back(info);
}