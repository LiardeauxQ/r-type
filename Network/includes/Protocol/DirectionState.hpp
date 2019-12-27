//
// Created by Quentin Liardeaux on 12/27/19.
//

#ifndef R_TYPE_DIRECTION_HPP
#define R_TYPE_DIRECTION_HPP

#include <string>
#include <memory>

#include "Message.hpp"
#include "protocol.hpp"

class DirectionState : public Message {
public:
    DirectionState(Direction dir)
            : Message(UDP_COMMUNICATION::MOVE)
            , m_direction(dir) {}
    ~DirectionState() override = default;

    static std::unique_ptr<Message> from(void *data);

    [[nodiscard]] std::vector<uint8_t> serialize() const override;
    size_t getSize() const final { return PACKET_HDR_SIZE + MOVE_SIZE; }

    Direction getDirection() const { return m_direction; }
private:
    Direction m_direction;
};


#endif //R_TYPE_DIRECTION_HPP
