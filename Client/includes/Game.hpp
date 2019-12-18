//
// Created by Quentin Liardeaux on 12/17/19.
//

#ifndef R_TYPE_GAME_HPP
#define R_TYPE_GAME_HPP

#include "TcpStream.hpp"
#include "TcpListener.hpp"
#include "InputOptionsHandler.hpp"
#include "Protocol/PacketDispatcher.hpp"
#include "ClientPacketDispatcher.hpp"
#include <optional>

class Game {
public:
    Game(int ac, char **av);
    ~Game();

    void run();
private:
    void gameConnection();
    void displayHelp();

    InputOptionsHandler m_input;
    ClientPacketDispatcher *m_dispatcher;
};

#endif //R_TYPE_GAME_HPP
