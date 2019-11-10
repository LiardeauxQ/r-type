//
// Created by alex on 11/10/19.
//

#ifndef CPP_RTYPE_2019_GAMESERVER_HPP
#define CPP_RTYPE_2019_GAMESERVER_HPP

#include "Definition.hpp"
#include <vector>
using namespace std;

class GameServer {
public:
    GameServer(short port, const std::string& addr);
    ~GameServer();
private:
    vector<Box<GameRoom>>
};

#endif //CPP_RTYPE_2019_GAMESERVER_HPP
