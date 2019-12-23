/*
** EPITECH PROJECT, 2019
** PauseState.hpp
** File description:
** MenuState header
*/

#ifndef PAUSESTATE_HPP
	#define PAUSESTATE_HPP

#include "State.hpp"

class PauseState : public State {
    public:
        PauseState(std::shared_ptr<ClientPacketDispatcher> dispatcher, TextureBuilder &textureBuilder);
        ~PauseState();
        void onStart();
        void onStop();
        void onPause();
        void onResume();
        void update();
        Transition handleEvent(sf::Event &event);
};

#endif /* !PAUSESTATE_HPP */
