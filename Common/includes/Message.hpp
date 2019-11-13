//
// Created by alex on 11/10/19.
//

#ifndef R_TYPE_SERVER_COMMAND_HPP
#define R_TYPE_SERVER_COMMAND_HPP

#include <unordered_map>
#include "ISerialize.hpp"
#include "Definitions.hpp"
using namespace std;

enum REQUEST_ID {
    ERROR,              // client <=> server
    CREATE_ROOM,        // client => server
    JOIN_ROOM,          // client => server
    QUIT_ROOM,          // client => server
    ROOM_INFO,          // server => client
    ROOM_PLAYER_JOIN,   // server => client
    ROOM_PLAYER_QUIT,   // server => client
    GAME_START,         // server => client
};

struct Request : ISerialize {
    explicit Request(REQUEST_ID id) : m_id(id) {}

    template <typename T>
    static Box<T> deserialize(void *data);

    void* serialize(size_t& size) const override = 0;

    REQUEST_ID m_id;
};
template <typename T>
Box<T> Request::deserialize(void* data)
{
    auto element = make_unique<T>();
    memset(element.get(), data, sizeof(T));
}

#endif //R_TYPE_SERVER_COMMAND_HPP
