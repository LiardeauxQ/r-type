//
// Created by Quentin Liardeaux on 12/29/19.
//

#ifndef R_TYPE_ERRORPACKET_HPP
#define R_TYPE_ERRORPACKET_HPP

#include <string>
#include <memory>

#include "Message.hpp"
#include "protocol.hpp"

class ErrorPacket : public Message {
public:
    ErrorPacket(ERROR_CODE code)
            : Message(TCP_COMMUNICATION::ERROR)
            , m_code(code) {}
    ~ErrorPacket() override = default;

    static std::unique_ptr<Message> from(void *data);

    [[nodiscard]] std::vector<uint8_t> serialize() const override;
    size_t getSize() const final { return PACKET_HDR_SIZE + ERROR_SIZE; }

    ERROR_CODE getErrorCode() const { return m_code; }
private:
    ERROR_CODE m_code;
};

#endif //R_TYPE_ERRORPACKET_HPP
