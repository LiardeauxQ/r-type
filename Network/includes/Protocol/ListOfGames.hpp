//
// Created by Quentin Liardeaux on 12/18/19.
//

#ifndef R_TYPE_LISTOFGAMES_HPP
#define R_TYPE_LISTOFGAMES_HPP

#include <string>

#include "Message.hpp"
#include "protocol.hpp"

class ListOfGames : public Message {
public:
    ListOfGames() : Message(TCP_COMMUNICATION::LIST_OF_GAMES) {}
    ~ListOfGames() override = default;

    static std::unique_ptr<Message> from(void *data);

    [[nodiscard]] std::vector<uint8_t> serialize() const override;
    size_t getSize() const final;

    void addGame(uint32_t idGame, const std::string& name, bool isPrivate,
                  uint8_t nbPlayers, uint8_t maxPlayers);
private:
    std::vector<game_list_info_t> m_games;
};

#endif //R_TYPE_LISTOFGAMES_HPP
