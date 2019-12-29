//
// Created by Quentin Liardeaux on 12/16/19.
//

#ifndef R_TYPE_PROTOCOL_HPP
#define R_TYPE_PROTOCOL_HPP

#include <cstdint>
#include <cstddef>

#if defined (__clang__) || (WINDOWS)
#   pragma pack(1)
#endif /* __clang__ */

#if defined (__GNUC__) && (__GNUC__ >= 7)
#   define PACKED __attribute__((packed))
#else
#   define PACKED
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_BUFFER_SIZE 256
#define PORT_SIZE 15

const uint32_t MAGIC_NUMBER = 0x522d5444;

#define MAGIC_NUMBER_SIZE 4

enum ERROR_CODE {
    UNKNOWN_ROOM = 0x01,
    WRONG_PASSWORD = 0x02,
    NICKNAME_ALREADY_TAKEN = 0x03,
    GAME_IS_FULL = 0x04,
};

enum TCP_COMMUNICATION {
    ERROR = 0x00,
    CREATE_GAME = 0x01,
    JOIN_GAME = 0x02,
    ROOM_INFO = 0x03,
    ROOM_PLAYER_JOIN = 0x04,
    ROOM_PLAYER_QUIT = 0x05,
    ROOM_PLAYER_STATE = 0x06,
    GAME_START = 0x07,
    LIST_STAGES = 0x08,
    LIST_OF_STAGES = 0x09,
    LIST_GAMES = 0x0A,
    LIST_OF_GAMES = 0x0B,
    CLIENT_CONNECT = 0x11,
    PLAYER_INFO = 0x12,
    SUCCESS_CONNECT = 0x13,
};

enum UDP_COMMUNICATION {
    GAME_READY = 0x0C,
    FIRE_ENTITY = 0x0D,
    STATE_ENTITY = 0x0E,
    MOVE = 0x0F,
    SYNC_DIST = 0x10,
};

typedef struct {
    uint32_t magic_number;
    uint8_t packet_id;
    uint16_t packet_size;
} packet_header_t;

const size_t PACKET_HDR_SIZE = sizeof(packet_header_t);

typedef struct {
    uint8_t command_code;
    uint8_t error_code;
} server_error_t;

const size_t ERROR_SIZE = sizeof(server_error_t);

typedef struct {
    float x;
    float y;
} pos_t;

typedef struct {
    uint16_t port;
    uint8_t address[PORT_SIZE];
} client_connect_t;

const size_t CLIENT_CONNECT_SIZE = sizeof(client_connect_t);

typedef struct {
    size_t id_player;
} success_connect_t;

const size_t SUCCESS_CONNECT_SIZE = sizeof(success_connect_t);

typedef struct {
    size_t id_player;
    uint8_t name[MAX_BUFFER_SIZE];
    uint8_t password[MAX_BUFFER_SIZE];
    uint8_t nickname[MAX_BUFFER_SIZE];
} create_game_t;

const size_t CREATE_GAME_SIZE = sizeof(create_game_t);

typedef struct {
    size_t id_player;
    uint8_t name[MAX_BUFFER_SIZE];
    uint8_t password[MAX_BUFFER_SIZE];
    uint8_t nickname[MAX_BUFFER_SIZE];
} join_game_t;

const size_t JOIN_GAME_SIZE = sizeof(join_game_t);

typedef struct {
    size_t id_game;
    uint8_t name[MAX_BUFFER_SIZE];
    uint8_t nb_players;
    uint8_t max_players;
    size_t id_player;
} room_info_t;

const size_t ROOM_INFO_SIZE = sizeof(room_info_t);

typedef struct {
    size_t id_player;
    uint8_t nickname[MAX_BUFFER_SIZE];
    uint8_t is_ready;
} player_info_t;

const size_t PLAYER_INFO_SIZE = sizeof(player_info_t);

typedef struct {
    size_t id_player;
    uint8_t nickname[MAX_BUFFER_SIZE];
    uint8_t is_ready;
} room_player_join_t;

const size_t ROOM_PLAYER_JOIN_SIZE = sizeof(room_player_join_t);

typedef struct {
    size_t id_player;
    uint8_t nickname[MAX_BUFFER_SIZE];
    uint8_t is_ready;
} room_player_quit_t;

const size_t ROOM_PLAYER_QUIT_SIZE = sizeof(room_player_quit_t);

typedef struct {
    size_t id_player;
    uint8_t nickname[MAX_BUFFER_SIZE];
    uint8_t is_ready;
} room_player_state_t;

const size_t ROOM_PLAYER_STATE_SIZE = sizeof(room_player_state_t);

typedef struct {
    uint16_t udp_port;
} game_start_t;

const size_t GAME_START_SIZE = sizeof(game_start_t);

typedef struct {
    size_t id_game;
    uint8_t name[MAX_BUFFER_SIZE];
    uint8_t is_private;
    uint8_t nb_players;
    uint8_t max_players;
} game_list_info_t;

const size_t GAME_LIST_INFO_SIZE = sizeof(game_list_info_t);

typedef struct {
    uint8_t tmp;
} list_stages_t;

const size_t LIST_STAGES_SIZE = sizeof(list_stages_t);

typedef struct {
    uint32_t nb_games;
    game_list_info_t *games;
} list_of_stages_t;

typedef struct {
    uint8_t tmp;
} list_games_t;

const size_t LIST_GAMES_SIZE = sizeof(list_games_t);

typedef struct {
    uint32_t nb_games;
    game_list_info_t *games;
} list_of_games_t;

typedef struct {
    size_t id_player;
} game_ready_t;

const size_t GAME_READY_SIZE = sizeof(game_ready_t);

enum FireType {
    NORMAL = 0x00,
};

typedef struct {
    //team
    size_t id_new_entity;
    FireType type;
} fire_entity_t;

const size_t FIRE_ENTITY_SIZE = sizeof(fire_entity_t);

enum EntityType {
    SHIP,
    ENEMY,
    BULLET,
};

typedef struct {
    size_t id_entity;
    pos_t position;
    pos_t velocity;
    uint16_t angle;
    EntityType type;
} state_entity_t;

const size_t STATE_ENTITY_SIZE = sizeof(state_entity_t);

enum Direction {
    LEFT,
    RIGHT,
    TOP,
    BOTTOM,
};

typedef struct {
    Direction dir;
} move_t;

const size_t MOVE_SIZE = sizeof(move_t);

typedef struct {
    uint64_t dist;
} sync_dist_t;

const size_t SYNC_DIST_SIZE = sizeof(sync_dist_t);

#ifdef __cplusplus
}
#endif

#if defined(__clang__) || (WINDOWS)
#   pragma options align=reset
#endif /* __clang__ */

#endif //R_TYPE_PROTOCOL_HPP
