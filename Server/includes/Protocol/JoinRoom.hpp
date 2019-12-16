//
// Created by alex on 12/2/19.
//

#ifndef R_TYPE_JOINROOM_HPP
#define R_TYPE_JOINROOM_HPP

#include "Message.hpp"

class Join : public Message {
public:
    ~Join() override = default;
    [[nodiscard]] String getKey() const override;
    [[nodiscard]] Box<IFactorizable<String>> copy() const override;
    [[nodiscard]] Vec<u8> serialize() const override;
    void deserialize(Vec<u8>& data) override;

    String m_roomName;
};

#endif //R_TYPE_JOINROOM_HPP
