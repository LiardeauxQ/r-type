//
// Created by Quentin Liardeaux on 12/18/19.
//

#ifndef R_TYPE_ROOMINFO_HPP
#define R_TYPE_ROOMINFO_HPP

#include <string>
#include <memory>

#include "Message.hpp"
#include "protocol.hpp"

class RoomInfo : public Message {
public:
    RoomInfo(uint32_t idGame, std::string name, uint8_t nbPlayers, uint8_t maxPlayers, uint8_t idPlayer)
            : Message(TCP_COMMUNICATION::ROOM_INFO)
            , m_idGame(idGame)
            , m_name(std::move(name))
            , m_nbPlayers(nbPlayers)
            , m_maxPlayers(maxPlayers)
            , m_idPlayer(idPlayer)
            {}
    ~RoomInfo() override = default;

    static std::unique_ptr<Message> from(void *data);

    [[nodiscard]] std::vector<uint8_t> serialize() const override;
    size_t getSize() const final { return PACKET_HDR_SIZE + ROOM_INFO_SIZE; }

    uint32_t getIdGame() const { return m_idGame; }
    uint8_t getNbPlayers() const { return m_nbPlayers; }
    uint8_t getMaxPlayers() const { return m_maxPlayers; }
    uint8_t getIdPlayer() const { return m_idPlayer; }
    const std::string &getName() const { return m_name; }
private:
    uint32_t m_idGame;
    std::string m_name;
    uint8_t m_nbPlayers;
    uint8_t m_maxPlayers;
    uint8_t m_idPlayer;
};

#endif //R_TYPE_ROOMINFO_HPP
