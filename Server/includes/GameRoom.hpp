//
// Created by alex on 11/10/19.
//

#ifndef CPP_RTYPE_2019_GAMEROOM_HPP
#define CPP_RTYPE_2019_GAMEROOM_HPP

#include <vector>
#include "Definitions.hpp"

using namespace std;

class GameRoom {
public:
    GameRoom(Rc<Client> firstClient);

private:
    vector<Rc<Client>> m_players;
};

#endif //CPP_RTYPE_2019_GAMEROOM_HPP
