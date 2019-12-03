//
// Created by alex on 11/11/19.
//

#include "includes/Protocol/PlayerConnected.hpp"

vector<u8> PlayerConnected::serialize() const
{
    return Vec<u8>();
}

String PlayerConnected::getKey() const
{
    return Message::getKey();
}

unique_ptr<IFactorizable<string>> PlayerConnected::copy() const
{
    return unique_ptr<IFactorizable<string>>();
}

void PlayerConnected::deserialize(vector<u8>& data)
{

}

