//
// Created by alex on 11/10/19.
//

#ifndef R_TYPE_SERVER_COMMAND_HPP
#define R_TYPE_SERVER_COMMAND_HPP

#include <unordered_map>
#include "ISerialize.hpp"
#include "Definitions.hpp"
using namespace std;

enum COMMAND_ID {
    ERROR,              // client <=> server
    CREATE_ROOM,        // client => server
    JOIN_ROOM,          // client => server
    QUIT_ROOM,          // client => server
    ROOM_INFO,          // server => client
    ROOM_PLAYER_JOIN,   // server => client
    ROOM_PLAYER_QUIT,   // server => client
    GAME_START,         // server => client
};

class Command : ISerialize {
public:
    explicit Command(COMMAND_ID id) : m_id(id) {}

    template <typename T>
    static Box<T> deserialize(void *data);

    void* serialize(size_t& size) const override = 0;

    COMMAND_ID m_id;
};

#endif //R_TYPE_SERVER_COMMAND_HPP
