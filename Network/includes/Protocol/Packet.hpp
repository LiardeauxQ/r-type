//
// Created by Quentin Liardeaux on 12/23/19.
//

#ifndef R_TYPE_PACKET_HPP
#define R_TYPE_PACKET_HPP

#include "ClientConnect.hpp"
#include "CreateGame.hpp"
#include "GameStart.hpp"
#include "JoinGame.hpp"
#include "ListGames.hpp"
#include "ListOfGames.hpp"
#include "ListOfStages.hpp"
#include "ListStages.hpp"
#include "PlayerInfo.hpp"
#include "RoomInfo.hpp"
#include "RoomPlayerJoin.hpp"
#include "RoomPlayerQuit.hpp"
#include "RoomPlayerState.hpp"
#include "SuccessConnect.hpp"
#include "DirectionState.hpp"
#include "EntityState.hpp"
#include "FireEntity.hpp"
#include "SyncDistance.hpp"
#include "CollisionTrigger.hpp"

#include <vector>
#include <tuple>

extern const std::vector<std::tuple<uint8_t, std::unique_ptr<Message> (*)(void *)>> packetInitializers;

#endif //R_TYPE_PACKET_HPP
