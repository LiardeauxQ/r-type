//
// Created by alex on 11/10/19.
//

#ifndef CPP_RTYPE_2019_CREATEROOM_HPP
#define CPP_RTYPE_2019_CREATEROOM_HPP

#include "Message.hpp"

class CreateRoom : public Message {
public:
    explicit CreateRoom(string roomName);

    void *serialize(size_t& size) const override;

    string m_roomName;
    static const size_t CREATE_GAME_PAYLOAD_SIZE = sizeof(char) * 256;
};

#endif //CPP_RTYPE_2019_CREATEROOM_HPP
