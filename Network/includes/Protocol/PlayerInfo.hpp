//
// Created by Quentin Liardeaux on 12/18/19.
//

#ifndef R_TYPE_PLAYERINFO_HPP
#define R_TYPE_PLAYERINFO_HPP

#include <string>

#include "Message.hpp"
#include "protocol.hpp"

class PlayerInfo : public Message {
public:
    PlayerInfo(uint8_t id_player, std::string nickname, bool is_ready)
            : Message(TCP_COMMUNICATION::PLAYER_INFO)
            , m_idPlayer(id_player)
            , m_nickname(std::move(nickname))
            , m_isReady(is_ready) {}
    PlayerInfo(void *data);
    ~PlayerInfo() override = default;

    [[nodiscard]] std::vector<uint8_t> serialize() const override;
    size_t getSize() const final { return PACKET_HDR_SIZE + PLAYER_INFO_SIZE; }

    uint8_t getIdPlayer() const { return m_idPlayer; }
    const std::string &getNickname() const { return m_nickname; }
    bool isReady() const { return m_isReady; }
private:
    uint8_t m_idPlayer;
    std::string m_nickname;
    bool m_isReady;
};

#endif //R_TYPE_PLAYERINFO_HPP
