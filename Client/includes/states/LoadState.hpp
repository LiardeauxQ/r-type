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
        LoadState();
        ~LoadState();
        void onStart();
        void onStop();
        void onPause();
        void onResume();
        void update();
        void handleEvent();
};

#endif /* !LOADSTATE_HPP */
