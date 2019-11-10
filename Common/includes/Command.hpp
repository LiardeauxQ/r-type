//
// Created by alex on 11/10/19.
//

#ifndef R_TYPE_SERVER_COMMAND_HPP
#define R_TYPE_SERVER_COMMAND_HPP

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

class Command {
public:
    Command(TcpSocket sock);
    Command(id, void *payload);

    send(TcpSocket sock);

    struct CommandContent {
        uint32_t id;
        void *payload;
    };

    CommandContent content;
};



#endif //R_TYPE_SERVER_COMMAND_HPP
