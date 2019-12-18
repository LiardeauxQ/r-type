//
// Created by alex on 12/2/19.
//

#ifndef R_TYPE_JOINGAME_HPP
#define R_TYPE_JOINGAME_HPP

#include <string>

#include "Message.hpp"
#include "protocol.hpp"

class JoinGame : public Message {
public:
    JoinGame(std::string name, std::string password, std::string nickname)
        : Message(TCP_COMMUNICATION::JOIN_GAME)
        , m_name(std::move(name))
        , m_password(std::move(password))
        , m_nickname(std::move(nickname)) {}
    JoinGame(void *data);
    ~JoinGame() override = default;

    [[nodiscard]] std::vector<uint8_t> serialize() const override;
    size_t getSize() const override { return PACKET_HDR_SIZE + JOIN_GAME_SIZE; }

    const std::string& getName() const { return m_name; }
    const std::string& getPassword() const { return m_password; }
    const std::string& getNickname() const { return m_nickname; }
private:
    std::string m_name;
    std::string m_password;
    std::string m_nickname;
};

#endif //R_TYPE_JOINGAME_HPP
