//
// Created by Quentin Liardeaux on 12/29/19.
//

#ifndef R_TYPE_COLLISIONTRIGGER_HPP
#define R_TYPE_COLLISIONTRIGGER_HPP

#include <string>
#include <memory>

#include "Message.hpp"
#include "protocol.hpp"

class CollisionTrigger : public Message {
public:
    CollisionTrigger(size_t firstEntity, size_t secondEntity, pos_t position)
            : Message(UDP_COMMUNICATION::COLLISION_TRIGGER)
            , m_firstEntity(firstEntity)
            , m_secondEntity(secondEntity)
            , m_position(position) {}
    ~CollisionTrigger() override = default;

    static std::unique_ptr<Message> from(void *data);

    [[nodiscard]] std::vector<uint8_t> serialize() const override;
    size_t getSize() const final { return PACKET_HDR_SIZE + COLLISION_TRIGGER_SIZE; }

    size_t getFirstEntityId() const { return m_firstEntity; }
    size_t getSecondEntityId() const { return m_secondEntity; }
    pos_t getPosition() const { return m_position; }
private:
    size_t m_firstEntity;
    size_t m_secondEntity;
    pos_t m_position;
};

#endif //R_TYPE_COLLISIONTRIGGER_HPP
