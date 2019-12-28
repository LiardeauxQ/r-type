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
#include "EntityBuilder.hpp"
#include "StateBuilder.hpp"
#include "StateStack.hpp"
#include "InputOptionsHandler.hpp"
#include "TcpCommunication.hpp"
#include "UdpCommunication.hpp"
#include "GameData.hpp"

class Game {
    public:
        Game(int ac, char **av);
        ~Game();

        void run();
    private:
        void handleTransition(Transition transition);
        void loop();
        void checkGameStatus();

        void displayHelp();

        InputOptionsHandler m_input;
        boost::shared_ptr<TcpCommunication> m_tcpHandler;
        boost::shared_ptr<UdpCommunication> m_udpHandler;
        std::shared_ptr<GameData> m_gameData;
        EntityBuilder m_entityBuilder;
        StateBuilder m_stateBuilder;
        StateStack m_states;
        bool m_isRunning;
        sf::RenderWindow *m_window;
        sf::Event m_event;
        float m_deltaTime;
};

#endif /* !GAME_HPP */
