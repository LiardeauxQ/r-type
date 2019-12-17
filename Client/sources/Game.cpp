/*
** EPITECH PROJECT, 2019
** Game.cpp
** File description:
** Game implementation
*/

#include "Game.hpp"

Game::Game()
    : stateBuilder()
    , states()
{
    states.push(stateBuilder.createState(States::EMPTY));
}
