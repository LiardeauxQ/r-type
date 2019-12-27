//
// Created by Quentin Liardeaux on 12/23/19.
//

#ifndef R_TYPE_SUCCESSCONNECT_HPP
#define R_TYPE_SUCCESSCONNECT_HPP

#include <string>
#include <memory>

#include "Message.hpp"
#include "protocol.hpp"

class SuccessConnect : public Message {
public:
    SuccessConnect(size_t id)
            : Message(TCP_COMMUNICATION::SUCCESS_CONNECT)
            , m_idPlayer(id) {}
    ~SuccessConnect() override = default;

    static std::unique_ptr<Message> from(void *data);

    [[nodiscard]] std::vector<uint8_t> serialize() const override;
    size_t getSize() const final { return PACKET_HDR_SIZE + SUCCESS_CONNECT_SIZE; }

    size_t getId() const { return m_idPlayer; }
private:
    size_t m_idPlayer;
};


#endif //R_TYPE_SUCCESSCONNECT_HPP
