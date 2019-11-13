//
// Created by alex on 11/12/19.
//

#include "includes/Protocol/JoinRoom.hpp"
JoinRoom::JoinRoom(string roomName)
    : Message(JOIN_ROOM)
    , m_roomName(move(roomName))
{}
