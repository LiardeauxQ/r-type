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
        EmptyState(std::shared_ptr<GameData> gameData);
        ~EmptyState();
        void onStart();
        void onStop();
        void onPause();
        void onResume();
        Transition update();
        Transition handleEvent(sf::Event &event);
};

#endif /* !EMPTYSTATE_HPP */
