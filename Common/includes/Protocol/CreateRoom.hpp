//
// Created by alex on 11/10/19.
//

#ifndef CPP_RTYPE_2019_CREATEROOM_HPP
#define CPP_RTYPE_2019_CREATEROOM_HPP

#include <string>

#include "Command.hpp"

class CreateRoom : public Command {
public:
    explicit CreateRoom(void *data);

    string m_roomName;
    static const size_t CREATE_GAME_PAYLOAD_SIZE = sizeof(char) * 256;
};

#endif //CPP_RTYPE_2019_CREATEROOM_HPP
