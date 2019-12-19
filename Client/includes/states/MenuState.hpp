/*
** EPITECH PROJECT, 2019
** MenuState.hpp
** File description:
** MenuState header
*/

#ifndef MENUSTATE_HPP
	#define MENUSTATE_HPP

#include "State.hpp"

class MenuState : public State {
    public:
        MenuState(TextureBuilder &textureBuilder);
        ~MenuState();
        void onStart();
        void onStop();
        void onPause();
        void onResume();
        void update();
        void handleEvent();
};

#endif /* !MENUSTATE_HPP */
