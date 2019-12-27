//
// Created by Quentin Liardeaux on 12/27/19.
//

#ifndef R_TYPE_FIREENTITY_HPP
#define R_TYPE_FIREENTITY_HPP

#include <string>
#include <memory>

#include "Message.hpp"
#include "protocol.hpp"

class FireEntity : public Message {
public:
    FireEntity(size_t entityId, FireType type)
            : Message(UDP_COMMUNICATION::FIRE_ENTITY)
            , m_entityId(entityId)
            , m_type(type) {}
    ~FireEntity() override = default;

    static std::unique_ptr<Message> from(void *data);

    [[nodiscard]] std::vector<uint8_t> serialize() const override;
    size_t getSize() const final { return PACKET_HDR_SIZE + FIRE_ENTITY_SIZE; }

    size_t getEntityId() const { return m_entityId; }
    FireType getType() const { return m_type; }
private:
    size_t m_entityId;
    FireType m_type;
};


#endif //R_TYPE_FIREENTITY_HPP
