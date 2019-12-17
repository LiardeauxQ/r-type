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
        ~Game() = default;
    private:
        StateBuilder stateBuilder;
        std::stack<State *> states;
};

#endif /* !GAME_HPP */
