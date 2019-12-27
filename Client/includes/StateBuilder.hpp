/*
** EPITECH PROJECT, 2019
** StateBuilder.hpp
** File description:
** StateBuilder header
*/

#ifndef STATEBUILDER_HPP
	#define STATEBUILDER_HPP

#include "State.hpp"
#include "EntityBuilder.hpp"

class StateBuilder {
    public:
        StateBuilder() = default;
        ~StateBuilder() = default;
        State *createState(States stateName, std::shared_ptr<GameData> gameData);
    private:
};

#endif /* !STATEBUILDER_HPP */
