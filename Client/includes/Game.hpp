/*
** EPITECH PROJECT, 2019
** Game.hpp
** File description:
** Game header
*/

#include <SFML/Graphics.hpp>
#include "StateBuilder.hpp"
#include "StateStack.hpp"

#ifndef GAME_HPP
	#define GAME_HPP

    #define WINDOW_WIDTH 1536
    #define WINDOW_HEIGHT 864

class Game {
    public:
        Game();
        ~Game();
        void run();
    private:
        void loop();
        StateBuilder m_stateBuilder;
        StateStack m_states;
        bool m_isRunning;
        std::shared_ptr<sf::RenderWindow> m_window;
};

#endif /* !GAME_HPP */
