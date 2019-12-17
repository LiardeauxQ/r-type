/*
** EPITECH PROJECT, 2019
** EmptyState.hpp
** File description:
** EmptyState header
*/

#ifndef EMPTYSTATE_HPP
	#define EMPTYSTATE_HPP

#include "State.hpp"

class EmptyState : public State {
    public:
        EmptyState();
        ~EmptyState();
        void onStart();
        void onStop();
        void onPause();
        void onResume();
        void update();
        void handleEvent();
};

#endif /* !EMPTYSTATE_HPP */
