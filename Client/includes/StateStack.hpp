/*
** EPITECH PROJECT, 2019
** StateStack.hpp
** File description:
** StateStack header
*/

#ifndef STATESTACK_HPP
	#define STATESTACK_HPP

#include <stack>
#include <memory>
#include "State.hpp"

class StateStack : public std::stack<std::unique_ptr<State>> {
    public:
        StateStack(): std::stack<std::unique_ptr<State>>() {};
        ~StateStack() = default;
        void swap(std::unique_ptr<State> newState);
};

#endif /* !STATESTACK_HPP */
