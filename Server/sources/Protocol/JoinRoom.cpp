//
// Created by alex on 11/12/19.
//

#include "includes/Protocol/JoinRoom.hpp"

String Join::getKey() const
{
    return Message::getKey();
}

Box<IFactorizable<String>> Join::copy() const
{
    return Box<IFactorizable<String>>();
}

Vec<u8> Join::serialize() const
{
    Vec<u8> data = {'R', '-', 'T', 'Y'};
    union {
        int integer;
        u8 bytes[4];
    } test{};
    test.integer = static_cast<int>(m_roomName.length());
    for (unsigned char byte : test.bytes)
        data.push_back(byte);
    return data;
}

void Join::deserialize(Vec<u8>& data)
{

}
