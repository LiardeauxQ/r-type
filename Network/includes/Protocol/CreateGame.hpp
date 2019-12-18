//
// Created by Quentin Liardeaux on 12/17/19.
//

#ifndef R_TYPE_CREATEGAME_HPP
#define R_TYPE_CREATEGAME_HPP

#include <string>

#include "Message.hpp"
#include "protocol.hpp"

class CreateGame : public Message {
public:
    CreateGame(std::string name, std::string password, std::string nickname)
    : Message(TCP_COMMUNICATION::CREATE_GAME)
    , m_name(std::move(name))
    , m_password(std::move(password))
    , m_nickname(std::move(nickname)) {}
    CreateGame(void *data);
    ~CreateGame() override = default;

    [[nodiscard]] std::vector<uint8_t> serialize() const override;
    size_t getSize() const { return PACKET_HDR_SIZE + CREATE_GAME_SIZE; }

    const std::string &getName() const { return m_name; }
    const std::string &getPassword() const { return m_password; }
    const std::string &getNickname() const { return m_nickname; }
private:
    std::string m_name;
    std::string m_password;
    std::string m_nickname;
};


#endif //R_TYPE_CREATEGAME_HPP
