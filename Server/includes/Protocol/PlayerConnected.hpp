//
// Created by alex on 11/10/19.
//

#ifndef CPP_RTYPE_2019_GAMEROOM_HPP
#define CPP_RTYPE_2019_GAMEROOM_HPP

#include "Message.hpp"

using namespace std;

class PlayerConnected : public Message {
public:
    ~PlayerConnected() override = default;
    [[nodiscard]] unique_ptr<IFactorizable> copy() const override;
    [[nodiscard]] string getKey() const override;
    [[nodiscard]] vector<u8> serialize() const override;
    void deserialize(Vec<u8>& data) override;
};

#endif //CPP_RTYPE_2019_GAMEROOM_HPP
