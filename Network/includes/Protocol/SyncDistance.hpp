//
// Created by Quentin Liardeaux on 12/27/19.
//

#ifndef R_TYPE_SYNCDISTANCE_HPP
#define R_TYPE_SYNCDISTANCE_HPP

#include <string>
#include <memory>

#include "Message.hpp"
#include "protocol.hpp"

class SyncDistance : public Message {
public:
    SyncDistance(uint64_t dist)
            : Message(UDP_COMMUNICATION::SYNC_DIST)
            , m_distance(dist) {}
    ~SyncDistance() override = default;

    static std::unique_ptr<Message> from(void *data);

    [[nodiscard]] std::vector<uint8_t> serialize() const override;
    size_t getSize() const final { return PACKET_HDR_SIZE + SYNC_DIST_SIZE; }

    uint64_t getDistance() const { return m_distance; }
private:
    uint64_t m_distance;
};

#endif //R_TYPE_SYNCDISTANCE_HPP
