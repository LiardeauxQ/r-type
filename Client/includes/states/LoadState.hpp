/*
** EPITECH PROJECT, 2019
** LoadState.hpp
** File description:
** LoadState header
*/

#ifndef LOADSTATE_HPP
	#define LOADSTATE_HPP

#include "State.hpp"

class LoadState : public State {
    public:
        LoadState(std::shared_ptr<ClientPacketDispatcher> dispatcher, TextureBuilder &textureBuilder);
        ~LoadState();
        void onStart();
        void onStop();
        void onPause();
        void onResume();
        void update();
        Transition handleEvent(sf::Event &event);
};

#endif /* !LOADSTATE_HPP */
