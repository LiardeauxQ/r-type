//
// Created by Quentin Liardeaux on 12/18/19.
//

#ifndef R_TYPE_LISTSTAGES_HPP
#define R_TYPE_LISTSTAGES_HPP

#include <string>

#include "Message.hpp"
#include "protocol.hpp"

class ListStages : public Message {
public:
    ListStages()
            : Message(TCP_COMMUNICATION::LIST_STAGES) {}
    ListStages(void *data);
    ~ListStages() override = default;

    [[nodiscard]] std::vector<uint8_t> serialize() const override;
    size_t getSize() const final { return PACKET_HDR_SIZE + LIST_STAGES_SIZE; }
};

#endif //R_TYPE_LISTSTAGES_HPP
