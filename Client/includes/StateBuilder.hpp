/*
** EPITECH PROJECT, 2019
** StateBuilder.hpp
** File description:
** StateBuilder header
*/

#ifndef STATEBUILDER_HPP
	#define STATEBUILDER_HPP

#include "State.hpp"
#include "TextureBuilder.hpp"

class StateBuilder {
    public:
        StateBuilder();
        State *createState(States stateName, std::shared_ptr<ClientPacketDispatcher> display, TextureBuilder &textureBuilder);
        ~StateBuilder() = default;
    private:
};

#endif /* !STATEBUILDER_HPP */
