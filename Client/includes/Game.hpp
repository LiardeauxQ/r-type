/*
** EPITECH PROJECT, 2019
** Game.hpp
** File description:
** Game header
*/

#ifndef GAME_HPP
    #define GAME_HPP

    #define WINDOW_NAME "test"
    #define WINDOW_WIDTH 1536
    #define WINDOW_HEIGHT 864

#include <SFML/Graphics.hpp>
#include <memory>
#include "TextureBuilder.hpp"
#include "StateBuilder.hpp"
#include "StateStack.hpp"
#include "InputOptionsHandler.hpp"
#include "ClientPacketDispatcher.hpp"

class Game {
    public:
        Game(int ac, char **av);
        ~Game();

        void run();
    private:
        void handleTransition(Transition transition);
        void loop();
        void gameConnection();
        void checkServerPackets();
        void handlePacket(const Message& msg);
        void roomInfo(const RoomInfo& msg);
        void successConnection(const SuccessConnect& msg);
        void playerHasJoin(const RoomPlayerJoin& msg);
        void playerHasQuit(const RoomPlayerQuit& msg);
        void getPlayerState(const RoomPlayerState& msg);
        void displayHelp();

        InputOptionsHandler m_input;
        std::shared_ptr<ClientPacketDispatcher> m_dispatcher;
        TextureBuilder m_textureBuilder;
        StateBuilder m_stateBuilder;
        StateStack m_states;
        bool m_isRunning;
        sf::RenderWindow *m_window;
        sf::Event m_event;
        float m_deltaTime;
};

#endif /* !GAME_HPP */
