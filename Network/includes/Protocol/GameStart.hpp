//
// Created by Quentin Liardeaux on 12/18/19.
//

#ifndef R_TYPE_GAMESTART_HPP
#define R_TYPE_GAMESTART_HPP

#include <string>
#include <memory>

#include "Message.hpp"
#include "protocol.hpp"

class GameStart : public Message {
public:
    GameStart(uint16_t udp_port)
            : Message(TCP_COMMUNICATION::GAME_START)
            , m_udp_port(udp_port) {}
    ~GameStart() override = default;

    static std::unique_ptr<Message> from(void *data);

    [[nodiscard]] std::vector<uint8_t> serialize() const override;
    size_t getSize() const final { return PACKET_HDR_SIZE + GAME_START_SIZE; }

    uint16_t getUdpPort() const { return m_udp_port; }
private:
    uint16_t m_udp_port;
};

#endif //R_TYPE_GAMESTART_HPP
