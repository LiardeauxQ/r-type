//
// Created by Quentin Liardeaux on 12/27/19.
//

#ifndef R_TYPE_ENTITYSTATE_HPP
#define R_TYPE_ENTITYSTATE_HPP

#include <string>
#include <memory>

#include "Message.hpp"
#include "protocol.hpp"

class EntityState : public Message {
public:
    EntityState(size_t entityId, pos_t position, pos_t velocity, uint16_t angle, EntityType type)
            : Message(UDP_COMMUNICATION::STATE_ENTITY)
            , m_entityId(entityId)
            , m_position(position)
            , m_velocity(velocity)
            , m_angle(angle)
            , m_type(type) {}
    ~EntityState() override = default;

    static std::unique_ptr<Message> from(void *data);

    [[nodiscard]] std::vector<uint8_t> serialize() const override;
    size_t getSize() const final { return PACKET_HDR_SIZE + STATE_ENTITY_SIZE; }

    size_t getEntityId() const { return m_entityId; }
    const pos_t& getPosition() const { return m_position; }
    const pos_t& getVelocity() const { return m_velocity; }
    uint16_t getAngle() const { return m_angle; }
    EntityType getType() const { return m_type; }
private:
    size_t m_entityId;
    pos_t m_position;
    pos_t m_velocity;
    uint16_t m_angle;
    EntityType m_type;
};

#endif //R_TYPE_ENTITYSTATE_HPP
