//
// Created by alex on 11/11/19.
//

#include "Protocol/CreateRoom.hpp"

CreateRoom::CreateRoom(string roomName)
    : Message(CREATE_ROOM)
    , m_roomName(move(roomName))
{}
void* CreateRoom::serialize(size_t& size) const
{
    size = m_roomName.length();
    return (void *) m_roomName.c_str();
}
