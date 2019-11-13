//
// Created by alex on 11/12/19.
//

#ifndef R_TYPE_JOINROOM_HPP
#define R_TYPE_JOINROOM_HPP

#include "Message.hpp"

using namespace std;

class JoinRoom : public Message {
    explicit JoinRoom(string roomName);

    string m_roomName;
};

#endif //R_TYPE_JOINROOM_HPP
