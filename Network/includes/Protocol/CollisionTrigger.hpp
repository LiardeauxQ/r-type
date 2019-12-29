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
    CollisionTrigger(size_t firstEntity, EntityType firstType, size_t secondEntity,
            EntityType secondType, pos_t position)
            : Message(UDP_COMMUNICATION::COLLISION_TRIGGER)
            , m_firstEntity(firstEntity)
            , m_firstType(firstType)
            , m_secondEntity(secondEntity)
            , m_secondType(secondType)
            , m_position(position) {}
    ~CollisionTrigger() override = default;

    static std::unique_ptr<Message> from(void *data);

    [[nodiscard]] std::vector<uint8_t> serialize() const override;
    size_t getSize() const final { return PACKET_HDR_SIZE + COLLISION_TRIGGER_SIZE; }

    size_t getFirstEntityId() const { return m_firstEntity; }
    EntityType getFirstType() const { return m_firstType; }
    size_t getSecondEntityId() const { return m_secondEntity; }
    EntityType getSecondType() const { return m_secondType; }
    pos_t getPosition() const { return m_position; }
private:
    size_t m_firstEntity;
    EntityType m_firstType;
    size_t m_secondEntity;
    EntityType m_secondType;
    pos_t m_position;
};

#endif //R_TYPE_COLLISIONTRIGGER_HPP
