/*
** EPITECH PROJECT, 2019
** StateStack.cpp
** File description:
** StateStack implementation
*/

#include "StateStack.hpp"

void StateStack::swap(State *newState)
{
    this->pop();
    this->push(newState);
}
