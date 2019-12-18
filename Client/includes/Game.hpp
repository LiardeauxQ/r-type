//
// Created by Quentin Liardeaux on 12/17/19.
//

#ifndef R_TYPE_GAME_HPP
#define R_TYPE_GAME_HPP

#include "TcpStream.hpp"
#include "TcpListener.hpp"
#include "InputOptionsHandler.hpp"
#include "Protocol/PacketDispatcher.hpp"
#include <optional>

class Game {
public:
    Game(int ac, char **av);
    ~Game() = default;

    void run();
private:
    void gameConnection();

    std::optional<PacketDispatcher> m_dispatcher;
    InputOptionsHandler m_input;
};

#endif //R_TYPE_GAME_HPP
