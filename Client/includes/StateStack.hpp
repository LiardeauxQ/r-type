/*
** EPITECH PROJECT, 2019
** StateStack.hpp
** File description:
** StateStack header
*/

#ifndef STATESTACK_HPP
	#define STATESTACK_HPP

#include <stack>
#include "State.hpp"

class StateStack : public std::stack<State*> {
    public:
        StateStack(): std::stack<State*>() {};
        ~StateStack() = default;
        void swap(State *newState);
};

#endif /* !STATESTACK_HPP */
