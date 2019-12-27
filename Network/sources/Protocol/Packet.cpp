//
// Created by Quentin Liardeaux on 12/23/19.
//

#include "Protocol/Packet.hpp"

const std::vector<std::tuple<uint8_t, std::unique_ptr<Message> (*)(void *)>> packetInitializers = {
        std::make_tuple(CLIENT_CONNECT, &ClientConnect::from),
        std::make_tuple(CREATE_GAME, &CreateGame::from),
        std::make_tuple(GAME_START, &GameStart::from),
        std::make_tuple(JOIN_GAME, &JoinGame::from),
        std::make_tuple(LIST_GAMES, &ListGames::from),
        std::make_tuple(LIST_OF_GAMES, &ListOfGames::from),
        std::make_tuple(LIST_OF_STAGES, &ListOfStages::from),
        std::make_tuple(LIST_STAGES, &ListStages::from),
        std::make_tuple(PLAYER_INFO, &PlayerInfo::from),
        std::make_tuple(ROOM_INFO, &RoomInfo::from),
        std::make_tuple(ROOM_PLAYER_JOIN, &RoomPlayerJoin::from),
        std::make_tuple(ROOM_PLAYER_QUIT, &RoomPlayerQuit::from),
        std::make_tuple(ROOM_PLAYER_STATE, &RoomPlayerState::from),
        std::make_tuple(SUCCESS_CONNECT, &SuccessConnect::from),
        std::make_tuple(FIRE_ENTITY, &FireEntity::from),
        std::make_tuple(MOVE, &DirectionState::from),
        std::make_tuple(STATE_ENTITY, &EntityState::from),
        std::make_tuple(SYNC_DIST, &SyncDistance::from),
};