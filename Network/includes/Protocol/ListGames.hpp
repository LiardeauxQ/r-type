//
// Created by Quentin Liardeaux on 12/18/19.
//

#ifndef R_TYPE_LISTGAMES_HPP
#define R_TYPE_LISTGAMES_HPP

#include <string>
#include <memory>

#include "Message.hpp"
#include "protocol.hpp"

class ListGames : public Message {
public:
    ListGames() : Message(TCP_COMMUNICATION::LIST_GAMES) {}
    ~ListGames() override = default;

    static std::unique_ptr<Message> from(void *data);

    [[nodiscard]] std::vector<uint8_t> serialize() const override;
    size_t getSize() const final { return PACKET_HDR_SIZE + LIST_GAMES; }

private:
};

#endif //R_TYPE_LISTGAMES_HPP
