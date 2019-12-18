/*
** EPITECH PROJECT, 2019
** StateStack.cpp
** File description:
** StateStack implementation
*/

#include "StateStack.hpp"

void StateStack::swap(std::unique_ptr<State> newState)
{
    this->pop();
    this->push(std::move(newState));
}
