/*
** EPITECH PROJECT, 2019
** GameState.hpp
** File description:
** PauseState header
*/

#ifndef GAMESTATE_HPP
	#define GAMESTATE_HPP

#include "State.hpp"

class GameState : public State {
    public:
        GameState();
        ~GameState();
        void onStart();
        void onStop();
        void onPause();
        void onResume();
        void update();
        void handleEvent();
};

#endif /* !GAMESTATE_HPP */
