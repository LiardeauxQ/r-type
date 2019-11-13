//
// Created by alex on 11/10/19.
//

#ifndef R_TYPE_SERVER_COMMAND_HPP
#define R_TYPE_SERVER_COMMAND_HPP

#include <unordered_map>
#include "ISerialize.hpp"
#include "Definitions.hpp"
using namespace std;

enum MESSAGE_ID {
    ERROR,              // client <=> server
    CREATE_ROOM,        // client => server
    JOIN_ROOM,          // client => server
    QUIT_ROOM,          // client => server
    ROOM_INFO,          // server => client
    ROOM_PLAYER_JOIN,   // server => client
    ROOM_PLAYER_QUIT,   // server => client
    GAME_START,         // server => client
};

struct Message : ISerialize {
    explicit Message(MESSAGE_ID id) : m_id(id) {}
    ~Message() override = default;

    template <typename T>
    static Box<T> deserialize(void *data);

    MESSAGE_ID m_id;
};

template <typename T>
Box<T> Message::deserialize(void* data)
{
    auto element = make_unique<T>();
    memset(element.get(), data, sizeof(T));
}

#endif //R_TYPE_SERVER_COMMAND_HPP
