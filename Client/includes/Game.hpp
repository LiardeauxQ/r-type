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
};

#endif /* !GAME_HPP */
