/*
** EPITECH PROJECT, 2019
** Game.hpp
** File description:
** Game header
*/

#include <stack>
#include "StateBuilder.hpp"

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
        std::stack<std::unique_ptr<State>> m_states;
        bool m_isRunning;
};

#endif /* !GAME_HPP */
